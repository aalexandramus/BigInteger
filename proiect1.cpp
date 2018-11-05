// proiect1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "BigInt.h"

int main()
{
	BigInt number(12,10);
	BigInt a(2, 10);
	BigInt b;
	number /= a;
	BigInt ob1(543, 10);
	BigInt ob2;
	try
	{
		ob1 /= ob2;
		std::cout << ob1;
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what();
		exit(0);
	}

	
	std::cout << (number /a);
	return 0;
	
}
