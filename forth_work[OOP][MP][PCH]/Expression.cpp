#include "stdafx.h"


void Expression::input_infix()
{
	int opening_parenthesis_amount = 0;
	int closing_parenthesis_amount = 0;
	int operandes_amount = 0;
	int length = 0;
	char c = 0;

	while (true)
	{
		c = _getch();

		char previous_symbol = length != 0 ? infix[length - 1] : NULL;

		if (is_operand(c) && !is_operand(previous_symbol) && previous_symbol != ')') {
			infix.push_back(c);
			std::cout << (char)c;
			length++;
			operandes_amount++;
		} else if (is_operator(c) && length != 0 && !is_operator(previous_symbol) && previous_symbol != '(') {
			infix.push_back(c);
			std::cout << (char)c;
			length++;
		} else if (c == '(' && previous_symbol != ')' && !is_operand(previous_symbol)) {
			infix.push_back(c);
			std::cout << (char)c;
			opening_parenthesis_amount++;
			length++;
		} else if (c == ')' && opening_parenthesis_amount != closing_parenthesis_amount && !is_operator(previous_symbol) && previous_symbol != '(') {
			infix.push_back(c);
			std::cout << (char)c;
			closing_parenthesis_amount++;
			length++;
		} else if (c == '\b' && length != 0) {	// Backspace
			if (previous_symbol == '(')
				opening_parenthesis_amount--;
			else if (previous_symbol == ')')
				closing_parenthesis_amount--;
			else if (is_operand(previous_symbol))
				operandes_amount--;

			infix.pop_back();
			length--;
			std::cout << "\b \b";
		} else if (c == 13 && operandes_amount != 0 && opening_parenthesis_amount == closing_parenthesis_amount && !is_operator(previous_symbol)
			&& previous_symbol != '^') {
			break;
		}
	}
}


void Expression::infix_to_postfix(Stack** stack_pointer)
{
	Stack stack;

	for (size_t i = 0; i < infix.size(); i++)
	{
		char infix_symbol = infix[i];
		if (is_operand(infix_symbol)) {
			postfix.push_back(infix_symbol);
		} else if (is_operator(infix_symbol)) {
			while (*stack_pointer != NULL && (*stack_pointer)->element != '('
				&& precedence_comparsion(static_cast<char>((*stack_pointer)->element), static_cast<char>(infix_symbol))) {
				postfix.push_back(stack.pop(stack_pointer));
			}
			stack.push(infix_symbol, stack_pointer);
		} else if (infix_symbol == '(') {
			stack.push(infix_symbol, stack_pointer);
		} else if (infix_symbol == ')') {
			while (*stack_pointer != NULL && (*stack_pointer)->element != '(') {
				postfix.push_back(stack.pop(stack_pointer));
			}
			stack.pop(stack_pointer);	// pop '(', cause loop stops when ('s met 
		}
	}

	while (*stack_pointer != NULL) {
		postfix.push_back(stack.pop(stack_pointer));
	}
}


double Expression::evaluate_postfix(Stack** stack_pointer)
{
	Stack stack;

	std::vector<double> variable_values(0);

	for (size_t i = 0; i < postfix.size(); i++)
	{
		// 0   1   2   3    4  5
		// a, 302, b, 5314, c, 1
		char current_symbol = postfix[i];

		if (is_operand(current_symbol)) {
			bool skip = false;

			for (size_t i = 0; i < variable_values.size(); i += 2) {
				if (current_symbol == variable_values[i]) {
					std::cout << "\nDuplicate operand: '" << current_symbol << "' with value " << variable_values[i + 1] << std::endl;
					stack.push(variable_values[i + 1], stack_pointer);
					skip = true;
					break;
				}
			}
			if (!skip) {
				std::cout << "\nEnter the value of '" << current_symbol << "': ";
				double value = number_input(4);
				variable_values.push_back(current_symbol);
				variable_values.push_back(value);
				stack.push(value, stack_pointer);
				std::cout << std::endl;
			}
		}
		else {
			double first_value = stack.pop(stack_pointer);
			double second_value = stack.pop(stack_pointer);

			switch (current_symbol)
			{
			case '+':
				stack.push(second_value + first_value, stack_pointer);
				break;
			case '/':
				if (first_value == 0) {
					error = -1;
					return NULL;
				}
				stack.push(second_value / first_value, stack_pointer);
				break;
			case '*':
				stack.push(second_value * first_value, stack_pointer);
				break;
			case '^':
			{
				if (second_value == 0 && first_value < 0) {
					error = -2;
					return NULL;
				}
				stack.push(static_cast<int64_t>(powl(static_cast<long double>(second_value), static_cast<long double>(first_value))), stack_pointer);
				break;
			}
			case '-':
				stack.push(second_value - first_value, stack_pointer);
				break;
			}
		}

	}
	return stack.pop(stack_pointer);
}


void Expression::print(std::vector<char> vector)
{
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << vector[i];
}


bool Expression::precedence_comparsion(char true_symbol, char false_symbol)
{
	// Returns true if true_symbol precedence is greaten than false_symbol precedence

	short true_precedence = 0;
	short false_precedence = 0;

	if (true_symbol == '^')
		true_precedence = 3;
	else if (true_symbol == '/' || true_symbol == '*')
		true_precedence = 2;
	else if (true_symbol == '+' || true_symbol == '-')
		true_precedence = 1;
	else
		true_precedence = 0;

	if (false_symbol == '^')
		false_precedence = 3;
	else if (false_symbol == '/' || false_symbol == '*')
		false_precedence = 2;
	else if (false_symbol == '+' || false_symbol == '-')
		false_precedence = 1;
	else
		false_precedence = 0;

	if (true_precedence >= false_precedence)
		return true;
	else
		return false;

}


bool Expression::is_operand(char symbol)
{
	if ((symbol >= 65 && symbol <= 90) ||
		(symbol >= 97 && symbol <= 122))
		return true;
	else
		return false;
}


bool Expression::is_operator(char symbol)
{
	if (symbol == '+' || symbol == '-' ||
		symbol == '*' || symbol == '/' ||
		symbol == '^')
		return true;
	return false;
}