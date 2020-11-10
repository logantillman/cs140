// avltree_lab.cpp
// Lab B
// CS 140
// Author: Logan Tillman
// Date: December 5, 2019

/* This is a program that recreates AVLTrees */

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include "avltree.hpp"
using namespace std;
using CS140::AVLTree;
using CS140::AVLNode;

// This function will recursively fix the height of the nodes
void fix_height(AVLNode *n)
{
	// Return if sentinel
	if (n->height == 0)
		return;

	// Takes the larger child and sets the node height to + 1 the child's height
	if (n->right->height > n->left->height)
		n->height = n->right->height + 1;
	else
		n->height = n->left->height + 1;
}

// This function determines if there's an imbalance in the tree or not
bool imbalance(const AVLNode *n)
{
	// Checks the height of the node and it's children for imbalances
	if (n->height > (n->left->height + 2))
		return true;
	else if (n->height > (n->right->height + 2))
		return true;
	return false;
}

// This function rotates a node
void rotate(AVLNode *n)
{
	// Checking to make sure the node isn't the sentinel and it's not the root
	if (n->height == 0)
		return;

	AVLNode *parent;
	AVLNode *grandparent;
	AVLNode *middle;

	// Assigning the parent and grandparent
	parent = n->parent;
	grandparent = parent->parent;

	// Moving the node to be the grandparents child
	if (grandparent->right == n->parent)
		grandparent->right = n;
	else
		grandparent->left = n;

	// Determining what to set depending on which side the child is on
	if (parent->left == n)
	{
		middle = n->right;
		parent->left = middle;
		n->right = parent;
	}
	else if (parent->right == n)
	{
		middle = n->left;
		parent->right = middle;
		n->left = parent;
	}

	// Setting the parents for the nodes
	n->parent = grandparent;
	parent->parent = n;
	middle->parent = parent;

	// Fixing the height of the node and it's parent
	fix_height(parent);
	fix_height(n);
}

// This function fixes the imbalances in the AVLTree
void fix_imbalance(AVLNode *n)
{
	// Executes if the imbalance comes from the right child
	if (n->right->height > n->left->height)
	{
		// Zig-Zag to the right
		if (n->right->left->height > n->right->right->height)
		{
			rotate(n->right->left);
			rotate(n->right);
		}
		
		// Zig-Zig to the right
		else
			rotate(n->right);

	}
	
	// Executes if the imbalances comes from the left child
	else if (n->left->height > n->right->height)
	{
		// Zig-Zag to the left
		if (n->left->right->height > n->left->left->height)
		{
			rotate(n->left->right);
			rotate(n->left);
		}

		// Zig-Zig to the left
		else
			rotate(n->left);
	}
}

// This is the assignment overload
AVLTree& AVLTree::operator= (const AVLTree &t)        
{
	// Clearing the tree before copying
	Clear();
	size = 0;

	// Copying the tree over using recursion and setting the parent of the root node
	sentinel->right = recursive_postorder_copy(t.sentinel->right);
	sentinel->right->parent = sentinel;

	// Setting the size
	size = t.size;

  return *this;
}

/* I simply took Insert and Delete from their binary search tree
   implementations.  They aren't correct for AVL trees, but they are
   good starting points.  */

bool AVLTree::Insert(const string &key, void *val)
{
  AVLNode *parent;
  AVLNode *n;

  parent = sentinel;
  n = sentinel->right;

  /* Find where the key should go.  If you find the key, return false. */

  while (n != sentinel) {
    if (n->key == key) return false;
    parent = n;
    n = (key < n->key) ? n->left : n->right;
  }

  /* At this point, parent is the node that will be the parent of the new node.
     Create the new node, and hook it in. */

  n = new AVLNode;
  n->key = key;
  n->val = val;
  n->parent = parent;
  n->height = 1;
  n->left = sentinel;
  n->right = sentinel;

  /* Use the correct pointer in the parent to point to the new node. */

  if (parent == sentinel) {
    sentinel->right = n;
  } else if (key < parent->key) {
    parent->left = n;
  } else {
    parent->right = n;
  }

  // Fixing the height of nodes as they're inserted and checking if it's balanced
  while (n->parent != sentinel)
  {
	 n = n->parent;
	 fix_height(n);
	 if (imbalance(n) == true)
		 fix_imbalance(n);
  }

  /* Increment the size */
  size++;
  return true;
}
    
