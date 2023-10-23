#include "BitcoinExchange.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src): _rates(src._rates)
{}

static double get_rate(const std::string &rate_str, const std::string &filename, const std::string &line)
{
	char	*endptr;
	double rate;

	errno = 0;
	rate = strtod(rate_str.c_str(), &endptr);
	if (endptr && *endptr)
	{
		std::cerr << "Error: Invalid format in " << "\"" << filename << "\"" << " on line: " << line << std::endl;
		throw BitcoinExchange::ConstructorFailedException();
	}
	if (errno == ERANGE)
	{
		std::cerr << "Error: Invalid format (number out of range) in " << "\"" << filename << "\"" << " on line: " << line << std::endl;
		throw BitcoinExchange::ConstructorFailedException();
	}
	if (rate < 0)
	{
		std::cerr << "Error: Invalid format (need a positive number) in " << "\"" << filename << "\"" << " on line: " << line << std::endl;
		throw BitcoinExchange::ConstructorFailedException();
	}
	return (rate);
}

BitcoinExchange::BitcoinExchange(const std::string &filename)
{
	std::ifstream	file(filename.c_str());
	std::string		line;
	std::string		date;
	std::string		rate;
	size_t			sep;
	Date			d;

	if (!file.is_open())
	{
		std::cerr << "Error: could not open \"" << filename << "\"" << std::endl;
		throw ConstructorFailedException();
	}
	if (!std::getline(file, line))
	{
		std::cerr << "Error: Empty \"" << filename << "\" file" << std::endl;
		throw ConstructorFailedException();
	}
	if (line != "date,exchange_rate")
	{
		std::cerr << "Error: Invalid format in " << "\"" << filename << "\"" << " on first line: " << line << std::endl << "Expected: \"date,exchange_rate\"" << std::endl;
		throw ConstructorFailedException();
	}
	while (std::getline(file, line))
	{
		sep = line.find(',');
		if (line.empty())
			continue ;
		if (sep == std::string::npos)
		{
			std::cerr << "Error: Invalid format in " << "\"" << filename << "\"" << " on line: " << line << std::endl;
			throw ConstructorFailedException();
		}

		date = line.substr(0, sep);
		rate = line.substr(sep + 1);

		if (date.empty() || rate.empty())
		{
			std::cerr << "Error: Invalid format in " << "\"" << filename << "\"" << " on line: " << line << std::endl;
			throw ConstructorFailedException();
		}

		try
		{
			d = Date(date);
			_rates[d] = get_rate(rate, filename, line);
		}
		catch (Date::InvalidDateException &e)
		{
			std::cerr << "Error: Invalid format in " << "\"" << filename << "\"" << " on line: " << line << std::endl;
			throw ConstructorFailedException();
		}
	}
}

BitcoinExchange::~BitcoinExchange()
{}

double BitcoinExchange::getRate(const std::string &date) const
{
	Date	d(date);
	std::map<Date, double>::const_iterator	it = _rates.upper_bound(d);

	if (it == _rates.begin())
	{
		std::cout << "Error: no rate found for " << date << std::endl;
		return (-1.);
	}
	--it;
	return (it->second);
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this == &src)
		return (*this);
	_rates = src._rates;
	return (*this);
}

const char *BitcoinExchange::ConstructorFailedException::what() const throw()
{
	return "BitcoinExchange constructor failed";
}
