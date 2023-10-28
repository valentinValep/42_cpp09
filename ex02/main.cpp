#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <utility>
#include <sys/time.h>

unsigned long long int getTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

int	sort(int argc, char **argv)
{
	std::vector<unsigned int> vec;
	std::deque<unsigned int> dequeue;
	unsigned long long int time;

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
		dequeue.push_back(num);
	}

	std::cout << "Before: ";
	for (std::vector<unsigned int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	// std::vector
	time = getTime();
	PmergeMe<unsigned int, std::vector > pmm_vector(vec);
	std::vector<unsigned int> sorted_vec = pmm_vector.merge_insertion_sort();
	time = getTime() - time;

	std::cout << "After: ";
	for (std::vector<unsigned int>::iterator it = sorted_vec.begin(); it != sorted_vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "Time to process a range of " << argc - 1 << "elements with std::vector: " << time << "us" << std::endl;

	// std::deque @TODO
	time = getTime();
	PmergeMe<unsigned int, std::deque > pmm_deque(dequeue);
	pmm_deque.merge_insertion_sort();
	time = getTime() - time;

	std::cout << "Time to process a range of " << argc - 1 << "elements with std::deque: " << time << "us" << std::endl;

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
