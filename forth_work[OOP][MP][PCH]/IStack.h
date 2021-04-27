#pragma once

#ifndef _ISTACK_H_
#define _ISTACK_H_

#include "stdafx.h"


class Stack {
public:
	int64_t element;		// current value of the element in the node
	Stack* lower_node;		// pointer to the lower element

	void push(int64_t value, Stack** head_node);
	int64_t pop(Stack** head_node);
};


#endif // _ISTACK_H_
