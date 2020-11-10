// Lab 4
// CS140
// Author: Logan Tillman
// Date: September 23, 2019
// This lab implements a hash table with two different hash functions

#include "hash_140.hpp"
#include <sstream>
#include <cstdio>

using namespace std;

// Checks to see if the key contains valid hex characters
string keycheck (const string &key)
{
	string possiblehex = "0123456789abcdefABCDEF";
	
	// Checks the characters in key and compares them to the characters
	// in possiblehex to make sure they're all valid
	for (int i = 0; i < (int) key.size(); i++)
    {
        for (int j = 0; j < (int) possiblehex.size(); j++)
        {
            if (key[i] ==  possiblehex[j])
                break;
            if (j == (int) (possiblehex.size()-1))
                return "Error";
        }
    }
return "";
}

// Hash function that returns the last 7 characters of the key
string Last7(const string &key)
{
    string tempkey;

	if (keycheck(key) == "Error")
		return "Error";

	// Takes the last 7 characters from the string if its longer than 7
    if (key.size() > 7)
        for (int i = 1; i <= 7; i++)
            tempkey = key[key.size()-i] + tempkey;
	else
		tempkey = key;

    return tempkey;
}

// Returns the hash of 7 character strings from key XOR'ed with each other
string Xor(const string &key)
{
    stringstream ss;
    string tempkey;
    vector <string> strings;
    vector <int> hexcheck;
    string rv;
    int count = 0;
    int total = 0;

	if (keycheck(key) == "Error")
		return "Error";

	// Breaks the key string up into 7 character long strings
    for (int i = 0; i < (int) key.size(); i++)
    {
        tempkey = tempkey + key[i];
        ++count;
        if ((count == 7) || (i == ((int) key.size()-1)))
        {
            strings.push_back(tempkey);
            tempkey = "";
            count = 0;
        }
    }

    hexcheck.resize(strings.size());

	// Converts the strings into hex
    for (int i = 0; i < (int) strings.size(); i++)
    {
        stringstream s;
        s << strings[i];
        s.clear();
		s >> hex >> hexcheck[i];
    }

	// XOR's all of the hex values together
    for (int i = 0; i < (int) hexcheck.size(); i++)
        total = total ^ hexcheck[i];

	// Converts the value back to a hex string
    ss.clear();
    ss << hex << total;
    ss >> rv;

return rv;
}

string Hash_140::Set_Up(size_t table_size, const std::string &fxn, const std::string &collision)
{
	// Checking the table sizes
	if (Vals.size() != 0 || Keys.size() != 0)
		return "Hash table already set up";
	if (table_size < 1)	
		return "Bad table size";
	
	// Sets the sizes of the tables
	Keys.resize(table_size);
	Vals.resize(table_size);
	
	// Checking the hashing function
	if (fxn == "XOR")
		Fxn = 'X';
	else if (fxn == "Last7")
		Fxn = 'L';
	else
		return "Bad hash function";

	// Checking the collision resolution strategy
	if (collision == "Double")
		Coll = 'D';
	else if (collision == "Linear")
		Coll = 'L';
	else
		return "Bad collision resolution strategy";
	
	// Initializing Nkeys
	Nkeys = 0;

  return "";
}

string Hash_140::Add(const string &key, const string &val)
{
	string hash;
	stringstream ss;
	int index, hashint;
	
	if (Keys.size() == 0 || Vals.size() == 0)
		return "Hash table not set up";
	if (key.size() == 0)
		return "Empty key";
	if (Keys.size() == Nkeys)
		return "Hash table full";

	if (Fxn == 'L')
		hash = Last7(key);
	else if (Fxn == 'X')
		hash = Xor(key);
	if (hash == "Error")
		return "Bad key (not all hex digits)";
	
	// Converting the hash into and integer
	ss << hash;
	ss >> hex >> hashint;
	ss.clear();

	// Calculating the index by hash % size
	index = hashint % Vals.size();

	// Inserts if the index is empty
	if (Vals[index].size() == 0)
	{
		Keys[index] = key;
		Vals[index] = val;
		++Nkeys;
	}

	// If it fails to insert, it tries to collision resolution strategies
	else
	{
		// Linear Collision
		if (Coll == 'L')
		{
			// Looping through to find an empty space in the vector
			for (int i = 0; index <= (int) Vals.size(); i++)
			{
				// Calculates the new index
				index = (hashint + i) % Vals.size();

				// If it loops through and can't find an empty slot
				// it returns hash table full
				if (index >= (int) Vals.size())
					return "Hash table full";

				// If the space is empty it inserts
				if (Vals[index].size() == 0)
				{
					Keys[index] = key;
					Vals[index] = val;
					++Nkeys;
					break;
				}

				// Increments Nprobes if it failed to insert
				++Nprobes;
			}
		}

		// Double Collision
		if (Coll == 'D')
		{
			string temp_hash;
			int temp_hashint;
			vector <int> collcheck;

			// temp_hash is the other hash function
			if (Fxn == 'X')
				temp_hash = Last7(key);
			else if (Fxn == 'L')
				temp_hash = Xor(key);
			else
				return "Bad key (not all hex digits)";

			// Turning the temp_hash hex string into an int
			ss << temp_hash;
			ss >> hex >> temp_hashint;
			ss.clear();

			// Getting the index value for the temp_hash
			temp_hashint = temp_hashint % Vals.size();

			if (temp_hashint == 0)
				temp_hashint = 1;

			
			for (int i = 0; i < (int) Vals.size(); i++)
			{
				// Calculates new index
				index = (hashint + (temp_hashint*i)) % Vals.size();

				// Checks to see if we're hitting a pattern when calculating
				// the new index
				for (int j = 0; j < (int) collcheck.size(); j++)
				{
					if (collcheck[j] == index)
						return "Cannot insert key";
				}

				// Adds it to the vector if it doesn't already exist
				collcheck.push_back(index);
				
				// Checks to see if it can insert into the index
				if (Vals[index].size() == 0)
				{
					Keys[index] = key;
					Vals[index] = val;
					++Nkeys;
	//				return "";
					break;
				}
			
				// Increments Nprobes if it fails
				++Nprobes;
			}
		}
	}

  return "";
}	

string Hash_140::Find(const string &key)
{
		// Finds the value at the given key
		for (int i = 0; i < (int) Keys.size(); i++)
		{
			if (Keys[i] == key)
				return Vals[i];
		}
  return "";
}

void Hash_140::Print() const
{
	// Prints out any key and value in the vector
	for (int i = 0; i < (int) Vals.size(); i++)
	{
		if (Vals[i].size() != 0)
			printf("%5d %s %s\n", i, Keys[i].c_str(), Vals[i].c_str());
	}
}

size_t Hash_140::Total_Probes()
{
	// Checks to see if the vector exists
	if (Vals.size() == 0)
		return 0;

	// Returns the value of Nprobes
	return Nprobes;
}

