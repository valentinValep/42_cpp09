#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>

template <typename T>
PmergeMe<T, 0>::PmergeMe()
{}

template <typename T>
PmergeMe<T, 0>::PmergeMe(const PmergeMe &src)
{
	(void)src;
}

template <typename T>
PmergeMe<T, 0>::~PmergeMe()
{}

template <typename T>
PmergeMe<T, 0>	&PmergeMe<T, 0>::operator=(const PmergeMe<T, 0> &src)
{
	(void)src;
	return (*this);
}

template <typename T>
inline void PmergeMe<T, 0>::swap_pairs()
{
	for (typename std::vector<T>::iterator it = this->vector.begin() + 1; it < this->vector.end(); it += 2)
		if (*it < *(it - 1))
			std::swap(*it, *(it - 1));
}

template <typename T>
inline PmergeMe<T, 0>::PmergeMe(const std::vector<T> &array)
{
	this->vector = array;
}

template <typename T>
inline std::vector<T> PmergeMe<T, 0>::merge_insertion_sort()
{
	if (this->vector.size() <= 1)
		return this->vector;
	if (this->vector.size() > 2)
		throw InvalidArraySizeException();
	if (this->vector[0] > this->vector[1])
		std::swap(this->vector[0], this->vector[1]);
	return this->vector;
}

template <typename T>
inline const char *PmergeMe<T, 0>::InvalidArraySizeException::what() const throw()
{
	return "Invalid array size";
}
