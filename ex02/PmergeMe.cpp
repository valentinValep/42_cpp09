#include "PmergeMe.hpp"

PmergeMe::PmergeMe(): /* @TODO data */
{}

PmergeMe::PmergeMe(const PmergeMe &src): /* @TODO data */
{}

PmergeMe::~PmergeMe()
{}

PmergeMe	&PmergeMe::operator=(const PmergeMe &src)
{
	if (this == &src)
		return (*this);
	// @TODO
	// Copy all the data from src to this
	// ex: this->data = src.data;
	return (*this);
}
