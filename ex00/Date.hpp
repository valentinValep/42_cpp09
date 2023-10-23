#pragma once

#include <string>

class Date
{
private:
	unsigned	_day;
	unsigned	_month;
	unsigned	_year;
public:
	Date();
	Date(const Date &src);
	Date(unsigned day, unsigned month, unsigned year);
	Date(const std::string &date);
	~Date();
	Date	&operator=(const Date &src);

	bool	operator==(const Date &src) const;
	bool	operator!=(const Date &src) const;
	bool	operator<(const Date &src) const;
	bool	operator<=(const Date &src) const;
	bool	operator>(const Date &src) const;
	bool	operator>=(const Date &src) const;

	unsigned	getDay() const;
	unsigned	getMonth() const;
	unsigned	getYear() const;

	class InvalidDateException: public std::exception
	{
	public:
		virtual const char	*what() const throw();
	};
};