bool AVLTree::Delete(const string &key)
{
  AVLNode *n, *parent, *mlc;
  string tmpkey;
  void *tmpval;

  /* Try to find the key -- if you can't return false. */

  n = sentinel->right;
  while (n != sentinel && key != n->key) {
    n = (key < n->key) ? n->left : n->right;
  }
  if (n == sentinel) return false;

  /* We go through the three cases for deletion, although it's a little
     different from the canonical explanation. */

  parent = n->parent;

  /* Case 1 - I have no left child.  Replace me with my right child.
     Note that this handles the case of having no children, too. */

  if (n->left == sentinel) {
    if (n == parent->left) {
      parent->left = n->right;
    } else {
      parent->right = n->right;
    }
    if (n->right != sentinel) n->right->parent = parent;
    delete n;
    size--;

	// Fixing the height of the parent and checking for imbalance
	fix_height(parent);
	while (parent != sentinel)
	  {
		fix_height(parent);
		if (imbalance(parent) == true)
			fix_imbalance(parent);
		parent = parent->parent;
	  } 
  /* Case 2 - I have no right child.  Replace me with my left child. */

  } else if (n->right == sentinel) {
    if (n == parent->left) {
      parent->left = n->left;
    } else {
      parent->right = n->left;
    }
    n->left->parent = parent;
    delete n;
    size--;

	// Fixing the height of the parent and checking for imbalance
	fix_height(parent);
	while (parent != sentinel)
	{
		fix_height(parent);
		if (imbalance(parent) == true)
			fix_imbalance(parent);
		parent = parent->parent;
	} 
  /* If I have two children, then find the node "before" me in the tree.
     That node will have no right child, so I can recursively delete it.
     When I'm done, I'll replace the key and val of n with the key and
     val of the deleted node.  You'll note that the recursive call 
     updates the size, so you don't have to do it here. */

  }	else {
    for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
    tmpkey = mlc->key;
    tmpval = mlc->val;
    Delete(tmpkey);
    n->key = tmpkey;
    n->val = tmpval;
  }

return true;
}
               
/* You need to write these two.  You can lift them verbatim from your
   binary search tree lab. */

vector <string> AVLTree::Ordered_Keys() const
{
  vector <string> rv;

  // Ordering the vector
  make_key_vector(sentinel->right, rv);

  return rv;
}
    
void AVLTree::make_key_vector(const AVLNode *n, vector<string> &v) const
{    
	// Base case
    if (n == sentinel)
        return;

    // Creating the vector in order by going from the lowest node to the highest
    make_key_vector(n->left, v);
    v.push_back(n->key);
    make_key_vector(n->right, v);
}
     
size_t AVLTree::Height() const
{
  return sentinel->right->height;
}

/* You need to write this to help you with the assignment overload.
   It makes a copy of the subtree rooted by n.  That subtree is part
   of a different tree -- the copy will be part of the tree that
   is calling the method. */

// Recursively copying the nodes
AVLNode *AVLTree::recursive_postorder_copy(const AVLNode *n) const
{
	// Making sure the node isn't sentinel
	if (n->height == 0)
		return sentinel;

	AVLNode *curr;
	
	curr = new AVLNode;

	// Setting the left and right subtrees recursively
	curr->left = recursive_postorder_copy(n->left);
	curr->right = recursive_postorder_copy(n->right);

	// Setting the key, value, and height of the node
	curr->key = n->key;
	curr->val = n->val;
	curr->height = n->height;

	// Setting the parents of the children
	curr->left->parent = curr;
	curr->right->parent = curr;

	return curr;
}
