#pragma once

#include "MergePair.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

template <typename T, unsigned N = 32>
class PmergeMe
{
private:
	std::vector<T>	vector;

	PmergeMe();
	PmergeMe(const PmergeMe &src);

	void swap_pairs();
public:
	PmergeMe	&operator=(const PmergeMe &src);
	~PmergeMe();
	PmergeMe(const std::vector<T> &array);
	std::vector<T>	merge_insertion_sort();
};

template <typename T>
class PmergeMe<T, 0>
{
private:
	std::vector<T>	vector;

	PmergeMe();
	PmergeMe(const PmergeMe &src);
	PmergeMe	&operator=(const PmergeMe &src);

	void swap_pairs();
public:
	~PmergeMe();
	PmergeMe(const std::vector<T> &array);
	std::vector<T>	merge_insertion_sort();

	class InvalidArraySizeException : public std::exception
	{
		virtual const char *what() const throw();
	};
};

#include "PmergeMeSpecialization.tpp"
#include "PmergeMe.tpp"
