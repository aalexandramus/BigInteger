#include "pch.h"
#include "BigInt.h"


BigInt::BigInt(int number, unsigned char base)
	: m_base(base)
{

	int digit;
	bool isNegative = false;
	if (number < 0)
	{
		isNegative = true;
		number = number * (-1);
	}

	if (number == 0)
	m_digits.push_back(0);

	while (number != 0)
	{
		digit = number % 10;
		m_digits.push_back(digit);
		number = number / 10;
	}


	if (isNegative == true)
		m_sign = '-';
	else
		m_sign = '+';
}

BigInt::BigInt(std::string characters, int base)
	:m_base(base)
{
	try {
		for (unsigned int i = 0; i < characters.length(); i++)
			if (isdigit(characters.at(i)) == 0 && characters.at(0) != '-')
				throw 0;
	}
	catch (...) {
		std::cout << "The string should be a number";
		exit(0);
	}

	int offSet = 0;

	if (characters.at(0) == '-')
	{

		offSet = 1;
		m_sign = '-';
	}
	else m_sign = '+';

	for (int i = characters.length() - 1; i >= offSet; i--)
		m_digits.push_back(characters.at(i) - '0');

}

BigInt::BigInt(long long int number, unsigned char base)
	: m_base(base)
{
	char digit;
	int c = 0, zeros = 0;
	bool isNegative = false;
	if (number < 0)
	{
		isNegative = true;
		number = number * (-1);

	}

	while (number != 0)
	{
		digit = number % (int)m_base;
		m_digits.push_back(digit);
		number = number / (int)m_base;
		c++;
	}


	if (isNegative == true)
		m_sign = '-';
	else
		m_sign = '+';
}


void BigInt::setBase(unsigned char base)
{
	m_base = base;
}

void BigInt::setSign(char sign)
{
	m_sign = sign;
}

char BigInt::getSign() const
{
	return m_sign;
}

unsigned char BigInt::getBase() const
{
	return m_base;
}

BigInt min(const BigInt& first, const BigInt& second)
{
	if (first.m_digits.size() < second.m_digits.size())
		return first;
	if (second.m_digits.size() < first.m_digits.size())
		return second;
	for (int i = first.m_digits.size() - 1; i >= 0; i--)
		if (first.m_digits.at(i) < second.m_digits.at(i))
			return first;
	return second;
}

BigInt & BigInt::operator+=(int number)
{

	if (number == 0)
		return *this;

	BigInt numberAsBigInt; 

	numberAsBigInt.m_digits.clear();

	if (number < 0)
		numberAsBigInt.m_sign = '-';
	else
		numberAsBigInt.m_sign = '+';

	if (number < 0)
		number *= (-1);

	int  digit;
	
	while (number != 0) 
	{
		digit = number % 10;	
		numberAsBigInt.m_digits.push_back(digit);		
		number = number / 10;
	}
	*this += numberAsBigInt; 
	return *this; 
}

BigInt &BigInt::operator+=(const BigInt &second)
{
	int carry = 0, added, i;
	BigInt minNumber = min(*this, second);
	BigInt maxNumber;
	if (minNumber == second)                      //calculez mixamul dintre cele doua  pt a le aduce la ac. dimendiune cu 0s
		maxNumber = *this;
	else
		maxNumber = second;
	int minSize = minNumber.m_digits.size();
	int maxSize = maxNumber.m_digits.size(); //pun dimensiunile in min si max
	m_digits.clear();
	if (m_sign == second.m_sign)
	{
		if (m_digits.size() != second.m_digits.size())
		{
			for (i = minSize; i < maxSize; i++)
				minNumber.m_digits.push_back(0);                 //aduc la aceeasi dim punand 0
		}
		for (i = 0; i < maxSize; i++)
		{
			added = (minNumber.m_digits[i]) + (maxNumber.m_digits[i]) + carry;
			carry = 0;
			m_digits.push_back(added % 10);
			if (added >= 10)
				carry = added / 10;                  //tinem unul in minte
		}
		if (carry)
			m_digits.push_back(carry);             //cand ramane un nr, il pun in fata
		m_sign = maxNumber.m_sign;                    //daca au amandoua minus, pun semnul la final
		return *this;
	}

	if (getSign() != second.getSign())
	{
		m_sign = maxNumber.m_sign;

		carry = 0;
		for (int i = 0; i < minSize; i++)
		{
			added = (maxNumber.m_digits[i]) - (minNumber.m_digits[i]) - carry;
			if (added < 0)
			{
				added = added + 10;
				carry = 1;
			}
			else
				carry = 0;
			m_digits.push_back(added);
		}

		for (int i = minSize; i < maxSize; i++)
		{
			added = (maxNumber.m_digits[i]) - carry;
			if (added < 0)
			{
				added = added + 10;
				carry = 1;
			}
			else
				carry = 0;

			m_digits.push_back(added);
		}
	}
	while (m_digits.size() > 1)
	{
		if (m_digits[m_digits.size() - 1] == 0)
			m_digits.pop_back();
		else
			break;
	}
	return *this;
}


