#pragma once

#include <string>

class RPN
{
	private :
		RPN();
		RPN(const RPN &rhs);
		RPN& operator=(const RPN &rhs);
		~RPN();
	public :
		static int rpn(std::string str);
};
