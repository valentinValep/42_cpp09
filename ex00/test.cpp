#include "BitcoinExchange.hpp"
#include "Date.hpp"
#include <iostream>
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
		( std::ostringstream() << std::dec << x ) ).str()

int	test_date_constructors(void)
{
	Date	d1;
	Date	d2(1, 1, 1970);
	Date	d3("1970-01-01");

	if (d1.getDay() != 0 || d1.getMonth() != 0 || d1.getYear() != 0)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d1.getDay() != 0 || d1.getMonth() != 0 || d1.getYear() != 0" << std::endl;
		return (0);
	}
	if (d2.getDay() != 1 || d2.getMonth() != 1 || d2.getYear() != 1970)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d2.getDay() != 1 || d2.getMonth() != 1 || d2.getYear() != 1970" << std::endl;
		return (0);
	}
	if (d3.getDay() != 1 || d3.getMonth() != 1 || d3.getYear() != 1970)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d3.getDay() != 1 || d3.getMonth() != 1 || d3.getYear() != 1970" << std::endl;
		return (0);
	}

	try
	{
		Date	d4(32, 1, 1970);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(32, 1, 1970) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(1, 13, 1970);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(1, 13, 1970) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(1, 1, 0);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(1, 1, 0) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(29, 2, 2019);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(29, 2, 2019) should throw an exception" << std::endl;
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
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(29, 2, 2020) should not throw an exception" << std::endl;
		return (0);
	}

	try
	{
		Date	d4(29, 2, 2021);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(29, 2, 2021) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(30, 2, 2020);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(30, 2, 2020) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(29, 2, 1900);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(29, 2, 1900) should throw an exception" << std::endl;
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
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(29, 2, 2000) should not throw an exception" << std::endl;
		return (0);
	}

	try
	{
		Date	d4(31, 4, 2020);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(31, 4, 2020) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(31, 6, 2020);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(31, 6, 2020) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(31, 9, 2020);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(31, 9, 2020) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(31, 11, 2020);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(31, 11, 2020) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(31, 0, 2020);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(31, 0, 2020) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(31, 11, 0);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(31, 11, 0) should throw an exception" << std::endl;
		return (0);
	}
	catch (Date::InvalidDateException &e)
	{}

	try
	{
		Date	d4(0, 11, 2020);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "Date(0, 11, 2020) should throw an exception" << std::endl;
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
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d1 != d1" << std::endl;
		return (0);
	}
	if (d1 == d2)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d1 == d2" << std::endl;
		return (0);
	}
	if (d2 != d3)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d2 != d3" << std::endl;
		return (0);
	}
	if (!(d2 <= d3))
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "!(d2 <= d3)" << std::endl;
		return (0);
	}
	if (!(d2 >= d3))
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "!(d2 >= d3)" << std::endl;
		return (0);
	}
	if (d2 == d4)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d2 == d4" << std::endl;
		return (0);
	}
	if (!(d2 < d4))
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "!(d2 < d4)" << std::endl;
		return (0);
	}
	if (!(d2 <= d4))
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "!(d2 <= d4)" << std::endl;
		return (0);
	}
	if (d2 > d4)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d2 > d4" << std::endl;
		return (0);
	}
	if (d2 >= d4)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d2 >= d4" << std::endl;
		return (0);
	}
	if (d2 == d5)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d2 == d5" << std::endl;
		return (0);
	}
	if (!(d2 < d5))
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "!(d2 < d5)" << std::endl;
		return (0);
	}
	if (!(d2 <= d5))
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "!(d2 <= d5)" << std::endl;
		return (0);
	}
	if (d2 > d5)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d2 > d5" << std::endl;
		return (0);
	}
	if (d2 >= d5)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d2 >= d5" << std::endl;
		return (0);
	}
	if (d2 == d6)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d2 == d6" << std::endl;
		return (0);
	}
	if (!(d2 < d6))
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "!(d2 < d6)" << std::endl;
		return (0);
	}
	if (!(d2 <= d6))
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "!(d2 <= d6)" << std::endl;
		return (0);
	}
	if (d2 > d6)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d2 > d6" << std::endl;
		return (0);
	}
	if (d2 >= d6)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "d2 >= d6" << std::endl;
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