BigInt & BigInt::operator-=(int number)
{
	number *= (-1);
	return (*this += number);
}

BigInt & BigInt::operator-=(const BigInt & second)
{	
	return (*this += (-second));
}

BigInt & BigInt::operator*=(int number)
{
	int carry = 0, k, numDigits = 0, copyNumber = number;// product == product of num and one digit + carry
	int product;
	while (copyNumber != 0)
	{
		numDigits++;
		copyNumber /= 10;
	}

	int length = numDigits;

	if (0 == number)              // treat zero as special case and stop
	{
		*this = 0;
		return *this;
	}

	if (m_base < number || number < 0)        // handle pre-condition failure
	{
		*this *= BigInt(number);
		return *this;
	}
	
	if (1 == number)              // treat one as special case, no work
	{
		return *this;
	}

	for (k = 0; k < length; k++)     // once for each digit
	{
		product = number * (m_digits.at(k)) + carry;
		carry = product / m_base;
		m_digits.at(k) = product % m_base;
	}

	while (carry != 0)         // carry all digits
	{
		m_digits.at(m_digits.size()) =  carry % m_base;
		
		carry /= m_base;
	}
	return *this;
}

BigInt & BigInt::operator*=(const BigInt & second)
{

	if (m_sign != second.m_sign)
	{
		m_sign = '-';
	}
	else
	{
		m_sign = '+';
	}

	BigInt first(*this);                        // copia lui this
	BigInt sum;                             
	int k;
	int length = second.m_digits.size();                 

	for (k = 0; k < length; k++)
	{
		sum += first * second.m_digits.at(k);          // inmultire cu cifra k
		first *= 10;                           // adauga un 0
	}
	*this = sum;
	return *this;
}

BigInt & BigInt::operator/=(int number)
{
	if (number == 0)
		throw std::runtime_error("Impartire la 0.");
	int divisor = number;
	BigInt numberAsBigInt;
	numberAsBigInt.m_digits.clear();
	if (number > 0)
		numberAsBigInt.m_sign = '+';
	else numberAsBigInt.m_sign = '-';
	if (number < 0) number = std::abs(number);
	while (number != 0)
	{
		numberAsBigInt.m_digits.push_back((number % 10) + '0');
		number = number / 10;
	}
	if (numberAsBigInt > *this)
	{
		m_digits.clear();
		m_digits.push_back('0');
		return *this;
	}

	if (m_sign == numberAsBigInt.m_sign)
		m_sign = '+';
	else m_sign = '-';

	std::vector<int> result;
	unsigned int idx = m_digits.size() - 1;
	int temp = m_digits.at(idx);
	while (temp < divisor)
		temp = temp * 10 + (m_digits.at(--idx));
	while (m_digits.size() > idx)
	{
		result.push_back((temp / divisor));
		temp = (temp % divisor) * 10 + m_digits.at(--idx);
	}

	m_digits.clear();
	for (unsigned int i = 0; i < result.size(); i++)
		m_digits.push_back(result.at(i));
	return *this;
}

bool operator==(const BigInt &first, const BigInt &second)
{
	if (first.getSign() != second.getSign() || first.m_digits.size() != second.m_digits.size())
		return false;
	for (unsigned int i = 0; i < first.m_digits.size(); i++)
		if (first.m_digits[i] != second.m_digits[i])
			return false;
	return true;
}

bool operator==(const BigInt & digits, int number)
{
	int copyNumber = number;
	char m_signNumber;
	if (number < 0)
		m_signNumber = '-';
	else
		m_signNumber = '+';

	if (digits.m_sign != m_signNumber)
		return false;
	int digitsOfNumber = 0;
	while (copyNumber != 0)
	{
		digitsOfNumber++;
		copyNumber /= 10;
		}
	if (digits.m_digits.size() != digitsOfNumber)
		return false;
	for (int i = digits.m_digits.size() - 1; i >= 0; i--)
	{
		if (digits.m_digits.at(i) != (number % 10))
			return false;
			number = number / 10;
	}
	return true;
		
}

