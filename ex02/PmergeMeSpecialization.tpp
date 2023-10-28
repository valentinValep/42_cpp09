#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>

template <typename T, template<typename, class> class Container>
PmergeMe<T, Container, 0>::PmergeMe()
{}

template <typename T, template<typename, class> class Container>
PmergeMe<T, Container, 0>::PmergeMe(const PmergeMe<T, Container, 0> &src)
{
	(void)src;
}

template <typename T, template<typename, class> class Container>
PmergeMe<T, Container, 0>::~PmergeMe()
{}

template <typename T, template<typename, class> class Container>
PmergeMe<T, Container, 0>	&PmergeMe<T, Container, 0>::operator=(const PmergeMe<T, Container, 0> &src)
{
	(void)src;
	return (*this);
}

template <typename T, template<typename, class> class Container>
inline void PmergeMe<T, Container, 0>::swap_pairs()
{
	for (typename Container<T, std::allocator<T> >::iterator it = this->container.begin() + 1; it < this->container.end(); it += 2)
		if (*it < *(it - 1))
			std::swap(*it, *(it - 1));
}

template <typename T, template<typename, class> class Container>
inline PmergeMe<T, Container, 0>::PmergeMe(const Container<T, std::allocator<T> > &array)
{
	this->container = array;
}

template <typename T, template<typename, class> class Container>
inline Container<T, std::allocator<T> > PmergeMe<T, Container, 0>::merge_insertion_sort()
{
	if (this->container.size() <= 1)
		return this->container;
	if (this->container.size() > 2)
		throw InvalidArraySizeException();
	if (this->container[0] > this->container[1])
		std::swap(this->container[0], this->container[1]);
	return this->container;
}

template <typename T, template<typename, class> class Container>
inline const char *PmergeMe<T, Container, 0>::InvalidArraySizeException::what() const throw()
{
	return "Invalid array size";
}
