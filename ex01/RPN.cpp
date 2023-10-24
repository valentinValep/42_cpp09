#include <stack>
#include <stdexcept>
#include "RPN.hpp"

RPN::~RPN() {}

RPN &RPN::operator=(const RPN &rhs)
{
	(void)rhs;
	return (*this);
}

RPN::RPN(const RPN &rhs)
{
	(void)rhs;
}

RPN::RPN() {}

int RPN::rpn(std::string str)
{
	std::stack<int> stack;

	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			stack.push(str[i] - '0');
		else if (str[i] == '+')
		{
			if (stack.size() < 2)
				throw std::runtime_error("Error: Invalid expression");
			int a = stack.top();
			stack.pop();
			int b = stack.top();
			stack.pop();
			stack.push(a + b);
		}
		else if (str[i] == '-')
		{
			if (stack.size() < 2)
				throw std::runtime_error("Error: Invalid expression");
			int a = stack.top();
			stack.pop();
			int b = stack.top();
			stack.pop();
			stack.push(b - a);
		}
		else if (str[i] == '*')
		{
			if (stack.size() < 2)
				throw std::runtime_error("Error: Invalid expression");
			int a = stack.top();
			stack.pop();
			int b = stack.top();
			stack.pop();
			stack.push(a * b);
		}
		else if (str[i] == '/')
		{
			if (stack.size() < 2)
				throw std::runtime_error("Error: Invalid expression");
			int a = stack.top();
			stack.pop();
			int b = stack.top();
			stack.pop();
			stack.push(b / a);
		}
		else if (std::isspace(str[i]) == false)
			throw std::runtime_error("Error: Invalid character");
	}
	if (stack.size() != 1)
		throw std::runtime_error("Error: Invalid expression");
	return (stack.top());
}
