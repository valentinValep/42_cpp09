#include "MergePair.hpp"

template <typename T>
MergePair<T>::MergePair(): main(NULL), second(NULL)
{}

template <typename T>
MergePair<T>::MergePair(const MergePair<T> &src): main(src.main), second(src.second)
{}

template <typename T>
MergePair<T>::MergePair(T *main, T *second): main(main), second(second)
{}

template <typename T>
MergePair<T>::~MergePair()
{}

template <typename T>
MergePair<T>	&MergePair<T>::operator=(const MergePair<T> &src)
{
	this->main = src.main;
	this->second = src.second;
	return (*this);
}

template <typename T>
bool MergePair<T>::operator==(const MergePair &src) const
{
	return (*this->main == *src.main);
}

template <typename T>
bool MergePair<T>::operator!=(const MergePair &src) const
{
	return (*this->main != *src.main);
}

template <typename T>
bool MergePair<T>::operator<(const MergePair &src) const
{
	return (*this->main < *src.main);
}

template <typename T>
bool MergePair<T>::operator<=(const MergePair &src) const
{
	return (*this->main <= *src.main);
}

template <typename T>
bool MergePair<T>::operator>=(const MergePair &src) const
{
	return (*this->main >= *src.main);
}

template <typename T>
bool MergePair<T>::operator>(const MergePair &src) const
{
	return (*this->main > *src.main);
}

template<class T>
const T *MergePair<T>::get_main() const
{
	return (this->main);
}

template<class T>
const T *MergePair<T>::get_second() const
{
	return (this->second);
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const MergePair<T> &src)
{
	out << "[" << *src.get_main() << " > " << *src.get_second() << "]";
	return (out);
}