bool operator==(int number, const BigInt & digits)
{
	int copyNumber = number;
	char m_signNumber;
	if (number < 0)
		m_signNumber = '-';
	else
		m_signNumber = '+';

	if (digits.m_sign != m_signNumber)
		return false;
	int digitsOfNumber = 0;
	while (copyNumber != 0)
	{
		digitsOfNumber++;
		copyNumber /= 10;
	}
	if (digits.m_digits.size() != digitsOfNumber)
		return false;
	for (int i = digits.m_digits.size() - 1; i >= 0; i--)
	{
		if (digits.m_digits.at(i) != (number % 10))
			return false;
			number = number / 10;
	}
	return true;

}

bool operator!=(const BigInt & digits1, const BigInt & digits2)
{
	return !(digits1 == digits2);
}

bool operator!=(const BigInt & digits, int number)
{
	return !(digits == number);
}

bool operator!=(int number, const BigInt & digits)
{
	return !(number == digits);
}

bool operator<(const BigInt & digits1, const BigInt & digits2)
{	  
	if (digits1.m_sign == '+' && digits2.m_sign == '-')
		return false;
	if (digits1.m_digits.size() >= digits2.m_digits.size())
		return false;
	for (int i = digits1.m_digits.size() - 1; i >= 0; i--)
		if (digits1.m_digits.at(i) > digits2.m_digits.at(i))
			return false;
	return true;
}

bool operator<(const BigInt & digits, int number)
{
	int copyNumber = number;
	char m_signNumber;
	if (number < 0)
		m_signNumber = '-';
	else
		m_signNumber = '+';

	if (digits.m_sign == '+' && m_signNumber == '-')
		return false;
	unsigned int digitsOfNumber = 0;
	while (copyNumber != 0)
	{
		digitsOfNumber++;
		copyNumber /= 10;
	}
	if (digits.m_digits.size() >= digitsOfNumber)
		return false;

	for (int i = digits.m_digits.size() - 1; i >= 0; i--)
	{
		if (digits.m_digits.at(i) > (number % 10))
			return false;
			number = number / 10;
	}
	return true;
}

bool operator<(int number, const BigInt & digits)
{
	int copyNumber = number;
	char m_signNumber;
	if (number < 0)
		m_signNumber = '-';
	else
		m_signNumber = '+';

	if (digits.m_sign == '+' && m_signNumber == '-')
		return true;
	unsigned int digitsOfNumber = 0;
	while (copyNumber != 0)
	{
		digitsOfNumber++;
		copyNumber /= 10;
	}
	if (digits.m_digits.size() <= digitsOfNumber)
		return false;

	for (int i = digits.m_digits.size() - 1; i >= 0; i--)
	{
		if (digits.m_digits.at(i) < (number % 10))
			return false;
		
		number = number / 10;
	}
	return true;
}

bool operator<=(const BigInt & digits1, const BigInt & digits2)
{                    
	if (digits1.m_sign == '+' && digits2.m_sign == '-')
		return false;
	if (digits1.m_digits.size() > digits2.m_digits.size())
		return false;
	for (int i = digits1.m_digits.size() - 1; i >= 0; i--)
		if (digits1.m_digits.at(i) > digits2.m_digits.at(i))
			
			return false;
	return true;
}

bool operator<=(const BigInt & digits, int number)
{
	int copyNumber = number;
	char m_signNumber;
	if (number < 0)
		m_signNumber = '-';
	else
		m_signNumber = '+';

	if (digits.m_sign == '+' && m_signNumber == '-')
		return false;
	unsigned int digitsOfNumber = 0;
	while (copyNumber != 0)
	{
		digitsOfNumber++;
		copyNumber /= 10;
	}
	if (digits.m_digits.size() > digitsOfNumber)
		return false;

	for (int i = digits.m_digits.size() - 1; i >= 0; i--)
	{
		if (digits.m_digits.at(i) > (number % 10))
			return false;
		number = number / 10;
	}
	return true;
}

