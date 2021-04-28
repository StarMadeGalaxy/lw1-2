#pragma once

#ifndef _ISTACK_H_
#define _ISTACK_H_

#include "stdafx.h"


class Stack {
public:
	double element;		// current value of the element in the node
	Stack* lower_node;		// pointer to the lower element

	void push(double value, Stack** head_node);
	double pop(Stack** head_node);
};


#endif // _ISTACK_H_
