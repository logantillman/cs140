// fraction.cpp
// Lab 6
// CS140
// Author: Logan Tillman
// Date: October 21, 2019
// This program manages a fraction using different method calls

#include <iostream>
#include <cstdio>
#include "fraction.hpp"
using namespace std;

// Clears the fraction
void Fraction::Clear()
{
	numerator.clear();
	denominator.clear();
}

// Multiplies the fraction
bool Fraction::Multiply_Number(int n)
{
	if (n <= 0)
		return false;

	// Checks to see if the number exists in the denominator for cancellation
	if (denominator.find(n) != denominator.end())
	{
		denominator.erase(denominator.find(n));
		return true;
	}

	// Inserts the number into the numerator
	if (n > 1)
		numerator.insert(n);
	
	return true;
}

// Divides the fraction
bool Fraction::Divide_Number(int n)
{
	if (n <= 0)
		return false; 

	// Checks to see if the number exists in the numerator for cancellation
	if (numerator.find(n) != numerator.end())
	{
		numerator.erase(numerator.find(n));
		return true;
	}

	// Inserts the number into the denominator
	if (n > 1)
		denominator.insert(n);

	return true;
}

// Multiplying the fraction by a factorial
bool Fraction::Multiply_Factorial(int n)
{
	if (n <= 0) 
		return false;

	// Loops through the whole factorial
	for (int i = 2; i <= n; i++)
	{
		// Checks for cancellation
		if (denominator.find(i) != denominator.end())
		{
			denominator.erase(denominator.find(i));
			continue;
		}

		// Inserts the number in the numerator
		numerator.insert(i);
	}

	return true;
}

// Divides the fraction by a factorial
bool Fraction::Divide_Factorial(int n)
{
	if (n <= 0)
		return false;

	// Loops through the whole factorial
	for (int i = 2; i <= n; i++)
	{
		// Checks for cancellation
		if (numerator.find(i) != numerator.end())
		{
			numerator.erase(numerator.find(i));
			continue;
		}

		// Inserts the number into the denominator
		denominator.insert(i);
	}

	return true;
}

// Multiplies the fraction by a binomial
bool Fraction::Multiply_Binom(int n, int k)
{
	if (n <= 0)
		return false;
	if (k < 0)
		return false;

	// Inserting into the denominator
	for (int i = 2; i <= k; i++)
	{
		// Checks for cancellation
		if (numerator.find(i) != numerator.end())
		{
			numerator.erase(numerator.find(i));
			continue;
		}
		
		denominator.insert(i);
	}
	
	// Inserting into the numerator
	for (int i = n-k+1; i <= n; i++)
	{
		// Checks for cancellation
		if (denominator.find(i) != denominator.end())
		{
			denominator.erase(denominator.find(i));
			continue;
		}

		numerator.insert(i);
	}

	return true;
}

// Divides the fraction by a binomial
bool Fraction::Divide_Binom(int n, int k)
{
	if (n <= 0)
		return false;
	if (k < 0)
		return false; 

	// Inserting into the numerator
	for (int i = 2; i <= k; i++)
	{
		// Checks for cancellation
		if (denominator.find(i) != denominator.end())
		{
			denominator.erase(denominator.find(i));
			continue;
		}
		
		numerator.insert(i);
	}

	// Inserting into the denominator
	for (int i = n-k+1; i <= n; i++)
	{
		// Checks for cancellation
		if (numerator.find(i) != numerator.end())
		{
			numerator.erase(numerator.find(i));
			continue;
		}

		denominator.insert(i);
	}

	return true;
}

// Flips the numerator and denominator
void Fraction::Invert()
{
	multiset <int> temp;

	temp = numerator;
	numerator = denominator;
	denominator = temp;
}

// Prints the fraction to follow the correct formatting
void Fraction::Print() const 
{
	multiset <int>::const_iterator nit;
	multiset <int>::const_iterator dit;

	if (numerator.size() == 0)
		cout << "1";

	for (nit = numerator.begin(); nit != numerator.end(); nit++)
	{
		if (nit == numerator.begin())
			cout << *nit;
		else
			cout << " * " << *nit;
	}

	for (dit = denominator.begin(); dit != denominator.end(); dit++)
		cout << " / " << *dit;

	cout << '\n';
}

// Calculates the fraction
double Fraction::Calculate_Product() const
{
	multiset <int>::const_iterator nit;
	multiset <int>::const_iterator dit;
	double numer;
	double denom;
	double rv;

	numer = 1;
	denom = 1;

	// Running totals for the numerator and denominator
	for (nit = numerator.begin(); nit != numerator.end(); nit++)
		numer *= *nit;

	for (dit = denominator.begin(); dit != denominator.end(); dit++)
		denom *= *dit;

	rv = numer / denom;

	return rv;
}
