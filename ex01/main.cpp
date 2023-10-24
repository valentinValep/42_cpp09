#include "RNP.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./RNP <inverted Polish mathematical expression>" << std::endl;
		return (1);
	}
	try
	{
		std::cout << rnp(argv[1]) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