int	test_bitcoin_exchange_constructors(void)
{
	std::streambuf	*old;

	try
	{
		BitcoinExchange	exchange("data.csv");
	}
	catch (BitcoinExchange::ConstructorFailedException &e)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "BitcoinExchange(\"data.csv\") should not throw an exception" << std::endl;
		return (0);
	}

	try
	{
		BitcoinExchange	exchange("tests/data1.csv");
	}
	catch (BitcoinExchange::ConstructorFailedException &e)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "BitcoinExchange(\"tests/data1.csv\") should not throw an exception" << std::endl;
		return (0);
	}

	try
	{
		old = std::cerr.rdbuf(NULL);
		BitcoinExchange	exchange("does_not_exists.csv");
		std::cerr.rdbuf(old);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "BitcoinExchange(\"data2.csv\") should throw an exception" << std::endl;
		return (0);
	}
	catch (BitcoinExchange::ConstructorFailedException &e)
	{
		std::cerr.rdbuf(old);
	}

	try
	{
		old = std::cerr.rdbuf(NULL);
		BitcoinExchange	exchange("data_fails/data_fail_date.csv");
		std::cerr.rdbuf(old);
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "BitcoinExchange(\"data_fails/data_fail_date.csv\") should throw an exception" << std::endl;
		return (0);
	}
	catch (BitcoinExchange::ConstructorFailedException &e)
	{
		std::cerr.rdbuf(old);
	}

	for (int i = 1; i <= 17; i++)
	{
		try
		{
			old = std::cerr.rdbuf(NULL);
			BitcoinExchange	exchange(SSTR("data_fails/detailled/data_fail_date" << i << ".csv"));
			std::cerr.rdbuf(old);
			std::cerr << __FILE__ << ":" << __LINE__ << ": " << "BitcoinExchange(\"data_fails/detailled/data_fail_date" << i << ".csv\") should throw an exception" << std::endl;
			return (0);
		}
		catch (BitcoinExchange::ConstructorFailedException &e)
		{
			std::cerr.rdbuf(old);
		}
	}

	for (int i = 1; i <= 7; i++)
	{
		try
		{
			old = std::cerr.rdbuf(NULL);
			BitcoinExchange	exchange(SSTR("data_fails/detailled/data_fail_rate" << i << ".csv"));
			std::cerr.rdbuf(old);
			std::cerr << __FILE__ << ":" << __LINE__ << ": " << "BitcoinExchange(\"data_fails/detailled/data_fail_rate" << i << ".csv\") should throw an exception" << std::endl;
			return (0);
		}
		catch (BitcoinExchange::ConstructorFailedException &e)
		{
			std::cerr.rdbuf(old);
		}
	}

	return (1);
}

int	test_bitcoin_exchange_get_rate(void)
{
	BitcoinExchange	exchange("tests/data1.csv");

	std::streambuf	*old = std::cout.rdbuf(NULL);
	if (exchange.getRate("2010-09-30") != -1.)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "exchange.getRate(\"2010-09-30\") != -1." << std::endl;
		return (0);
	}
	std::cout.rdbuf(old);

	if (exchange.getRate("2010-10-01") != 0.1)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "exchange.getRate(\"2010-10-01\") != 0.1" << std::endl;
		return (0);
	}

	if (exchange.getRate("2010-10-02") != 0.1)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "exchange.getRate(\"2010-10-02\") != 0.1" << std::endl;
		return (0);
	}

	if (exchange.getRate("2010-10-31") != 0.1)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "exchange.getRate(\"2010-10-31\") != 0.1" << std::endl;
		return (0);
	}

	if (exchange.getRate("2010-11-01") != 0.2)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "exchange.getRate(\"2010-11-01\") != 0.2" << std::endl;
		return (0);
	}

	if (exchange.getRate("2010-11-02") != 0.2)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "exchange.getRate(\"2010-11-02\") != 0.2" << std::endl;
		return (0);
	}

	if (exchange.getRate("3000-01-01") != 0.2)
	{
		std::cerr << __FILE__ << ":" << __LINE__ << ": " << "exchange.getRate(\"3000-01-01\") != 0.2" << std::endl;
		return (0);
	}

	return (1);
}

int	test_bitcoin_exchange(void)
{
	if (!test_bitcoin_exchange_constructors())
		return (0);
	if (!test_bitcoin_exchange_get_rate())
		return (0);
	return (1);
}

int	main(void)
{
	if (test_date())
		std::cout << "Date: \033[32mOK\033[0m" << std::endl;
	else
		std::cout << "Date: \033[31mKO\033[0m" << std::endl;
	if (test_bitcoin_exchange())
		std::cout << "BitcoinExchange: \033[32mOK\033[0m" << std::endl;
	else
		std::cout << "BitcoinExchange: \033[31mKO\033[0m" << std::endl;
	return (0);
}
