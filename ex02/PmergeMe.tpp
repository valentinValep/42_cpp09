#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>

template <typename T, template<typename, class> class Container, unsigned N>
PmergeMe<T, Container, N>::PmergeMe()
{}

template <typename T, template<typename, class> class Container, unsigned N>
PmergeMe<T, Container, N>::PmergeMe(const PmergeMe<T, Container, N> &src)
{
	(void)src;
}

template <typename T, template<typename, class> class Container, unsigned N>
PmergeMe<T, Container, N>::~PmergeMe()
{}

template <typename T, template<typename, class> class Container, unsigned N>
PmergeMe<T, Container, N>	&PmergeMe<T, Container, N>::operator=(const PmergeMe<T, Container, N> &src)
{
	this->container = src.container;
	return (*this);
}

template <typename T, template<typename, class> class Container, unsigned N>
inline void PmergeMe<T, Container, N>::swap_pairs()
{
	for (typename Container<T, std::allocator<T> >::iterator it = this->container.begin() + 1; it < this->container.end(); it += 2)
		if (*it < *(it - 1))
			std::swap(*it, *(it - 1));
}

template <typename T, template<typename, class> class Container, unsigned N>
inline PmergeMe<T, Container, N>::PmergeMe(const Container<T, std::allocator<T> > &array)
{
	this->container = array;
}

unsigned int	get_jacobstal_number(unsigned int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return get_jacobstal_number(n - 1) + get_jacobstal_number(n - 2) * 2;
}

template <template<typename, class> class Container>
Container<unsigned int, std::allocator<unsigned int> >	get_jacobstal_indexes(unsigned int size)
{
	Container<unsigned int, std::allocator<unsigned int> >	jac_indexes;
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

template <typename T, template<typename, class> class Container>
unsigned int	binary_search(const Container<T, std::allocator<T> > &array, size_t size, T value)
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

template <typename T, template<typename, class> class Container, unsigned N>
inline Container<T, std::allocator<T> > PmergeMe<T, Container, N>::merge_insertion_sort()
{
	Container<MergePair<T>, std::allocator<MergePair<T> > >	pairs;

	if (this->container.size() <= 1)
		return this->container;
	if (this->container.size() == 2)
	{
		if (this->container[0] > this->container[1])
			std::swap(this->container[0], this->container[1]);
		return this->container;
	}
	this->swap_pairs();

	for (typename Container<T, std::allocator<T> >::iterator it = this->container.begin() + 1; it < this->container.end(); it += 2)
		pairs.push_back(MergePair<T>(&(*it), &(*(it - 1))));
	#ifdef DEBUG
		std::cout << "sending pairs: ";
		for (typename Container<MergePair<T>, std::allocator<MergePair<T> > >::iterator it = pairs.begin(); it != pairs.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
	#endif
	PmergeMe<MergePair<T>, Container, N - 1> pmm(pairs);
	pairs = pmm.merge_insertion_sort();

	#ifdef DEBUG
		std::cout << "sorted pairs: ";
		for (typename Container<MergePair<T>, std::allocator<MergePair<T> > >::iterator it = pairs.begin(); it != pairs.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
	#endif

	Container<T, std::allocator<T> >	sorted;
	Container<T, std::allocator<T> >	pending;
	for (typename Container<MergePair<T>, std::allocator<MergePair<T> > >::iterator it = pairs.begin(); it != pairs.end(); it++)
	{
		sorted.push_back(*it->get_main());
		pending.push_back(*it->get_second());
	}
	if (this->container.size() % 2 == 1)
		pending.push_back(this->container[this->container.size() - 1]);

	Container<unsigned int, std::allocator<unsigned int> >	jac_indexes = get_jacobstal_indexes<Container>(pending.size());
	unsigned int bin_search_size;
	for (unsigned int i = 0; i < jac_indexes.size(); i++)
	{
		#ifdef DEBUG
			std::cout << "==================\nsorted: ";
			for (typename Container<T, std::allocator<T> >::iterator it = sorted.begin(); it != sorted.end(); it++)
				std::cout << *it << " ";
			std::cout << std::endl;
			std::cout << "pending: ";
			for (typename Container<T, std::allocator<T> >::iterator it = pending.begin(); it != pending.end(); it++)
				std::cout << *it << " ";
			std::cout << std::endl;
		#endif

		unsigned int pending_index = jac_indexes[i];

		if (i == 0 || jac_indexes[i - 1] != jac_indexes[i] + 1)
			bin_search_size = i + jac_indexes[i];

		#ifdef DEBUG
			std::cout << "pending_index: " << pending_index << std::endl;
			std::cout << "bin_search_size: " << bin_search_size << std::endl;
		#endif
		if (pending_index >= pending.size())
		{
			bin_search_size--;
			continue;
		}

		unsigned int insert_index = binary_search(sorted, bin_search_size, pending[pending_index]);
		#ifdef DEBUG
			std::cout << "insert_index: " << insert_index << std::endl;
		#endif
		if (insert_index == bin_search_size)
			bin_search_size--;

		sorted.insert(sorted.begin() + insert_index, pending[pending_index]);
	}

	//std::cout << "==================\nsorted: ";
	//for (typename Container<T, std::allocator<T> >::iterator it = sorted.begin(); it != sorted.end(); it++)
	//	std::cout << *it << " ";
	//std::cout << std::endl;

	return sorted;
}
