#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>

template <typename T, unsigned N>
PmergeMe<T, N>::PmergeMe()
{}

template <typename T, unsigned N>
PmergeMe<T, N>::PmergeMe(const PmergeMe &src)
{
	(void)src;
}

template <typename T, unsigned N>
PmergeMe<T, N>::~PmergeMe()
{}

template <typename T, unsigned N>
PmergeMe<T, N>	&PmergeMe<T, N>::operator=(const PmergeMe<T, N> &src)
{
	(void)src;
	return (*this);
}

template <typename T, unsigned N>
inline void PmergeMe<T, N>::swap_pairs()
{
	for (typename std::vector<T>::iterator it = this->vector.begin() + 1; it < this->vector.end(); it += 2)
		if (*it < *(it - 1))
			std::swap(*it, *(it - 1));
}

template <typename T, unsigned N>
inline PmergeMe<T, N>::PmergeMe(const std::vector<T> &array)
{
	this->vector = array;
}

static std::vector<unsigned int>	get_jacobstal_numbers(unsigned int n)
{
	std::vector<unsigned int>	jacobstal_numbers;

	jacobstal_numbers.push_back(0);
	jacobstal_numbers.push_back(1);
	for (unsigned int i = 2; i <= n; i++)
		jacobstal_numbers.push_back(jacobstal_numbers[i - 1] + 2 * jacobstal_numbers[i - 2]);
	return jacobstal_numbers;
}

static std::vector<unsigned int>	get_jacobstal_indexes(unsigned int n)
{
	std::vector<unsigned int>	jacobstal_indexes;
	unsigned int				jacobstal_index = 0;

	for (unsigned int i = 0; i <= n; i++)
	{

	}
	return jacobstal_indexes;
}

template <typename T, unsigned N>
inline std::vector<T> PmergeMe<T, N>::merge_insertion_sort()
{
	std::vector<MergePair<T> >	pairs;

	if (this->vector.size() <= 1)
		return this->vector;
	if (this->vector.size() == 2)
	{
		if (this->vector[0] > this->vector[1])
			std::swap(this->vector[0], this->vector[1]);
		return this->vector;
	}
	this->swap_pairs();

	for (typename std::vector<T>::iterator it = this->vector.begin() + 1; it < this->vector.end(); it += 2)
		pairs.push_back(MergePair<T>(&(*it), &(*(it - 1))));
	std::cout << "sending pairs: ";
	for (typename std::vector<MergePair<T> >::iterator it = pairs.begin(); it != pairs.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	PmergeMe<MergePair<T>, N - 1> pmm(pairs);
	pairs = pmm.merge_insertion_sort();

	std::cout << "sorted pairs: ";
	for (typename std::vector<MergePair<T> >::iterator it = pairs.begin(); it != pairs.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::vector<T>	sorted;
	std::vector<T>	pending;
	for (typename std::vector<MergePair<T> >::iterator it = pairs.begin(); it != pairs.end(); it++)
	{
		sorted.push_back(*it->get_main());
		pending.push_back(*it->get_second());
	}
	if (this->vector.size() % 2 == 1)
		pending.push_back(this->vector[this->vector.size() - 1]);

	std::cout << "sorted: ";
	for (typename std::vector<T>::iterator it = sorted.begin(); it != sorted.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "pending: ";
	for (typename std::vector<T>::iterator it = pending.begin(); it != pending.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;



	return sorted;
}
