#pragma once
#include <vector>
#include <algorithm> 
#include <random>

template <typename T>
class TournamentSelector
{
public:
	TournamentSelector(int cluster_size) : m_cluster_size(m_cluster_size)
	{};


	std::vector<T> operator()(std::vector<T> population, std::vector<float> notes)
	{
		std::vector<T> final_population;
		std::vector<T> cluster;
		for (std::vector<T>::iterator it = population.begin(); it != population.end(); ++it)
		{
			while(!population.empty() && population.size() > m_cluster_size)
			{
				for (int i = 0; i < cluster_size; ++i)
				{
					std::random_device random_device;
					std::mt19937 engine{ random_device() };
					std::uniform_int_distribution<int> dist(0, population.size() - 1);
					int random_element = v[dist(engine)];
					cluster.push_back(notes.at(random_element));
					notes.erase(notes.at(random_element));
					population.erase(population.at(random_element));
				}
				int index_max = std::max_element(cluster.begin(), cluster.end());
				final_population.push_back(population.at(index_max));
				cluster.clear();
			}
		}
		return final_population;
	}

private:
	int m_cluster_size;
};