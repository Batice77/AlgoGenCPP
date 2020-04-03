#include "Scene.h"
#include <sstream>

Scene::Scene()
{
}

Scene::Scene(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) :
	m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre), m_hauteurFenetre(hauteurFenetre),
	m_fenetre(0), m_contexteOpenGL(0), m_glsl_version(""),m_io(0)/*, m_input()*/
{
}

Scene::~Scene()
{
	SDL_GL_DeleteContext(m_contexteOpenGL);
	SDL_DestroyWindow(m_fenetre);
	SDL_Quit();
}

bool Scene::initialiserFenetre()
{
	//Initialisation de la SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		printf("Error: %s\n", SDL_GetError());
		return false;
	}

	// Decide GL+GLSL versions
#if __APPLE__
	// GL 3.2 Core + GLSL 150
	m_glsl_version = "#version 150";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
	// GL 3.0 + GLSL 130
	m_glsl_version = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

	// Create window with graphics context
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	m_fenetre = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, window_flags);
	
	if (NULL == m_fenetre)
	{
		std::cout << "Erreur lors de la creation de la fenetre: " << SDL_GetError() << std::endl;

		SDL_Quit();
		return false;
	}
	
	m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);
	SDL_GL_MakeCurrent(m_fenetre, m_contexteOpenGL);
	SDL_GL_SetSwapInterval(1); // Enable vsync

	//Creation du contexte OpenGL
	m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);
	if (m_contexteOpenGL == 0)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_fenetre);
		SDL_Quit();

		return false;
	}
	return true;
}

bool Scene::initGL()
{
	// Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
	bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
	bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
	bool err = false;
	glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
	bool err = false;
	glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)SDL_GL_GetProcAddress(name); });
#else
	bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		SDL_GL_DeleteContext(m_contexteOpenGL);
		SDL_DestroyWindow(m_fenetre);
		SDL_Quit();
		return false;
	}
	return true;
}

bool Scene::initImGui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	m_io = &io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(m_fenetre, m_contexteOpenGL);
	ImGui_ImplOpenGL3_Init(m_glsl_version);
	return true;
}

void Scene::bouclePrincipale()
{
	bool terminer(false);
	float angle(0.0);

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	// Main loop
	bool done = false;
	while (!done)
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				done = true;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_fenetre))
				done = true;
		}

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(m_fenetre);
		ImGui::NewFrame();

		constexpr size_t buf_size = 512;
		static float x_data[buf_size];
		static float y_data1[buf_size];
		static float y_data2[buf_size];
		static float y_data3[buf_size];

		constexpr float sampling_freq = 44100;
		constexpr float freq = 500;
		for (size_t i = 0; i < buf_size; ++i) {
			const float t = i / sampling_freq;
			x_data[i] = t;
			const float arg = 2 * M_PI * freq * t;
			y_data1[i] = sin(arg);
			y_data2[i] = y_data1[i] * -0.6 + sin(2 * arg) * 0.4;
			y_data3[i] = y_data2[i] * -0.6 + sin(3 * arg) * 0.4;
		}

		static const float* y_data[] = { y_data1, y_data2, y_data3 };
		static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(0, 0, 255) };
		static uint32_t selection_start = 0, selection_length = 0;

		ImGui::Begin("Example plot", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		// Draw first plot with multiple sources
		ImGui::PlotConfig conf;
		conf.values.xs = x_data;
		conf.values.count = buf_size;
		conf.values.ys_list = y_data; // use ys_list to draw several lines simultaneously
		conf.values.ys_count = 3;
		conf.values.colors = colors;
		conf.scale.min = -1;
		conf.scale.max = 1;
		conf.tooltip.show = true;
		conf.grid_x.show = true;
		conf.grid_x.size = 128;
		conf.grid_x.subticks = 4;
		conf.grid_y.show = true;
		conf.grid_y.size = 0.5f;
		conf.grid_y.subticks = 5;
		conf.selection.show = true;
		conf.selection.start = &selection_start;
		conf.selection.length = &selection_length;
		conf.frame_size = ImVec2(buf_size, 200);
		ImGui::Plot("plot1", conf);

		// Draw second plot with the selection
		// reset previous values
		conf.values.ys_list = nullptr;
		conf.selection.show = false;
		// set new ones
		conf.values.ys = y_data3;
		conf.values.offset = selection_start;
		conf.values.count = selection_length;
		conf.line_thickness = 2.f;
		ImGui::Plot("plot2", conf);

		ImGui::End();

		// Rendering
		ImGui::Render();
		glViewport(0, 0, (int)m_io->DisplaySize.x, (int)m_io->DisplaySize.y);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(m_fenetre);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(m_contexteOpenGL);
	SDL_DestroyWindow(m_fenetre);
	SDL_Quit();
}
