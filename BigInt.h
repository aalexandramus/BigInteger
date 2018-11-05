#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

class BigInt {

public:
	
	BigInt(int number = 0, unsigned char base = 10);
	BigInt(std::string characters, int base = 10);
	BigInt(long long int number, unsigned char base = 10);

	friend BigInt min(const BigInt& first, const BigInt& second);
	friend std::istream & operator>> (std::istream & stream, BigInt &number);
	friend std::ostream & operator<< (std::ostream & stream, const BigInt &number);

	void setBase(unsigned char);
	void setSign(char);
	char getSign() const;
	unsigned char getBase() const;

	BigInt &operator+= (int number);  
	BigInt &operator+= (const BigInt &second); 

	BigInt &operator-= (int number);
	BigInt &operator-= (const BigInt &second); 
	
	BigInt &operator*= (int number); 
	BigInt &operator*= (const BigInt &second);  

	BigInt &operator/= (int number);
	BigInt &operator/= (const  BigInt &second);  
	
	BigInt &operator %=(int number);
	BigInt &operator %=(const BigInt &second); 
	
	friend BigInt operator+ (const BigInt &digits); 
	friend BigInt operator- (const BigInt &digits);

	friend BigInt operator+ (const BigInt &digits1, const BigInt &digits2);
	friend BigInt operator+ (const BigInt &digits, int number);
	friend BigInt operator+ (int number, const BigInt &digits);

	friend BigInt operator- (const BigInt &digits1, const BigInt &digits2);
	friend BigInt operator- (const BigInt &digits, int number);
	friend BigInt operator- (int number, const BigInt &digits);

	friend BigInt operator* (const BigInt &digits1, const BigInt &digits2);
	friend BigInt operator* (const BigInt &digits, int number);
	friend BigInt operator* (int number, const BigInt &digits);

	friend BigInt operator %(const BigInt &digits1, const BigInt &digits2);
	friend BigInt operator% (const BigInt &digits, int number);
	friend BigInt operator% (int number, const BigInt &digits);  

	friend BigInt operator/ (const BigInt &digits1, const BigInt &digits2);
	friend BigInt operator/ (const BigInt &digits, int number);
	friend BigInt operator/ (int number, const BigInt &digits);

	friend BigInt operator^ (const BigInt &base, int exponent);

	friend bool operator== (const BigInt &digits1,const BigInt &digits2);
	friend bool operator== (const BigInt &digits, int number);
	friend bool operator== (int number, const BigInt &digits);

	friend bool operator!= (const BigInt &digits1, const BigInt &digits2);
	friend bool operator!= (const BigInt &digits, int number);
	friend bool operator!= (int number, const BigInt &digits);

	friend bool operator< (const BigInt &digits1, const BigInt &digits2);
	friend bool operator< (const BigInt &digits, int number);
	friend bool operator< (int number, const BigInt &digits);

	friend bool operator<= (const BigInt &digits1, const BigInt &digits2);
	friend bool operator<= (const BigInt &digits, int number);
	friend bool operator<= (int number, const BigInt &digits);

	friend bool operator> (const BigInt &digits1, const BigInt &digits2);
	friend bool operator> (const BigInt &digits, int number);
	friend bool operator> (int number, const BigInt &digits);

	friend bool operator>= (const BigInt &digits1, const BigInt &digits2);
	friend bool operator>= (const BigInt &digits, int number);  
	friend bool operator>= (int number, const BigInt &digits); 


private:
	std::vector<unsigned char> m_digits;
	unsigned char m_base;
	char m_sign;
	
};