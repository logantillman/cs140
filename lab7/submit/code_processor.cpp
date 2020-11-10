// code_processor.cpp
// Lab 7
// CS 140
// Author: Logan Tillman
// Date: October 26, 2019
// This program maintains a rewards system by managing users and prizes

#include <iostream>
#include <cstdio>
#include <fstream>
#include "code_processor.hpp"
using namespace std;

// Hash function used to calculate points
unsigned int djb_hash(const string &s)
{
  size_t i;
  unsigned int h;
  
  h = 5381;

  for (i = 0; i < s.size(); i++) {
    h = (h << 5) + h + s[i];
  }
  return h;
}

// Adds a new prize to the system
bool Code_Processor::New_Prize(const string &id, const string &description, int points, int quantity)
{
	/* Checks if the points and quantity are valid numbers 
	   and checks if the prize already exists */
	if (points <= 0)
		return false;
	if (quantity <= 0)
		return false;
	if (Prizes.find(id) != Prizes.end())
		return false;

	// Creating a new prize with the given parameters
	Prize *newprize;

	newprize = new Prize;

	newprize->id = id;
	newprize->description = description;
	newprize->points = points;
	newprize->quantity = quantity;

	// Adding the prize to the Prizes map
	Prizes[id] = newprize;

	return true;
}

// Adds a new user to the system
bool Code_Processor::New_User(const string &username, const string &realname, int starting_points)
{
	/* Checks to make sure the starting points is a valid number
	   and the user doesn't already exist */
	if (starting_points < 0)
		return false;
	if (Names.find(username) != Names.end())
		return false;

	// Creating the new user pointer with the given parameters
	User *newuser;

	newuser = new User;
	
	newuser->username = username;
	newuser->realname = realname;
	newuser->points = starting_points;

	// Inserting the user into the Names map
	Names[username] = newuser;

	return true;
}

bool Code_Processor::Delete_User(const string &username)
{
	// Checks to see if the username exists
	if (Names.find(username) == Names.end())
		return false;
	
	map <string, User *>::iterator nit;
	set <string>::iterator pnit;

	nit = Names.find(username);
	
	// Removing the phone numbers from the Phones map
	for (pnit = nit->second->phone_numbers.begin(); pnit != nit->second->phone_numbers.end(); pnit++)
		Remove_Phone(nit->second->username, *pnit);
	
	// Erasing the information from the Names map
	Names.erase(nit);
	
	// Deleting the User pointer
	delete nit->second;

	return true;
}

// Adds a phone number to the system
bool Code_Processor::Add_Phone(const string &username, const string &phone)
{
	/* Checks to see if the user exists and 
	   the phone number isn't already registered */
	if (Names.find(username) == Names.end())
		return false;
	if (Phones.find(phone) != Phones.end())
		return false;
	
	// Adds the number to the user's list of phone numbers
	Names[username]->phone_numbers.insert(phone);

	// Adds the phone and user to the Phones map
	Phones[phone] = Names[username];

	return true;
}

// Removes the phone from the system
bool Code_Processor::Remove_Phone(const string &username, const string &phone)
{
	/* Checks to make sure the user exists, the phone number
	   exists, and the phone number belongs to the given user */
	if (Names.find(username) == Names.end())
		return false;
	if (Phones.find(phone) == Phones.end())
		return false;
	if (Phones[phone]->username != username)
		return false;
	
	set <string>::iterator phit;

	// Iterator for the given phone number
	phit = Names[username]->phone_numbers.find(phone);

	// Erases the phone number from the user
	Names[username]->phone_numbers.erase(phit);

	// Erases the phone number from the Phones map
	Phones.erase(Phones.find(phone));

	return true;
}

// Displays all of the phone numbers registered under a username
string Code_Processor::Show_Phones(const string &username) const
{
	// Checks to make sure the user exists and has phones
	if (Names.find(username) == Names.end())
		return "BAD USER";
	if (Names.find(username)->second->phone_numbers.size() == 0)
		return "";

	map <string, User *>::const_iterator nit;
	set <string>::const_iterator pit;
	string rv;

	// Finding the iterator for the given username
	nit = Names.find(username);
	rv = "";

	// Adding each phone number to rv on their own lines
	for (pit = nit->second->phone_numbers.begin(); pit != nit->second->phone_numbers.end(); pit++)
		rv += *pit + "\n";	

	return rv;
}

