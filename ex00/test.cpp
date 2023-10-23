#include "BitcoinExchange.hpp"
#include "Date.hpp"
#include <iostream>

int	test_date_constructors(void)
{
	Date	d1;
	Date	d2(1, 1, 1970);
	Date	d3("1970-01-01");

	if (d1.getDay() != 0 || d1.getMonth() != 0 || d1.getYear() != 0)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d1.getDay() != 0 || d1.getMonth() != 0 || d1.getYear() != 0" << std::endl;
		return (0);
	}
	if (d2.getDay() != 1 || d2.getMonth() != 1 || d2.getYear() != 1970)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d2.getDay() != 1 || d2.getMonth() != 1 || d2.getYear() != 1970" << std::endl;
		return (0);
	}
	if (d3.getDay() != 1 || d3.getMonth() != 1 || d3.getYear() != 1970)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d3.getDay() != 1 || d3.getMonth() != 1 || d3.getYear() != 1970" << std::endl;
		return (0);
	}

	try
	{
		Date	d4(32, 1, 1970);
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "Date(32, 1, 1970) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(1, 13, 1970);
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "Date(1, 13, 1970) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(1, 1, 0);
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "Date(1, 1, 0) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(29, 2, 2019);
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "Date(29, 2, 2019) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(29, 2, 2020);
	}
	catch (Date::InvalidDateException &e)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "Date(29, 2, 2020) should not throw an exception" << std::endl;
		return (0);
	}

	try
	{
		Date	d4(29, 2, 2021);
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "Date(29, 2, 2021) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(30, 2, 2020);
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "Date(30, 2, 2020) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(29, 2, 1900);
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "Date(29, 2, 1900) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(29, 2, 2000);
	}
	catch (Date::InvalidDateException &e)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "Date(29, 2, 2000) should not throw an exception" << std::endl;
		return (0);
	}

	try
	{
		Date	d4(31, 4, 2020);
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "Date(31, 4, 2020) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(31, 6, 2020);
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "Date(31, 6, 2020) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(31, 9, 2020);
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "Date(31, 9, 2020) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(31, 11, 2020);
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "Date(31, 11, 2020) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}
	return (1);
}

int	test_date_operators(void)
{
	Date	d1;
	Date	d2(1, 1, 1970);
	Date	d3(1, 1, 1970);
	Date	d4(10, 10, 1971);
	Date	d5(10, 2, 1970);
	Date	d6(2, 1, 1970);

	if (d1 != d1)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d1 != d1" << std::endl;
		return (0);
	}
	if (d1 == d2)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d1 == d2" << std::endl;
		return (0);
	}
	if (d2 != d3)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d2 != d3" << std::endl;
		return (0);
	}
	if (!(d2 <= d3))
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "!(d2 <= d3)" << std::endl;
		return (0);
	}
	if (!(d2 >= d3))
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "!(d2 >= d3)" << std::endl;
		return (0);
	}
	if (d2 == d4)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d2 == d4" << std::endl;
		return (0);
	}
	if (!(d2 < d4))
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "!(d2 < d4)" << std::endl;
		return (0);
	}
	if (!(d2 <= d4))
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "!(d2 <= d4)" << std::endl;
		return (0);
	}
	if (d2 > d4)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d2 > d4" << std::endl;
		return (0);
	}
	if (d2 >= d4)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d2 >= d4" << std::endl;
		return (0);
	}
	if (d2 == d5)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d2 == d5" << std::endl;
		return (0);
	}
	if (!(d2 < d5))
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "!(d2 < d5)" << std::endl;
		return (0);
	}
	if (!(d2 <= d5))
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "!(d2 <= d5)" << std::endl;
		return (0);
	}
	if (d2 > d5)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d2 > d5" << std::endl;
		return (0);
	}
	if (d2 >= d5)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d2 >= d5" << std::endl;
		return (0);
	}
	if (d2 == d6)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d2 == d6" << std::endl;
		return (0);
	}
	if (!(d2 < d6))
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "!(d2 < d6)" << std::endl;
		return (0);
	}
	if (!(d2 <= d6))
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "!(d2 <= d6)" << std::endl;
		return (0);
	}
	if (d2 > d6)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d2 > d6" << std::endl;
		return (0);
	}
	if (d2 >= d6)
	{
		std::cerr << __FILE__ << ": " << __LINE__ << ": " << "d2 >= d6" << std::endl;
		return (0);
	}
	return (1);
}

int	test_date(void)
{
	if (!test_date_constructors())
		return (0);
	if (!test_date_operators())
		return (0);
	return (1);
}

int	main(void)
{
	if (test_date())
		std::cout << "Date: \033[32mOK\033[0m" << std::endl;
	else
		std::cout << "Date: \033[31mKO\033[0m" << std::endl;
	return (0);
}
