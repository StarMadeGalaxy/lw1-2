#include "stdafx.h"


int main()
{
	Expression expression;
	Stack* stack_pointer = NULL;	// First node of the linked 
	short menu_choice = 0;

	while (true)		// Main menu loop
	{
		system("CLS");
		
		std::cout << "Reverse Polish notation: "
			<< "\n\n1. Enter the expression in infix notation"
			<< "\n2. Convert to postfix notation"
			<< "\n3. Evaluate a postfix expression"
			<< "\n4. View the expression"
			<< "\n5. Clear memory"
			<< "\nELSE. Exit"
			<< "\n\nType here: ";

		menu_choice = static_cast<short>(number_input(MENU_LIMIT));

		switch (menu_choice)
		{
		case 1:		// enter the equation in infix notation
		{
			system("CLS");

			std::cout << "Type the equation in infix notation: ";

			if (expression.infix.size() != 0 || expression.postfix.size() != 0) {
				expression.infix.clear();
				expression.postfix.clear();
			}

			expression.input_infix();

			std::cout << "\n\nThe equation to be transformed into an postfix notation: ";

			expression.print(expression.infix);

			std::cout << "\n\nPress ENTER to continue...";
			std::cin.get();
			break;
		}
		case 2: // convert into a postfix notation
			system("CLS");

			if (expression.infix.size() == 0) {
				std::cout << "Enter an expression in infix notation and try again.";
			} else {
				hide_cursor();
				std::cout << "Expression '";
				expression.print(expression.infix);
				std::cout << "' is being transformed...";
				expression.infix_to_postfix(&stack_pointer);
				print_loading_field(1, 30);

				std::cout << "\n\nThe expression in postfix notation: ";

				expression.print(expression.postfix);

				std::cout << "\n\nTransformation is completed.";
			}

			std::cout << "\n\nPress ENTER to continue...";
			std::cin.get();
			break;
		case 3:
		{
			system("CLS");

			if (expression.postfix.size() == 0) {
				std::cout << "Postfix expression is empty.";
			} else {
				std::cout << "Expression: ";
				expression.print(expression.infix);
				std::cout << std::endl;
				double evaluation = expression.evaluate_postfix(&stack_pointer);
				switch (expression.error)
				{
				case -1:
					std::cout << "\nERROR: Division by 0.\n";
					expression.error = 0;
					break;
				case -2:
					std::cout << "\nERROR: Division by 0 in power operation.\n";
					expression.error = 0;
					break;
				default:
					std::cout << "\nEvaluation of expression: " << evaluation;
					break;
				}
			}
			std::cout << "\n\nPress ENTER to continue...";
			std::cin.get();
			break;
		}
		case 4:
			system("CLS");

			if (expression.infix.size() == 0) {
				std::cout << "Infix expression is empty.";
			} else {
				std::cout << "The infix expression: ";
				expression.print(expression.infix);
			}	

			if (expression.postfix.size() == 0) {
				std::cout << "\n\nPostifx expression is empty.";
			} else {
				std::cout << "\n\nThe postfix expression: ";
				expression.print(expression.postfix);
			}

			std::cout << "\n\nPress ENTER to continue...";
			std::cin.get();
			break;
		case 5:
		{
			system("CLS");
			
			if (expression.infix.size() == 0) {
				std::cout << "\nInfix expression is already empty.";
			} else {
				expression.infix.clear();
				std::cout << "\nInfix expression is clear.";
			}

			if (expression.postfix.size() == 0) {
				std::cout << "\nPostfix expression is already empty.";
			} else {
				expression.postfix.clear();
				std::cout << "\nPostfix expression is clear.";
			}

			std::cout << "\n\nPress ENTER to continue...";
			std::cin.get();
			break;
		}
		default:
			system("CLS");

			std::cout << "+----------Clear memory before exit.----------+\n";

			if (expression.infix.size() == 0) {
				std::cout << "\nInfix expression is already empty.";
			} else {
				expression.infix.clear();
				std::cout << "\nInfix expression is clear.";
			}

			if (expression.postfix.size() == 0) {
				std::cout << "\nPostfix expression is already empty.";
			} else {
				expression.postfix.clear();
				std::cout << "\nPostfix expression is clear.";
			}

			std::cout << "\n\n+---------------------------------------------+"
				<< "\n\nSee you!\n";
			return 0;
		}
	}
}













