#include "BitcoinExchange.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

BitcoinExchange::BitcoinExchange()
{
	std::ifstream	file("data.csv");
	std::string		line;
	std::string		date;
	std::string		rate;
	size_t			sep;
	Date			d;

	if (!file.is_open())
	{
		std::cerr << "Error: could not open \"data.csv\"" << std::endl;
		exit(1);
	}
	if (!std::getline(file, line))
	{
		std::cerr << "Error: Empty \"data.csv\" file" << std::endl;
		exit(1);
	}
	if (line != "date,exchange_rate")
	{
		std::cerr << "Error: Invalid format in " << "\"data.csv\"" << " on first line: " << line << std::endl << "Expected: \"date,exchange_rate\"" << std::endl;
		exit(1);
	}
	while (std::getline(file, line))
	{
		sep = line.find(',');
		if (sep == std::string::npos)
			continue ; // skip this line (invalid format)

		date = line.substr(0, sep);
		rate = line.substr(sep + 1);

		if (date.empty() || rate.empty())
			continue ; // skip this line (invalid format)

		try
		{
			d = Date(date);
			_rates[d] = strtod(rate.c_str(), NULL);
		}
		catch (Date::InvalidDateException &e)
		{
			std::cerr << "Error: Invalid format in " << "\"data.csv\"" << " on line: " << line << std::endl;
			exit(1);
		}
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src): _rates(src._rates)
{}

BitcoinExchange::~BitcoinExchange()
{}

double BitcoinExchange::getRate(const std::string &date) const
{
	Date	d(date);
	std::map<Date, double>::const_iterator	it = _rates.upper_bound(d);

	if (it == _rates.begin())
	{
		std::cerr << "Error: no rate found for " << date << std::endl;
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
