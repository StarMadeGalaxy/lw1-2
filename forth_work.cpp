//#pragma warning( disable : 28182 )
//#pragma warning( disable : 4715 )
#pragma warning( disable : 4244 )
//#pragma warning( disable : 6308 )
//#pragma warning( disable : 6011 )


#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <windows.h>


using namespace std;

#define MENU_LIMIT 1
#define INT64_POSITIVE_LENGTH 19		// long long int -9223372036854775808 to 9223372036854775807


struct Node {
	int64_t element;		// current value of the element in the node
	Node* lower_node;		// pointer to the lower element
};


void infix_to_postfix(vector<char>& infix_expression, vector<char>& postfix_expression, Node** stack_pointer);
int64_t evaluate_postfix(vector<char> postfix_expression, Node** stack_pointer, int& error_flag);
bool precedence_comparsion(char true_symbol, char false_symbol);
int64_t number_input(uint8_t limit = INT64_POSITIVE_LENGTH);
void expression_input(vector<char>& expression_string);
void print_loading_field(int delay, int end_offset);
void push(int64_t value, Node** head_node);
void move_console_cursor(short x, short y);
void vector_print(vector<char> vector);
bool is_operator(char symbol);
int64_t pop(Node** head_node);
bool is_operand(char symbol);
void hide_cursor();


int main()
{
	
	vector<char> postfix_expression(0);
	vector<char> infix_expression(0);
	Node* stack_pointer = NULL;	// First node of the linked 
	short menu_choice = 0;

	while (true)		// Main menu loop
	{
		system("CLS");
		
		cout << "Reverse Polish notation: "
			<< "\n\n1. Enter the expression in infix notation"
			<< "\n2. Convert to postfix notation"
			<< "\n3. Evaluate a postfix expression"
			<< "\n4. View the expression"
			<< "\n5. Clear memory"
			<< "\nELSE. Exit"
			<< "\n\nType here: ";

		menu_choice = number_input(MENU_LIMIT);

		switch (menu_choice)
		{
		case 1:		// enter the equation in infix notation
		{
			system("CLS");

			cout << "Type the equation in infix notation: ";

			if (infix_expression.size() != 0 || postfix_expression.size() != 0) {
				infix_expression.clear();
				postfix_expression.clear();
			}

			expression_input(infix_expression);

			cout << "\n\nThe equation to be transformed into an postfix notation: ";

			vector_print(infix_expression);

			cout << "\n\nPress ENTER to continue...";
			cin.get();
			break;
		}
		case 2: // convert into a postfix notation
			system("CLS");

			if (infix_expression.size() == 0) {
				cout << "Enter an expression in infix notation and try again.";
			} else {
				hide_cursor();
				cout << "Expressing is being transformed...";
				infix_to_postfix(infix_expression, postfix_expression, &stack_pointer);
				print_loading_field(1, 30);

				cout << "\n\nThe expression in postfix notation: ";

				vector_print(postfix_expression);

				cout << "\n\nTransformation is completed.";
			}

			cout << "\n\nPress ENTER to continue...";
			cin.get();
			break;
		case 3:
		{
			system("CLS");

			if (postfix_expression.size() == 0) {
				cout << "Postfix expression is empty.";
			} else {
				int error_flag = 0;
				cout << "Expression: ";
				vector_print(infix_expression);
				cout << endl;
				long long int evaluation = evaluate_postfix(postfix_expression, &stack_pointer, error_flag);
				switch (error_flag)
				{
				case -1:
					cout << "\nERROR: Division by 0.\n";
					break;
				case -2:
					cout << "\nERROR: Division by 0 in power operation.\n";
					break;
				default:
					cout << "\nEvaluation of expression: " << evaluation;
					break;
				}
			}
			cout << "\n\nPress ENTER to continue...";
			cin.get();
			break;
		}
		case 4:
			system("CLS");

			if (infix_expression.size() == 0) {
				cout << "Infix expression is empty.";
			} else {
				cout << "The infix expression: ";

				vector_print(infix_expression);
			}	

			if (postfix_expression.size() == 0) {
				cout << "\n\nPostifx expression is empty.";
			}
			else {
				cout << "\n\nThe postfix expression: ";

				vector_print(postfix_expression);
			}

			cout << "\n\nPress ENTER to continue...";
			cin.get();
			break;
		case 5:
		{
			system("CLS");
			
			if (infix_expression.size() == 0) {
				cout << "\nInfix expression is already empty.";
			} else {
				infix_expression.clear();
				cout << "\nInfix expression is clear.";
			}

			if (postfix_expression.size() == 0) {
				cout << "\nPostfix expression is already empty.";
			} else {
				postfix_expression.clear();
				cout << "\nPostfix expression is clear.";
			}

			cout << "\n\nPress ENTER to continue...";
			cin.get();
			break;
		}
		default:
			system("CLS");

			cout << "+----------Clear memory before exit.----------+\n";

			if (infix_expression.size() == 0) {
				cout << "\nInfix expression is already empty.";
			} else {
				infix_expression.clear();
				cout << "\nInfix expression is clear.";
			}

			if (postfix_expression.size() == 0) {
				cout << "\nPostfix expression is already empty.";
			} else {
				postfix_expression.clear();
				cout << "\nPostfix expression is clear.";
			}

			cout << "\n\n+---------------------------------------------+"
				<< "\n\nSee you!\n";
			return 0;
		}
	}
}

