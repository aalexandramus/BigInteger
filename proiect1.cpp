// proiect1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "BigInt.h"

int main()
{
	BigInt number(12,10);//hai cu 160*
	BigInt a(100, 10);
	
	std::cout << (number % 10);
	return 0;
	
}
