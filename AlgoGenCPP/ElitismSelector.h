#pragma once
#include <vector>
#include <algorithm> 

template <typename T>
class ElitismSelector
{
public:
	ElitismSelector(int number_selection) : m_number_selection(number_selection)
	{};


	std::vector<T> operator()(std::vector<T> population, std::vector<float> notes)
	{
		std::vector<T> final_population;
		int count = 0;
		for (std::vector<T>::iterator it = population.begin(); it != population.end(); ++it)
		{
			if (count <= m_number_selection)
			{
				int index_max = std::max_element(notes.begin(), notes.end());
				final_population.push_back(population.at(index_max));
				notes.erase(notes.at(index_max));
				population.erase(population.at(random_element));
				++count;
			}
		}
		return final_population;
	}

private:
	int m_number_selection;
};