// Processes a code entered by a user
int Code_Processor::Enter_Code(const string &username, const string &code)
{
	/* Checks to make sure the user exists and
	   the code hasn't been redeemed previously */
	if (Codes.find(code) != Codes.end())
		return -1;
	if (Names.find(username) == Names.end())
		return -1;

	/* If the code is divisible by 17, it adds 10 points
	   to the user and makes the code unredeemable */
	if ((djb_hash(code) % 17) == 0)
	{
		Codes.insert(code);
		Names[username]->points += 10;
		return 10;
	}

	/* If the code is divisible by 13, then it add 3 points
	   to the user and makes the code unredeemable */
	else if ((djb_hash(code) % 13) == 0)
	{
		Codes.insert(code);
		Names[username]->points += 3;
		return 3;
	}

	// If it's not divisible by 17 or 13, it's invalid
	else
		return 0;
}

// Processes a code entered by a phone number
int Code_Processor::Text_Code(const string &phone, const string &code)
{
	/* Checks to make sure the phone number exists
	   and the code hasn't been redeemed */
	if (Codes.find(code) != Codes.end())
		return -1;
	if (Phones.find(phone) == Phones.end())
		return -1;

	// The rest does the same as the Enter_Code function
	if ((djb_hash(code) % 17) == 0)
	{
		Codes.insert(code);
		Phones[phone]->points += 10;
		return 10;
	}

	else if ((djb_hash(code) % 13) == 0)
	{
		Codes.insert(code);
		Phones[phone]->points += 3;
		return 3;
	}

	else
		return 0;
}

// Makes the given code unredeemable
bool Code_Processor::Mark_Code_Used(const string &code)
{
	// Checks to make sure the code isn't already inserted
	if (Codes.find(code) != Codes.end())
		return false;

	// Checks to make sure the code is valid
	if ((djb_hash(code) % 17) == 0)
	{
		Codes.insert(code);
		return true;
	}

	else if ((djb_hash(code) % 13) == 0)
	{
		Codes.insert(code);
		return true;
	}

	// If the code is invalid, we don't insert it
	else
		return false;
}

// Returns the given users point balance 
int Code_Processor::Balance(const string &username) const
{
	// Checks to make sure the user exists
	if (Names.find(username) == Names.end())
		return -1;

	// Returns the amount of points associated with the given user
	return Names.find(username)->second->points;
}

// Redeems a prize for the given user
bool Code_Processor::Redeem_Prize(const string &username, const string &prize)
{
	/* Checks to make sure the user and prize exist,
	  and the user has enough points to redeem the prize */
	if (Names.find(username) == Names.end())
		return false;
	if (Prizes.find(prize) == Prizes.end())
		return false;
	if (Names[username]->points < Prizes[prize]->points)
		return false;

	map <string, Prize *>::iterator pit;

	pit = Prizes.find(prize);

	// Subtracts the cost of the prize from the user's points
	Names[username]->points -= Prizes[prize]->points;

	// Decreases the quantity of the prize by 1
	Prizes[prize]->quantity -= 1;

	// Checks to see if the amount of prizes left is 0
	if (Prizes[prize]->quantity == 0)
	{
		// Erases the prize from the Prizes map
		Prizes.erase(pit);
		delete pit->second;
	}

	return true;
}
   
// Destructor to give back the memory used for the users and prizes
Code_Processor::~Code_Processor()
{
	map <string, User *>::iterator nit;
	map <string, Prize *>::iterator pit;

	// Deletes all of the user pointers
	for (nit = Names.begin(); nit != Names.end(); nit++)
		delete nit->second;

	// Deletes all of the prizes pointers
	for (pit = Prizes.begin(); pit != Prizes.end(); pit++)
		delete pit->second;
}

// Writes the state of the server to the given file name
bool Code_Processor::Write(const string &filename) const
{
	ofstream file;
	map <string, User *>::const_iterator nit;
	map <string, Prize *>::const_iterator pit;
	set <string>::const_iterator phit;
	set <string>::const_iterator cit;

	// Opens the file
	file.open(filename.c_str());

	// Checks to make sure the file opened without error
	if (file.fail())
		return false;

	// Loops through all of the Users
	for (nit = Names.begin(); nit != Names.end(); nit++)
	{
		// Writes all of the ADD_USER statements to the file
		file << "ADD_USER " << nit->first << " " << nit->second->points
			 << " " << nit->second->realname << '\n';

		// Writes all of the ADD_PHONE statements to the file
		for (phit = nit->second->phone_numbers.begin(); phit != nit->second->phone_numbers.end(); phit++)
			file << "ADD_PHONE " << nit->first << " " << *phit << '\n';	
	}
	
	// Loops through all of the prizes
	for (pit = Prizes.begin(); pit != Prizes.end(); pit++)
	{
		// Adds all of the PRIZE statements to the file
		file << "PRIZE " << pit->first << " " << pit->second->points << " "
			 << pit->second->quantity << " " << pit->second->description << '\n';
	}

	// Adds all of the used codes to the file
	for (cit = Codes.begin(); cit != Codes.end(); cit++)
		file << "MARK_USED " << *cit << '\n';

	return true;
}

