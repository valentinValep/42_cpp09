#include "RPN.hpp"
#include <iostream>
#include <string>

int	basic_tests(void)
{
	int	ret;

	ret = 0;
	if (RPN::rpn("1") != 1)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1\") != 1" << std::endl;
		ret += 1;
	}
	if (RPN::rpn("1 2 +") != 3)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 2 +\") != 3" << std::endl;
		ret += 1;
	}
	if (RPN::rpn("1 2 -") != -1)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 2 -\") != 1" << std::endl;
		ret += 1;
	}
	if (RPN::rpn("1 2 *") != 2)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 2 *\") != 2" << std::endl;
		ret += 1;
	}
	if (RPN::rpn("1 2 /") != 0)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 2 /\") != 0" << std::endl;
		ret += 1;
	}
	return (ret);
}

int	subject_tests(void)
{
	int	ret;

	ret = 0;
	if (RPN::rpn("8 9 * 9 - 9 - 9 - 4 - 1 +") != 42)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"8 9 * 9 - 9 - 9 - 4 - 1 +\") != 42" << std::endl;
		ret += 1;
	}
	if (RPN::rpn("7 7 * 7 -") != 42)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"7 7 * 7 -\") != 42" << std::endl;
		ret += 1;
	}
	if (RPN::rpn("1 2 * 2 / 2 * 2 4 - +") != 0)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 2 * 2 / 2 * 2 4 - +\") != 0" << std::endl;
		ret += 1;
	}
	try
	{
		RPN::rpn("(1 + 1)");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"(1 + 1)\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	return (ret);
}

int	fail_tests(void)
{
	int	ret;

	ret = 0;
	try
	{
		RPN::rpn("");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	try
	{
		RPN::rpn("1 2");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 2\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	try
	{
		RPN::rpn("1 2 3 +");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 2 3 +\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	try
	{
		RPN::rpn("1 2 + 3");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 2 + 3\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	try
	{
		RPN::rpn("1 2 + 3 4 +");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 2 + 3 4 +\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	try
	{
		RPN::rpn("a");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"a\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	try
	{
		RPN::rpn("1 a +");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 a +\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	try
	{
		RPN::rpn("1 + 2");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 + 2\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	try
	{
		RPN::rpn("+ 1 2");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"+ 1 2\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	try
	{
		RPN::rpn("1 +");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 +\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	try
	{
		RPN::rpn("1 2 + +");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 2 + +\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	try
	{
		RPN::rpn("1p2p+");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1p2p+\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	try
	{
		RPN::rpn("2 0 /");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"2 0 /\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	try
	{
		RPN::rpn("10 3 +");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"2 0 /\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	try
	{
		RPN::rpn("987 3 +");
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"2 0 /\") should throw an exception but it doesn't" << std::endl;
		ret += 1;
	}
	catch(const std::exception& e)
	{}

	return (ret);
}

int	advanced_tests(void)
{
	int	ret;

	ret = 0;
	if (RPN::rpn("1 2 3 4 5 + + + +") != 15)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 2 3 4 5 + + + +\") != 15" << std::endl;
		ret += 1;
	}

	if (RPN::rpn("1 2 3 4 5 - - - -") != 3)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 2 3 4 5 - - - -\") != -13" << std::endl;
		ret += 1;
	}

	if (RPN::rpn("1 2 + 3 4 + 5 + +") != 15)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "RPN::rpn(\"1 2 + 3 4 + 5 + +\") != 15" << std::endl;
		ret += 1;
	}

	return (ret);
}

int	main(void)
{
	int	ret;

	if (!(ret = basic_tests()))
		std::cout << "Basic tests: ✅" << std::endl;
	else
		std::cout << "Basic tests: ❌" << std::endl;

	if (!(ret += subject_tests()))
		std::cout << "Subject tests: ✅" << std::endl;
	else
		std::cout << "Subject tests: ❌" << std::endl;

	if (!(ret += fail_tests()))
		std::cout << "Fail tests: ✅" << std::endl;
	else
		std::cout << "Fail tests: ❌" << std::endl;

	if (!(ret += advanced_tests()))
		std::cout << "Advanced tests: ✅" << std::endl;
	else
		std::cout << "Advanced tests: ❌" << std::endl;

	if (ret)
		std::cout << "Total: ❌" << std::endl;
	else
		std::cout << "Total: ✅" << std::endl;
	return (0);
}
