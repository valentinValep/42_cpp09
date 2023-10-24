#include "PmergeMe.hpp"
#include <iostream>

int	main(void)
{
	int	ret;

	if (!(ret = basic_tests()))
		std::cout << "Basic tests: ✅" << std::endl;
	else
		std::cout << "Basic tests: ❌" << std::endl;
	return (0);
}
