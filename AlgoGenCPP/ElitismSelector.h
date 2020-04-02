#pragma once
#include <vector>
#include <algorithm>

template <typename T>
class ElitismSelector
{
public:
	ElitismSelector(int number_selection) : m_number_selection(number_selection)
	{};


	std::vector<T> operator()(std::vector<T> population, std::vector<float> notes) const
	{
		std::vector<T> final_population;
		int count = 0;

		while (count < m_number_selection)
		{
			int index_max = std::distance(notes.begin(), std::max_element(notes.begin(), notes.end()));
			final_population.push_back(population.at(index_max));
			notes.erase(notes.begin() + index_max);
			population.erase(population.begin() + index_max);
			++count;
		}

		return final_population;
	}

private:
	int m_number_selection;
};
