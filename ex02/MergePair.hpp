#pragma once

#include <iostream>

template <typename T>
class MergePair
{
private:
	T	*main;
	T	*second;

	MergePair();
public:
	MergePair(const MergePair &src);
	MergePair(T *main, T *second);
	~MergePair();
	MergePair	&operator=(const MergePair &src);

	// comparaison operators
	bool	operator==(const MergePair &src) const;
	bool	operator!=(const MergePair &src) const;
	bool	operator<(const MergePair &src) const;
	bool	operator<=(const MergePair &src) const;
	bool	operator>(const MergePair &src) const;
	bool	operator>=(const MergePair &src) const;

	// getters
	const T	*get_main() const;
	const T	*get_second() const;
};

template <typename T>
std::ostream	&operator<<(std::ostream &out, const MergePair<T> &src);

#include "MergePair.tpp"