//SOME INTERESTING STUFF=------------------------------

void vector_print(vector<char> vector)
{
	for (size_t i = 0; i < vector.size(); i++)
		cout << vector[i];
}


void hide_cursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}


void print_loading_field(int delay, int end_offset) 
{
	int offset = 1;
	printf("\n\n[---------------------]");
	move_console_cursor(0, 1);
	for (int i = 0; i < 101; i++) {
		if (i % 5 == 0) {
			move_console_cursor(offset, 2);
			Sleep(delay);
			cout << "#";
			offset++;
		}
		Sleep(delay);
		move_console_cursor(end_offset, 2);
		cout << i;
		cout << '%';
	}
}


void move_console_cursor(short x, short y)
{
	COORD position = { x, y };
	HANDLE output_window = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output_window, position);
}


int64_t number_input(uint8_t limit)
{
	// #include <vector>
	// #define INT64_POSITIVE_LENGTH 19		// long long int -9223372036854775808 to 9223372036854775807
	// #include <conio.h>
	// #include <iostream>


	const int8_t size = sizeof(int8_t);

	vector<int8_t> number_array;

	int8_t current_limit = 0;
	int8_t c = 0;				// current entered symbol 	
	bool is_negative = false;
	int16_t length = 0;		// length of a number (digit capacity, minus included). Index for digits is [length - 1]
	int64_t number_array_integer = 0;


	while (true) {
		c = _getch();

		if (c > 47 && c < 58 && length < limit) {		//	Allow to enter only digits
			number_array.push_back(c);
			length++;
			number_array_integer *= 10;
			number_array_integer += number_array[length - 1] - 48;
			std::cout << (char)c;
		} else if (c == '\b' && length > 0) {	// Backspace
			if (c == 45) {
				is_negative = false;
				limit--;
			}

			if (length == 1)
				number_array_integer = 0;
			else
				number_array_integer /= 10;	// f.e. (34) -> ('\b') -> (34 / 10) -> (new 34 is 3)

			number_array.erase(number_array.begin() + --length);
			std::cout << "\b \b";
		} else if (c == 13 && length != 0) {		// Enter breaks down the loop
			if (number_array[0] == '-' && length < 2)/* && !is_vector_outta_ll(number_array)*/
				continue;
			break;
		} else if (c == 45 && length == 0) {		// Minus for negative number
			number_array.push_back(c);
			is_negative = true;
			limit++;
			length++;
			std::cout << (char)c;
		}
	}

	if (is_negative)
		return -1 * number_array_integer;
	return number_array_integer;
}


bool precedence_comparsion(char true_symbol, char false_symbol)
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


void infix_to_postfix(vector<char>& infix_expression, vector<char>& postfix_expression, Node** stack_pointer)
{
	for (size_t i = 0; i < infix_expression.size(); i++)
	{
		char infix_symbol = infix_expression[i];
		if (is_operand(infix_symbol)) {
			postfix_expression.push_back(infix_symbol);
		} else if (is_operator(infix_symbol)) {
			while (*stack_pointer != NULL && (*stack_pointer)->element != '('
				&& precedence_comparsion((*stack_pointer)->element, infix_symbol)) {
				postfix_expression.push_back(pop(stack_pointer));
			}
			push(infix_symbol, stack_pointer);
		} else if (infix_symbol == '(') {
			push(infix_symbol, stack_pointer);
		} else if (infix_symbol == ')') {
			while (*stack_pointer != NULL && (*stack_pointer)->element != '(') {
				postfix_expression.push_back(pop(stack_pointer));
			}
			pop(stack_pointer);	// pop '(', cause loop stops when ('s met 
		}
	}

	while (*stack_pointer != NULL) {
		postfix_expression.push_back(pop(stack_pointer));
	}
}


