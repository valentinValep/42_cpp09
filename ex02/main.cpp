#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

int	sort(int argc, char **argv)
{
	std::vector<unsigned int> vec;
	std::list<unsigned int> list;

	for (int i = 1; i < argc; i++)
	{
		int num = atoi(argv[i]);
		if (num < 0)
		{
			std::cerr << "Error: Invalid number" << std::endl;
			return (1);
		}
		if (std::find(vec.begin(), vec.end(), num) != vec.end())
		{
			std::cerr << "Error: Duplicate number" << std::endl;
			return (1);
		}
		vec.push_back(num);
		list.push_back(num);
	}

	PmergeMe<unsigned int, 32> pmm(vec);
	std::vector<unsigned int> sorted_vec = pmm.merge_insertion_sort();

	// @TODO

	return (0);
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: ./PmergeMe <positive number>.." << std::endl;
		return (1);
	}
	sort(argc, argv);
	return (0);
}