bool operator<=(int number, const BigInt & digits)
{
	int copyNumber = number;
	char m_signNumber;
	if (number < 0)
		m_signNumber = '-';
	else
		m_signNumber = '+';

	if (digits.m_sign == '+' && m_signNumber == '-')
		return true;
	unsigned int digitsOfNumber = 0;
	while (copyNumber != 0)
	{
		digitsOfNumber++;
		copyNumber /= 10;
	}
	if (digits.m_digits.size() <= digitsOfNumber)
		return false;   

	for (int i = digits.m_digits.size() - 1; i >= 0; i--)
	{
		if (digits.m_digits.at(i) < (number % 10))
			return false;

		number = number / 10;
	}
	return true;
}

bool operator>(const BigInt & digits1, const BigInt & digits2)
{
	return !(digits1 <= digits2);
}

bool operator>(const BigInt & digits, int number)
{
	return !(digits <= number);
}

bool operator>(int number, const BigInt & digits)
{
	return !(number <= digits);
}

bool operator>=(const BigInt & digits1, const BigInt & digits2)
{
	return !(digits1 < digits2);
}

bool operator>=(const BigInt & digits, int number)
{
	return !(digits < number);
}

bool operator>=(int number, const BigInt & digits)
{
	return !(number < digits);
}

std::istream & operator>>(std::istream & stream, BigInt & number)
{
	std::string s;
	stream >> s;
	number = BigInt(s);

	return stream;
}

std::ostream & operator<<(std::ostream & stream, const BigInt & number)
{
	if (number.m_sign == '-')
		std::cout << number.m_sign;
	if (number.m_digits.size() == 1 && number.m_digits.at(0) == '0')
		stream << "Numarul este 0, in baza 10";

	for (auto i = number.m_digits.rbegin(); i != number.m_digits.rend(); ++i)
	{
		stream << char(*i + '0');
	}

	return stream;

}

BigInt operator+(const BigInt & digits)
{
	return digits;
}

BigInt operator-(const BigInt & digits)
{
	BigInt auxiliar(digits);
	if (auxiliar.getSign() == '-')
		auxiliar.setSign('+');
	else
		auxiliar.setSign('-');
	return auxiliar;
}

BigInt operator+(const BigInt & digits1, const BigInt & digits2)
{
	BigInt result(digits1);
	result += digits2;
	return result;
}

BigInt operator+(const BigInt & digits, int number)
{
	BigInt result(digits);
	result += number;
	return result;
}

BigInt operator+(int number, const BigInt & digits)
{
	BigInt result(digits);
	result += number;
	return result;
}

BigInt operator-(const BigInt & digits1, const BigInt & digits2)
{
	BigInt result(digits1);
	result -= digits2;
	return result;
}

BigInt operator-(const BigInt & digits, int number)
{
	BigInt result(digits);
	result -= number;
	return result;
}

BigInt operator-(int number, const BigInt & digits)
{
	BigInt result(number);
	result -= number;
	return result;
}
/*
BigInt operator*(const BigInt & digits1, const BigInt & digits2)
{
	BigInt result(digits1);
	result *= digits2;
	return result;
}
*/
BigInt operator*(const BigInt & digits, int number)
{
	BigInt result(digits);
	result *= number;
	return result;
}
BigInt operator%(const BigInt & digits, int number)
{
	int res = 0;
	for (int i = 0; i < digits.m_digits.size(); i++)
		res = (res * 10 + digits.m_digits.at(i)) / number;

	return res;

}
BigInt operator%(int number, const BigInt & digits)
{
	int res = 0;
	for (int i = 0; i < digits.m_digits.size(); i++)
		res = (res * 10 + digits.m_digits.at(i)) / number;

	return res;
}
/*
BigInt operator*(int number, const BigInt & digits)
{
	BigInt result(number);
	result *= digits;
	return result;
}

BigInt operator/(const BigInt & digits1, const BigInt & digits2)
{
	BigInt result(digits1);
	result /= digits2;
	return result;
}

BigInt operator/(const BigInt & digits, int number)
{
	BigInt result(digits);
	result /= number;
	return result;
}

BigInt operator/(int number, const BigInt & digits)
{
	BigInt result(number);
	result /= number;
	return result;
}

BigInt operator^(const BigInt & base, int exponent)
{
	BigInt result;
	if (exponent == 0)
	{
		result.m_digits.push_back(1);
		return result;
	}

	for (i = 0; i < exponent; i++)
		result *= base;
	return result;
}
*/