int64_t evaluate_postfix(vector<char> postfix_expression, Node** stack_pointer, int& error_flag)
{
	vector<int64_t> variable_values(0);

	for (size_t i = 0; i < postfix_expression.size(); i++)
	{
		// 0   1   2   3    4  5
		// a, 302, b, 5314, c, 1
		char current_symbol = postfix_expression[i];

		if (is_operand(current_symbol)) {
			bool skip = false;

			for (size_t i = 0; i < variable_values.size(); i += 2) {
				if (current_symbol == variable_values[i]) {
					cout << "\nDuplicate operand: '" << current_symbol << "' with value " << variable_values[i + 1] << endl;
					push(variable_values[i + 1], stack_pointer);
					skip = true;
					break;
				}
			}

			if (!skip) {
				cout << "\nEnter the value of '" << current_symbol << "': ";
				long long int value = number_input(4);
				variable_values.push_back(current_symbol);
				variable_values.push_back(value);
				push(value, stack_pointer);
				cout << endl;
			}
		} else {
			int64_t first_value = pop(stack_pointer);
			int64_t second_value = pop(stack_pointer);

			switch (current_symbol)
			{
			case '+':
				push(second_value + first_value, stack_pointer);
				break;
			case '/':
				if (first_value == 0) {
					error_flag = -1;
					return NULL;
				}
				push(second_value / first_value, stack_pointer);
				break;
			case '*':
				push(second_value * first_value, stack_pointer);
				break;
			case '^':
			{
				if (second_value == 0 && first_value < 0) {
					error_flag = -2;
					return NULL;
				}
				push(powl(second_value, first_value), stack_pointer);
				break;
			}
			case '-':
				push(second_value - first_value, stack_pointer);
				break;
			}
		}

	}
	return pop(stack_pointer);
}


bool is_operand(char symbol)
{
	if ((symbol >= 65 && symbol <= 90) ||
		(symbol >= 97 && symbol <= 122))
		return true;
	else
		return false;
}


bool is_operator(char symbol)
{
	if (symbol == '+' || symbol == '-' ||
		symbol == '*' || symbol == '/' ||
		symbol == '^')
		return true;
	return false;
}


void expression_input(vector<char>& expression_string)
{
	int opening_parenthesis_amount = 0;
	int closing_parenthesis_amount = 0;
	int operandes_amount = 0;
	int length = 0;
	char c = 0;

	while (true)
	{
		c = _getch();

		char previous_symbol = length != 0 ? expression_string[length - 1] : NULL;

		if (is_operand(c) && !is_operand(previous_symbol) && previous_symbol != ')') {
			expression_string.push_back(c);
			std::cout << (char)c;
			length++;
			operandes_amount++;
		}
		else if (is_operator(c) && length != 0 && !is_operator(previous_symbol) && previous_symbol != '(') {
			expression_string.push_back(c);
			cout << (char)c;
			length++;
		}
		else if (c == '(' && previous_symbol != ')' && !is_operand(previous_symbol)) {
			expression_string.push_back(c);
			std::cout << (char)c;
			opening_parenthesis_amount++;
			length++;
		}
		else if (c == ')' && opening_parenthesis_amount != closing_parenthesis_amount && !is_operator(previous_symbol) && previous_symbol != '(') {
			expression_string.push_back(c);
			std::cout << (char)c;
			closing_parenthesis_amount++;
			length++;
		}
		else if (c == '\b' && length != 0) {	// Backspace
			if (previous_symbol == '(')
				opening_parenthesis_amount--;
			else if (previous_symbol == ')')
				closing_parenthesis_amount--;
			else if (is_operand(previous_symbol))
				operandes_amount--;

			expression_string.pop_back();
			length--;
			std::cout << "\b \b";
		}
		else if (c == 13 && operandes_amount != 0 && opening_parenthesis_amount == closing_parenthesis_amount && !is_operator(previous_symbol)
			&& previous_symbol != '^') {
			break;
		}
	}
}


void push(int64_t value, Node** head_node)
{
	Node* new_node = new Node;
	new_node->element = value;
	new_node->lower_node = *head_node;
	*head_node = new_node;
}


int64_t pop(Node** head_node)
{
	int64_t element_to_return;

	if (*head_node != NULL) {
		element_to_return = (*head_node)->element;
		Node* temp_node = (*head_node)->lower_node;
		delete* head_node;
		*head_node = temp_node;
		return element_to_return;
	}
	return NULL;
}
