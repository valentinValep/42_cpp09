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

	BitcoinExchange(const BitcoinExchange &src);
	BitcoinExchange	&operator=(const BitcoinExchange &src);
public:
	BitcoinExchange();
	~BitcoinExchange();

	double	getRate(const std::string &date) const;
};
