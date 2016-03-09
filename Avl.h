/**
* \file Avl.h
* \brief This file can create, insert and retrieve nodes in an AVL ( balanced
* binary tree search )
* \author Isabelle MARINO Pierrick JACQUETTE Hafça TIRICHINE
* \date 21 fevrier 2016
*
* Basic operations of an AVL tree involve carrying out the same actions as would
* be carried out on an unbalanced binary search tree, but modifications are
* followed by zero or more operations called tree rotations, which help to
* restore the height balance of the subtrees.
*
* The insertion, search are O(log n)

*/


#ifndef __AVL_H__
#define __AVL_H__

#include <stdio.h>
#include <stdlib.h>
#include "init.h"

/**
* search function in an AVL according to a key, this key is the reference node
* @param  a   Self-balancing binary search tree
* @param  key it is the reference node
* @return     return the node if it exists, otherwise null
*/
Node* search(Avl *a, unsigned long key);

/**
 * function to insert the key in the AVL in the right place according to its
 * value , and the transition if necessary, rebalanced the tree
 * @param  a       Self-balancing binary search tree
 * @param  contenu it is the reference node
 * @return         A tree under the pointer with the change
 */
Avl* insert(Avl **a,Node *n, Way *w);

/**
 * Initializing the AVL with the root , the parameter content
 * @param a       Self-balancing binary search tree
 * @param contenu it is the reference node
 */
void init(Avl **a,Node *n, Way*w);

/**
 * function allowing display of the AVL
 * @param a      Self-balancing binary search tree
 * @param nombre dentifier of the tree level view
 */
void print(Avl **a,unsigned long nombre);


#endif /* __AVL_H__ */
