#pragma once

#ifndef _IINPUT_H_
#define _IINPUT_H_

#include "stdafx.h"	


static double number_input(uint8_t limit = INT64_POSITIVE_LENGTH)
{
	// #include <vector>
	// #define INT64_POSITIVE_LENGTH 19		// long long int -9223372036854775808 to 9223372036854775807
	// #include <conio.h>
	// #include <iostream>

	const int8_t size = sizeof(int8_t);

	std::vector<int8_t> number_array;

	int8_t current_limit = 0;
	int8_t c = 0;				// current entered symbol 	
	bool is_negative = false;
	int16_t length = 0;		// length of a number (digit capacity, minus included). Index for digits is [length - 1]
	double number_array_integer = 0;


	while (true) {
		c = _getch();

		if (c > 47 && c < 58 && length < limit) {		//	Allow to enter only digits
			number_array.push_back(c);
			length++;
			number_array_integer *= 10;
			number_array_integer += number_array[length - 1] - 48;
			std::cout << (char)c;
		}
		else if (c == '\b' && length > 0) {	// Backspace
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
		}
		else if (c == 13 && length != 0) {		// Enter breaks down the loop
			if (number_array[0] == '-' && length < 2)/* && !is_vector_outta_ll(number_array)*/ // BETA
				continue;
			break;
		}
		else if (c == 45 && length == 0) {		// Minus for negative number
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

static void hide_cursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

static void move_console_cursor(short x, short y)
{
	COORD position = { x, y };
	HANDLE output_window = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output_window, position);
}

static void print_loading_field(int delay, int end_offset)
{
	int offset = 1;
	std::cout << "\n\n[---------------------]";
	move_console_cursor(0, 1);
	for (int i = 0; i < 101; i++) {
		if (i % 5 == 0) {
			move_console_cursor(offset, 2);
			Sleep(delay);
			std::cout << "#";
			offset++;
		}
		Sleep(delay);
		move_console_cursor(end_offset, 2);
		std::cout << i << '%';
	}
}



#endif	// _IINPUT_H_
