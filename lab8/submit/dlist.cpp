// dlist.cpp
// Lab 8
// CS 140
// Author: Logan Tillman
// Date: November 4, 2019

/* This lab is an implementation of the Doubly-Linked List data structure. */

#include <iostream>
#include "dlist.hpp"
using namespace std;

Dlist::Dlist()
{
	/* This is the constructor that creates the sentinel node and 
	   sets the size of the list to zero */
	sentinel = new Dnode;
	sentinel->flink = sentinel;
	sentinel->blink = sentinel;
	size = 0;
}

// This is the copy constructor
Dlist::Dlist(const Dlist &d)
{
	Dnode *n;

	// Creating the sentinel node for the new Dlist
	sentinel = new Dnode;
	sentinel->flink = sentinel;
	sentinel->blink = sentinel;
	size = 0;

	// Copying all of the data to the new Dlist
	for (n = d.Begin(); n != d.End(); n = n->flink)
		Push_Back(n->s);
}

// This is the assignment overload
Dlist& Dlist::operator= (const Dlist &d)
{
	Dnode *n;

	// Clearing out any existing data in the current Dlist
	Clear();
	
	// Copying the data to the current Dlist
	for (n = d.Begin(); n != d.End(); n = n->flink)
		Push_Back(n->s);

	// Returning the current Dlist
	return *this;
}

// This is the destructor
Dlist::~Dlist()
{
	/* Clearing all of the data in the Dlist and deleting
	   the sentinel node */
	Clear();
	delete sentinel;
}

// Deletes all of the data except the sentinel node
void Dlist::Clear()
{
	while (size > 0)
		Pop_Front();
}

// Checks to see if the list is empty or not
bool Dlist::Empty() const
{
	// Size is 0 even if there is a sentinel node
	if (size == 0)
		return true;
	else
		return false;
}

// Returns the size of the Dlist
size_t Dlist::Size() const
{
	return size;
}

// Adds a node onto the front of the Dlist
void Dlist::Push_Front(const string &s)
{
	// Inserting the node after the sentinel node
	Insert_Before(s, sentinel->flink);
}

// Adds a node onto the back of the Dlist
void Dlist::Push_Back(const string &s)
{
	// Inserting the node after the last node
	Insert_After(s, sentinel->blink);
}

// Removes and returns the node at the front of the Dlist
string Dlist::Pop_Front()
{
	string rv;

	// Saving the value to return before deleting the node
	rv = sentinel->flink->s;
	Erase(sentinel->flink);
	return rv;
}

// Removes and returns the nodes at the end of the Dlist
string Dlist::Pop_Back()
{
	string rv;

	// Saving the value before erasing it
	rv = sentinel->blink->s;
	Erase(sentinel->blink);
	return rv;
}

// Returns the node at the beginning of the Dlist
Dnode * Dlist::Begin() const
{
	/* The node at the beginning of the list comes after
	   the sentinel node */
	return sentinel->flink;
}

// Returns the node at the end of the Dlist
Dnode * Dlist::End() const
{
	// The node at the end is the sentinel node
	return sentinel;
}

// Returns the last node in the list
Dnode * Dlist::Rbegin() const
{
	return sentinel->blink;
}

// Returns the sentinel node
Dnode * Dlist::Rend() const
{
	return sentinel;
}

// Inserts a string before the given node
void Dlist::Insert_Before(const string &s, Dnode *n)
{
	/* Creating variables to store the new node
	   and the node that comes before it */
	Dnode *newnode;
	Dnode *prev;

	// Creating the new node and setting it's blink and flink
	newnode = new Dnode;
	newnode->s = s;
	prev = n->blink;
	n->blink = newnode;
	prev->flink = newnode;
	newnode->blink = prev;
	newnode->flink = n;

	// Incrementing the size by one
	size++;
}

// Inserts a node after the given node
void Dlist::Insert_After(const string &s, Dnode *n)
{
	/* I do this function by inserting the new node
	   before the current node's flink */
	Insert_Before(s, n->flink);
}

// Erases a node from the Dlist
void Dlist::Erase(Dnode *n)
{
	/* Checking to make sure we aren't deleting the
	   sentinel node */
	if (n == sentinel)
		return;

	/* Creating variables for the nodes that come
	   before and after the node we're deleting */
	Dnode *prev;
	Dnode *next;

	// Setting up the blinks and flinks for the nodes
	prev = n->blink;
	next = n->flink;
	next->blink = prev;
	prev->flink = next;

	// Decrementing the size
	size--;

	// Deleting the node
	delete n;
}


