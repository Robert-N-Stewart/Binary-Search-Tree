// ------------------------------------------------ bintree.h -------------------------------------------------------

// Programmer Name Course Section Number: Robert Stewart CSS 343 A

// Creation Date: 04/20/17

// Date of Last Modification: 04/20/17

// --------------------------------------------------------------------------------------------------------------------

// Purpose - this program acts as a BST to store pointers to nodedata 

// -------------------------------------------------------------------------------------------------------------------- 

// --------------------------------------------------------------------------------------------------------------------

#ifndef  BINTREE_H
#define BINTREE_H
#include <iostream>
#include <string>
#include "nodedata.h"

using namespace std;

// a bst for storing nodedata
class BinTree {

	//overloaded operator<< for outputing tree
	friend ostream& operator<<(ostream &output, const BinTree& b);

public:

	//constructors and destructors 
	//default constructor
	BinTree();
	//copy constructor
	BinTree(const BinTree& b);
	//destructor
	~BinTree();


	//Accessors
	bool retrieve(const NodeData&, NodeData*&);
	int getHeight(const NodeData&) const;

	//displays tree
	void displaySideways() const;

	//overloaded comparison operators
	bool operator==(const BinTree& b) const;
	bool operator!=(const BinTree& b) const;

	//modifiers
	//insertes passed nodedata ptr into the tree
	bool insert(NodeData* ptr);
	//makes the tree empty deleting each node of the tree and deallocating dynamic memory of node and nodedata
	void makeEmpty();
	//transfers nodedata from tree to passed array
	void bstreeToArray(NodeData*[]);
	//transfers nodedata from array to tree
	void arrayToBSTree(NodeData*[]);

	//assignment operator to assign passed tree to the implicit tree
	BinTree& operator=(const BinTree& b);

private:

	//node for storing data with left and right pointers to other nodes
	struct Node 
	{
		NodeData* data;
		Node* left;
		Node* right;

	};

	Node* root;

	//helper function for printing sideways
	void sideways(Node* current, int level) const;

	//helper modifing functions
	bool insertHelper(Node*& current, NodeData* data);
	void makeEmptyHelper(Node*& root);
	void copyHelper(Node*& thisCurrent, const Node* const passedCurrent);

	//equality helper function
	bool equalityHelper(const Node* const thisCurrent, const Node* const passedCurrent) const;

	//get height helper function
	int getHeightHelper(const NodeData& data, const Node* const root) const;
	int getHeightHelperHelper(const NodeData& data, const Node* const root, int count) const;

	bool retrieveHelper(const NodeData& data, NodeData*& prtToData, const Node* const root);

	//recursive helper function for overloaded<< operator
	void overloadedOutputHelper(ostream &output, const Node* const root) const;

	//recursive helper function for bstreeToArray function
	void bstreeToArrayHelper(NodeData* arr[], int& indexTracker, Node*& root);

	//recursive helper function for 
	void arrayToBSTreeHelper(NodeData* arr[], Node*& root, int low, int high);
};


#endif 

