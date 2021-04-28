#include "stdafx.h"


void Stack::push(double value, Stack** head_node)
{
	Stack* new_node = new Stack;
	new_node->element = value;
	new_node->lower_node = *head_node;
	*head_node = new_node;
}


double Stack::pop(Stack** head_node)
{
	double element_to_return;

	if (*head_node != NULL) {
		element_to_return = (*head_node)->element;
		Stack* temp_node = (*head_node)->lower_node;
		delete* head_node;
		*head_node = temp_node;
		return element_to_return;
	}
	return NULL;
}