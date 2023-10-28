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
	this->vector = src.vector;
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

unsigned int	get_jacobstal_number(unsigned int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return get_jacobstal_number(n - 1) + get_jacobstal_number(n - 2) * 2;
}

std::vector<unsigned int>	get_jacobstal_indexes(unsigned int size)
{
	std::vector<unsigned int>	jac_indexes;
	unsigned int				index = 0;
	unsigned int				last_jac_num = 0;
	unsigned int				jac_seq_index = 2;

	for (unsigned int i = 0; i < size; i++)
	{
		jac_indexes.push_back(index);
		if (index == 0 || index - 1 == last_jac_num)
		{
			last_jac_num = get_jacobstal_number(jac_seq_index) - 1;
			index = get_jacobstal_number(++jac_seq_index) - 1;
			if (i + 1 >= size)
				return (jac_indexes);
		}
		else
			index--;
	}
	while (!(index == 0 || index - 1 < last_jac_num))
		jac_indexes.push_back(index--);

	return jac_indexes;
}

template <typename T>
unsigned int	binary_search(const std::vector<T> &array, size_t size, T value)
{
	unsigned int	min = 0;
	unsigned int	max = size - 1;
	unsigned int	mid;

	if (size == 0)
		return (0);
	while (min <= max)
	{
		mid = (min + max) / 2;
		if (array[mid] == value)
			return mid;
		if (array[mid] < value)
			min = mid + 1;
		else if (mid == 0)
			return 0;
		else
			max = mid - 1;
	}
	return min;
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
	//std::cout << "sending pairs: ";
	//for (typename std::vector<MergePair<T> >::iterator it = pairs.begin(); it != pairs.end(); it++)
	//	std::cout << *it << " ";
	//std::cout << std::endl;
	PmergeMe<MergePair<T>, N - 1> pmm(pairs);
	pairs = pmm.merge_insertion_sort();

	//std::cout << "sorted pairs: ";
	//for (typename std::vector<MergePair<T> >::iterator it = pairs.begin(); it != pairs.end(); it++)
	//	std::cout << *it << " ";
	//std::cout << std::endl;

	std::vector<T>	sorted;
	std::vector<T>	pending;
	for (typename std::vector<MergePair<T> >::iterator it = pairs.begin(); it != pairs.end(); it++)
	{
		sorted.push_back(*it->get_main());
		pending.push_back(*it->get_second());
	}
	if (this->vector.size() % 2 == 1)
		pending.push_back(this->vector[this->vector.size() - 1]);

	std::vector<unsigned int>	jac_indexes = get_jacobstal_indexes(pending.size());
	unsigned int bin_search_size;
	for (unsigned int i = 0; i < jac_indexes.size(); i++)
	{
		//std::cout << "==================\nsorted: ";
		//for (typename std::vector<T>::iterator it = sorted.begin(); it != sorted.end(); it++)
		//	std::cout << *it << " ";
		//std::cout << std::endl;

		//std::cout << "pending: ";
		//for (typename std::vector<T>::iterator it = pending.begin(); it != pending.end(); it++)
		//	std::cout << *it << " ";
		//std::cout << std::endl;

		unsigned int pending_index = jac_indexes[i];

		if (i == 0 || jac_indexes[i - 1] != jac_indexes[i] + 1)
			bin_search_size = i + jac_indexes[i];

		//std::cout << "pending_index: " << pending_index << std::endl;
		//std::cout << "bin_search_size: " << bin_search_size << std::endl;
		if (pending_index >= pending.size())
		{
			bin_search_size--;
			continue;
		}

		unsigned int insert_index = binary_search(sorted, bin_search_size, pending[pending_index]);
		//std::cout << "insert_index: " << insert_index << std::endl;

		if (insert_index == bin_search_size)
			bin_search_size--;

		sorted.insert(sorted.begin() + insert_index, pending[pending_index]);
	}

	//std::cout << "==================\nsorted: ";
	//for (typename std::vector<T>::iterator it = sorted.begin(); it != sorted.end(); it++)
	//	std::cout << *it << " ";
	//std::cout << std::endl;

	return sorted;
}
