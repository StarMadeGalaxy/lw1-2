//cout << sqrt(1 + sqrt(2 + sqrt(3 + sqrt(4 + sqrt(5 + sqrt(6)))))) << endl;


#define SIZE 1000
#define UNLIMITED -1


#include <iostream>
#include <conio.h>


using namespace std;


long long int number_input(int limit);
long double recursive_function(long long int n, long long int a);
long double common_function(long long int n);


int main(void)
{
	cout << "Enter 'n' : ";
	long long int n = number_input(UNLIMITED);
	cout << "\n----------RECURSIVE---------" 
		<< "\nThe answer for the example 'sqrt(1 + sqrt(2 + ... + sqrt(n)))' with 'n' = " << n << " is ";
	cout << recursive_function(n, 0) << endl;
	cout << "-------NOT RECURSIVE---------"
		<< "\nThe answer for the example 'sqrt(1 + sqrt(2 + ... + sqrt(n)))' with 'n' = " << n << " is ";
	cout << common_function(n) << endl;
	return 0;
}


long double common_function(long long int n)
{
	long double result = sqrt(n);
	while (n != 0) { result = sqrt(n-- + result); }
	return result;
}


long double recursive_function(long long int n, long long int a)
{
	if (a == n) { return sqrt(n); }
	else { return sqrt(a + recursive_function(n, ++a)); }
}


long long int number_input(int limit)
{
	// Functions takes restrict to enter anything, but digits.
	// We can get only positive numbers. The 'limit' is referred to as digit capacity.
	// If the limit is equal to -1, the limit is the size of an array.
	char c;
	char string[SIZE];
	long long int result = 0;
	int length = 0;


	for (;;) {
		c = _getch();
		if (c == 13 && length != 0) { break; }
		if (c == '\b' && length != 0) {
			cout << "\b \b";
			length--;
			continue;
		} if (c < 48 || c > 57) { continue; }
		if (limit == -1) {
			if (length < SIZE) {
				cout << (int)c - 48;
				string[length] = c;
				length++;
			}
			else { continue; }
		}
		else if (length < limit) {
			cout << (int)c - 48;
			string[length] = c;
			length++;
		}
	} for (int j = 0; j < length; j++) {
		result *= 10;
		result += (int)string[j] - 48;
	}

	return result;
}
