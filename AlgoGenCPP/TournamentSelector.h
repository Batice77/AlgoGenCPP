#pragma once
#include <vector>
#include <algorithm> 
#include <random>

template <typename T>
class TournamentSelector
{
public:
	TournamentSelector(int number_selection, int cluster_size) : m_cluster_size(cluster_size), m_number_selection(number_selection)
	{}

	std::vector<T> operator()(std::vector<T> population, std::vector<float> notes)
	{
		std::vector<T> final_population;
		std::vector<T> clusterPopulation;
		std::vector<float> clusterNotes;
		std::vector<int> clusterIndex;
		int count = 0;
		std::uniform_int_distribution<> dist;
		while (count < m_number_selection)
		{
			for (int i = 0; i < m_cluster_size; ++i)
			{
				std::random_device random_device;
				std::mt19937 engine{ random_device() };

				if (population.empty())
					break;
				else if (population.size() < m_cluster_size)
				{
					dist = std::uniform_int_distribution<>(0, population.size() - 1);
				}
				else
				{
					dist = std::uniform_int_distribution<>(0, m_cluster_size - 1);
				}

				int random_element = population[dist(engine)];
				clusterPopulation.push_back(population.at(random_element));
				clusterNotes.push_back(notes.at(random_element));
				clusterIndex.push_back(random_element);
			}
			int index_max = std::distance(clusterNotes.begin(), std::max_element(clusterNotes.begin(), clusterNotes.end()));
			int index_individu = clusterIndex.at(index_max);
			final_population.push_back(population.at(index_individu));
			notes.erase(notes.begin() + index_individu);
			population.erase(population.begin() + index_individu);

			clusterPopulation.clear();
			clusterNotes.clear();
			clusterIndex.clear();
			count++;
		}
		return final_population;
	}

private:
	int m_cluster_size;
	int m_number_selection;
};