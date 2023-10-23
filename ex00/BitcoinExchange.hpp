#pragma once

#include "Date.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

class BitcoinExchange
{
private:
	std::map<Date, double>	_rates;

	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &src);
	BitcoinExchange	&operator=(const BitcoinExchange &src);
public:
	BitcoinExchange(const std::string &filename);
	~BitcoinExchange();

	double	getRate(const std::string &date) const;

	class ConstructorFailedException: public std::exception
	{
	public:
		virtual const char	*what() const throw();
	};
};
