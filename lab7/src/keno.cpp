// keno.cpp
// Lab 6
// CS 140
// Author: Logan Tillman
// Date: October 21, 2019
// This program calculates Keno odds after reading input

#include <iostream>
#include <cstdio>
#include "fraction.hpp"
using namespace std;

int main()
{
	Fraction *frac;
	double bet;
	double payout;
	double rpb;
	double winprob;
	double expectedret;
	double normalized;
	int balls;
	int caught;

	frac = new Fraction;
	rpb = 0;

	cin >> bet >> balls;

	printf("Bet: %.2f\n", bet);
	printf("Balls Picked: %d\n", balls); 

	while (cin >> caught >> payout)
	{
		/* Calculating the win probability using the formula 
		   binom(80-p,20-c) * binom(p,c) / binom(80,20) */
		frac->Clear();
		frac->Multiply_Binom(80-balls, 20-caught);
		frac->Multiply_Binom(balls, caught);
		frac->Divide_Binom(80, 20);
		winprob = frac->Calculate_Product();

		// Calculating the expected return
		expectedret = winprob * payout;

		cout << "  Probability of catching " << caught << " of " << balls << ": ";
		cout << winprob << " -- Expected return: " << expectedret << '\n';

		// Keeping a total of the expected return to find out the return per bet
		rpb += expectedret; 
	}

	// Finishing off the return per bet calculation
	rpb -= bet;

	// Finding the normalization
	normalized = rpb / bet;

	printf("Your return per bet: %.2f\n", rpb);
	printf("Normalized: %.2f\n", normalized);

	delete frac;
	return 0;
}
