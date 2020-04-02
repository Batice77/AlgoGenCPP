#pragma once
#include <vector>
#include <algorithm>
#include <random>

template <typename T>
class RankSelector
{
public:
	RankSelector(int number_selection) : m_number_selection(number_selection)
	{};

	std::vector<T> operator()(std::vector<T> population, std::vector<float> notes)
	{
		float sum = 0;
		for (int i = 0; i < notes.size(); i++)
			sum += notes.at(i);
		std::random_device random_device;
		std::mt19937 engine{ random_device() };
		std::uniform_real_distribution<float> dist(0, sum);
		float random_element = dist(engine);
		std::vector<T> ranked_population;
		std::vector<T> notes2;
		std::vector<T> final_population;

		while (!population.empty())
		{
			int index_max = std::max_element(notes.begin(), notes.end());
			ranked_population.push_back(population.at(index_max));
			notes2.push_back(population.at(index_max));
			notes.erase(notes.begin() + index_max);
			population.erase(population.begin() + index_max);
		}

		int count = 0;

		if (count <= m_number_selection)
		{
			float s = 0;
			for (int i = 0; i < notes.size(); i++)
			{
				s += notes.at(i);
				if (s > random_element)
				{
					final_population.push_back(population.at(i));
					notes.erase(notes.at(i));
					population.erase(population.at(i));
					++count;
				}
			}
		}

		return final_population;
	}

private:
	int m_number_selection;
};