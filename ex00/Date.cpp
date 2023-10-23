#include "Date.hpp"
#include <cstdlib>

Date::Date(): _day(0), _month(0), _year(0)
{}

Date::Date(const Date &src): _day(src._day), _month(src._month), _year(src._year)
{}

static bool	is_valid_date(unsigned day, unsigned month, unsigned year)
{
	if (year == 0)
		return (0);
	if (day > 31 || month > 12)
		return (0);
	if (day == 31 && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11))
		return (0);
	if (month == 2)
	{
		if ((!(year % 4) && year % 100) || !(year % 400))
		{
			if (day > 29)
				return (0);
		}
		else if (day > 28)
			return (0);
	}
	return (1);
}

Date::Date(unsigned day, unsigned month, unsigned year): _day(day), _month(month), _year(year)
{
	if (!is_valid_date(day, month, year))
		throw InvalidDateException();
	_day = day;
	_month = month;
	_year = year;
}

Date::Date(const std::string &date)
{
	// %F = %Y-%m-%d => 2019-01-01
	if (date.length() != 10)
		throw InvalidDateException();
	if (date[4] != '-' || date[7] != '-')
		throw InvalidDateException();
	_day = atoi(date.substr(8, 2).c_str());
	_month = atoi(date.substr(5, 2).c_str());
	_year = atoi(date.substr(0, 4).c_str());
	if (!is_valid_date(_day, _month, _year))
		throw InvalidDateException();
}

Date::~Date()
{}

Date	&Date::operator=(const Date &src)
{
	if (this == &src)
		return (*this);
	_day = src._day;
	_month = src._month;
	_year = src._year;
	return (*this);
}

bool Date::operator==(const Date &src) const
{
	return (_day == src._day && _month == src._month && _year == src._year);
}

bool Date::operator!=(const Date &src) const
{
	return (!(*this == src));
}

bool Date::operator<(const Date &src) const
{
	if (_year < src._year)
		return (1);
	if (_year > src._year)
		return (0);
	if (_month < src._month)
		return (1);
	if (_month > src._month)
		return (0);
	if (_day < src._day)
		return (1);
	return (0);
}

bool Date::operator<=(const Date &src) const
{
	return ((*this == src) || (*this < src));
}

bool Date::operator>(const Date &src) const
{
	return (!(*this <= src));
}

bool Date::operator>=(const Date &src) const
{
	return ((*this == src) || (*this > src));
}

unsigned Date::getDay() const
{
	return (_day);
}

unsigned Date::getMonth() const
{
	return (_month);
}

unsigned Date::getYear() const
{
	return (_year);
}

const char *Date::InvalidDateException::what() const throw()
{
	return ("Invalid date");
}
