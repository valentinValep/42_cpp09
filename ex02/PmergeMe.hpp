#pragma once

#include "MergePair.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

template <typename T, template<typename, class> class Container, unsigned N = 32>
class PmergeMe
{
private:
	Container<T, std::allocator<T> >	container;

	PmergeMe();
	PmergeMe(const PmergeMe &src);

	void swap_pairs();
public:
	PmergeMe	&operator=(const PmergeMe &src);
	~PmergeMe();
	PmergeMe(const Container<T, std::allocator<T> > &array);
	Container<T, std::allocator<T> >	merge_insertion_sort();
};

template <typename T, template<typename, class> class Container>
class PmergeMe<T, Container, 0>
{
private:
	Container<T, std::allocator<T> >	container;

	PmergeMe();
	PmergeMe(const PmergeMe &src);
	PmergeMe	&operator=(const PmergeMe &src);

	void swap_pairs();
public:
	~PmergeMe();
	PmergeMe(const Container<T, std::allocator<T> > &array);
	Container<T, std::allocator<T> >	merge_insertion_sort();

	class InvalidArraySizeException : public std::exception
	{
		virtual const char *what() const throw();
	};
};

#include "PmergeMeSpecialization.tpp"
#include "PmergeMe.tpp"
