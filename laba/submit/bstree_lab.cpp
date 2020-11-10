// bstree_lab.cpp
// Lab A
// CS 140
// Name: Logan Tillman
// Date: November 25, 2019

/* This lab recreates functions that will balance a BST, calculate 
   the height of the tree, and calculate the depth of a node */

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "bstree.hpp"
using namespace std;
using CS140::BSTree;
using CS140::BSTNode;

/* ---------------------------------------------- */
/* You'll write all of these as part of your lab. */

// This function calculates the depth of a node
int BSTree::Depth(const string &key) const
{
	BSTNode *n;
	int i;

	i = 0;
	
	// n is the root node
	n = sentinel->right;

	while (true) 
	{
    	if (n == sentinel) return -1;
    	if (key == n->key) return i;

		// Traversing the tree to find the key
    	if (key < n->key)  
			n = n->left;
		else	
			n = n->right;

		i++;
  	}
}
         
// This function returns the height of the tree
int BSTree::Height() const
{
	return recursive_find_height(sentinel->right);
}

// This function returns a vector of the keys in order
vector <string> BSTree::Ordered_Keys() const
{
  vector <string> rv;

  // Ordering the vector
  make_key_vector(sentinel->right, rv);

  return rv;
}
    
// This is the copy constructor
BSTree::BSTree(const BSTree &t)        
{
	// Creating the sentinel node
	sentinel = new BSTNode;
	sentinel->left = NULL;	
	sentinel->right = sentinel;
	sentinel->parent = NULL;
	sentinel->key = "---SENTINEL---";
	sentinel->val = NULL;
	size = 0;

	// Calling the operator overload
	*this = t;
}

// This is the operator overload
BSTree& BSTree::operator= (const BSTree &t) 
{
	// Clearing anything existing in the tree
	Clear();
	vector <string> tkeys;

	// I use a temporary vector to clean up my function call
	tkeys = t.Ordered_Keys();
	size = 0;

	// Balancing the tree passed in as a reference and setting the current tree equal to it
	sentinel->right = make_balanced_tree(tkeys, t.Ordered_Vals(), 0, tkeys.size());

	// Setting the size
	size = t.size;

  return *this;
}

// This function finds the height of the tree recursively
int BSTree::recursive_find_height(const BSTNode *n) const
{
	// Base case
	if (n == sentinel)
		return 0;

	int leftnodes, rightnodes;

	// Finds the height of the left and right nodes
	leftnodes = recursive_find_height(n->left);
	rightnodes = recursive_find_height(n->right);

	// Returns the greatest side (plus 1 because of the root node)
	if (leftnodes > rightnodes)
		return leftnodes+1;

	else
		return rightnodes+1;
}

// Creating the key vector in order
void BSTree::make_key_vector(const BSTNode *n, vector<string> &v) const
{
	// Base case
	if (n == sentinel)
		return;

	// Creating the vector in order by going from the lowest node to the highest
	make_key_vector(n->left, v);
	v.push_back(n->key);
	make_key_vector(n->right, v);
}

// This function balances a tree given the key and val vectors
BSTNode *BSTree::make_balanced_tree(const vector<string> &sorted_keys, 
                            const vector<void *> &vals,
                            size_t first_index,
                            size_t num_indices) const
{
	// Base case
	if (num_indices == 0)
		return sentinel;

	// Variable to keep up with the current node
	BSTNode *currentnode;

	currentnode = new BSTNode;

	// Using recursion to set the left and right nodes
	currentnode->left = make_balanced_tree(sorted_keys, vals, first_index, num_indices/2);
	currentnode->right = make_balanced_tree(sorted_keys, vals, (num_indices/2)+1+first_index, num_indices-(num_indices/2)-1);

	// Setting the val and key by accessing the vectors
	currentnode->val = vals[(num_indices/2)+first_index];
	currentnode->key = sorted_keys[(num_indices/2)+first_index];
		
	// Setting the current node to be its children's parent
	currentnode->left->parent = currentnode;
	currentnode->right->parent = currentnode;

	// returning the root node to the assignment overload
  return currentnode;
}
