#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

std::string	trim(const std::string &str)
{
	size_t start = str.find_first_not_of(" \n\r\t");
	size_t end = str.find_last_not_of(" \n\r\t");
	if (start == std::string::npos || end == std::string::npos)
		return ("");
	return (str.substr(start, end - start + 1));
}

bool	get_date_value(const std::string &line, std::string &date, std::string &value)
{
	size_t sep = line.find('|');
	static int line_number = 0;

	line_number++;
	if (sep == std::string::npos)
	{
		std::cout << "Error: bad input = > " << line << std::endl;
		return (false);
	}
	date = trim(line.substr(0, sep));
	value = trim(line.substr(sep + 1));
	if (date.empty() || value.empty())
	{
		std::cout << "Error: bad input = > " << line << std::endl;
		return (false);
	}
	if (date == "date" && value == "value" && line_number == 1)
	{
		std::cout << "Error: bad input = > " << line << std::endl;
		return (false);
	}
	return (true);
}

double	get_value(const std::string &value_str)
{
	char	*endptr;
	double value;

	errno = 0;
	value = strtod(value_str.c_str(), &endptr);
	if (endptr && *endptr)
	{
		std::cout << "Error: bad input = > " << value_str << std::endl;
		return (-1.);
	}
	if (errno == ERANGE)
	{
		std::cout << "Error: value out of range" << std::endl;
		return (-1.);
	}
	if (value < 0)
	{
		std::cout << "Error: not a positive number" << std::endl;
		return (-1.);
	}
	if (value > 1000)
	{
		std::cout << "Error: too large number." << std::endl;
		return (-1.);
	}
	return (value);
}

void	exchange_one_line(std::string &line, BitcoinExchange &exchange)
{
	std::string date;
	std::string value_str;
	double value;

	if (!get_date_value(line, date, value_str))
		return ;
	value = get_value(value_str);
	if (value < 0)
		return ;
	try {
		double rate = exchange.getRate(date);
		if (rate < 0)
			return ;
		std::cout << date << " => " << rate << " = " << rate * value << std::endl;
	} catch (const Date::InvalidDateException &e) {
		std::cout << "Error: bad input = > " << date << std::endl;
	}
}

int	get_rates(char *file_name)
{
	std::ifstream file(file_name);
	BitcoinExchange exchange;
	std::string line;

	if (!file.is_open())
	{
		std::cerr << "Error: could not open " << "\"" << file_name << "\"" << std::endl;
		return (1);
	}

	if (!std::getline(file, line))
	{
		std::cerr << "Error: Empty " << "\"" << file_name << "\"" << " file" << std::endl;
		return (1);
	}
	if (line != "date | value")
	{
		std::cerr << "Error: Invalid format in " << "\"" << file_name << "\"" << " on first line: " << line << std::endl << "Expected: \"date | value\"" << std::endl;
		return (1);
	}
	while (std::getline(file, line))
		exchange_one_line(line, exchange);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./btc <file>" << std::endl;
		return (1);
	}
	return (get_rates(argv[1]));
}
