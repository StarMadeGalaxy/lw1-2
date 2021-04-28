#pragma once

#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "stdafx.h"


class Expression
{
private:
	bool precedence_comparsion(char true_symbol, char false_symbol);
	bool is_operand(char symbol);
	bool is_operator(char symbol);
public:
	std::vector<char> infix;
	std::vector<char> postfix;
	int error = 0;

	void input_infix();
	void infix_to_postfix(Stack** stack_pointer);
	double evaluate_postfix(Stack** stack_pointer);
	void print(std::vector<char> vector);
};


#endif // _EXPRESSION_H_
