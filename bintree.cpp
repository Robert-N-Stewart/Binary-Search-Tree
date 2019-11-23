// ------------------------------------------------ bintree.cpp -------------------------------------------------------

// Programmer Name Course Section Number: Robert Stewart CSS 343 A

// Creation Date: 04/20/17

// Date of Last Modification: 04/20/17

// --------------------------------------------------------------------------------------------------------------------

// Purpose - this program acts as a BST to store pointers to nodedata 

// -------------------------------------------------------------------------------------------------------------------- 

// --------------------------------------------------------------------------------------------------------------------
#include "bintree.h"

//------------------------- Default Constructor ---------------------------------
// creates a default bintree
// bintree wil be empty with its root assigned to null
// Preconditions: None
// Postconditions: constructed empty bintree
BinTree::BinTree()
{
	//assigns the root to NULL for an empty tree
	root = NULL;

}

//------------------------- Copy Constructor ---------------------------------
// creates a bintree from passed bintree
// creates a bintree with equal nodedata in same structure as passed tree. Memory is dynamically created for the copy
// Preconditions: passed bintree must be in order
// Postconditions: constructs implicit tree from passed tree. Contains equal nodedata
BinTree::BinTree(const BinTree & b)
{
	//recursively traverses every path of the tree and deep copies every node of the passed BinTree 
	copyHelper(root, b.root);
}

//-------------------------Destructor ---------------------------------
// destructs implict tree
// deallocates all memory stored within the tree
// Preconditions: None
// Postconditions: Implicit bintree will be deleted 
BinTree::~BinTree()
{
	//recursivily traverses every path of the tree and deletes every node in the tree
	makeEmpty();

}

bool BinTree::retrieve(const NodeData& data, NodeData*& ptrToData)
{
	//recursively traverses the BST to find the data 
	//returns false if the passed NodeData was not found and does not change the passed NodeData pointer
	//returns true if the passed NodeData is found and assigns the passed NodeData pointer to point to it
	return retrieveHelper(data, ptrToData, root);

}

int BinTree::getHeight(const NodeData & data) const
{
	//calls helper function for recursive finding of NodeData in the tree
	//traverses all paths of the tree and returns the maximum height found for the NodeData
	return getHeightHelper(data, root);

}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side; 
// hard coded displaying to standard output. 
// Preconditions: NONE 
// Postconditions: BinTree remains unchanged. 
void BinTree::displaySideways() const
{
	//displays the tree sideways
	sideways(root, 0);

}

//------------------------- operator== ---------------------------------
// Compares passed tree with implicit tree 
// traverses tree in parallel comparing each nodedata 
// Preconditions: NONE 
// Postconditions: returns true if the two trees are equivelant
bool BinTree::operator==(const BinTree & b) const
{
	if (this == &b)
	{
		//if the passed bintree is the implicit tree then simply return true
		return true;
	}
	else
	{
		//calls recursive helper function 
		//for comparing each node in the implicit tree with each node in the passed tree
		return equalityHelper(root, b.root);
	}
}

//------------------------- operator!= ---------------------------------
// Compares passed tree with implicit tree 
// traverses tree in parallel comparing each nodedata 
// Preconditions: NONE 
// Postconditions: returns false if the two trees are equivelant
bool BinTree::operator!=(const BinTree & b) const
{
	//returns the negation of the bool value returned of the operator== 
	return (!(operator==(b)));
}

//------------------------- insert ---------------------------------
// inserts the passed nodedata pointer into the tree
// traverses tree path for insertation in correct spot 
// Preconditions: tree must be sorted 
// Postconditions: passed pointer to nodedata is inserted into the tree. maintains sorted order
bool BinTree::insert(NodeData * ptr)
{
	//recursively finds place to insert NodeData in the BST 
	return insertHelper(root, ptr);

}

//------------------------- makeEmpty ---------------------------------
// makes the implicit tree empty
// traverses tree deleting each node and the NodeData stored within it
// Preconditions: NONE 
// Postconditions: tree is empty with all dynamically memory deleted (node and nodedata)
void BinTree::makeEmpty()
{
	//calls helper method, passing the root to start recursive deletion of nodes in the tree
	//all nodes in tree will be deleted and root will be assigned as to a NULL pointer
	makeEmptyHelper(root);

}

//------------------------- bstreeToArray ---------------------------------
// transfers nodedata in bintree to array in sorted order
// tranfers pointers to nodedata stored in tree to array in order and makes the tree empty
// Preconditions: array must be of size 100 filled with NULL 
// Postconditions: All nodedata stored in tree is transfered to the array in sorted order. Tree is empty after
void BinTree::bstreeToArray(NodeData* arr[])
{
	//index tracker for inserting into the array 
	int indexTracker = 0;
	bstreeToArrayHelper(arr, indexTracker, root);

}

//------------------------- arrayToBSTree ---------------------------------
// transfers nodedata from array to tree
// transfers pointers to nodedata of array to implicit bintree. maintains a balanced tree then empties array
// Preconditions: tree must be empty. array must be sorted
// Postconditions: tree contains all nodedata of array and maintains a balance. array is filled with NULL data
void BinTree::arrayToBSTree(NodeData* arr[])
{
	//makes the implicit tree empty for creating tree from array
	makeEmpty();
	//gets the size of the array
	int i = 0;
	while (i < 100 && arr[i] != NULL)
	{

		i++;
	}

	if (i > 0)
	{
		arrayToBSTreeHelper(arr, root, 0, i - 1);
	}
}

//------------------------- operator= ---------------------------------
// assigns the passed tree to the implicit tree
// makes the implicit tree empty and then copies the passed tree to the implicit tree in dynamic memory
// Preconditions: NONE 
// Postconditions: the implicit tree is a deep copy of the passed tree
BinTree & BinTree::operator=(const BinTree & b)
{
	//if the passed bintree is the same as the implicit tree then there is no need for assignment
	if (this != &b)
	{
		//empties the implicit tree
		makeEmpty();

		//copies the passed tree to the empty implicit tree
		copyHelper(root, b.root);

		//returns the implicit list for further assignment
		return *this;
	}
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways 
// Preconditions: NONE 
// Postconditions: BinTree remains unchanged. 
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);
		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}
		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}

}

//------------------------- insertHelper ---------------------------------
// Recursive helper function for inserting
// Traverses tree by comparing data passed with tree data and inserts passed data into correct spot
// Preconditions: BST must be in ordered structure  
// Postconditions: passed NodeData is inserted into the BST by order
bool BinTree::insertHelper(Node *& current, NodeData* data)
{
	//
	if (current == NULL)	// data is at the location to insert
	{

		// creates a new node to insert into the binary tree at current location  
		current = new Node();

		// assigns nodes data to passed NodeData and its left and right to NULL 
		current->data = data;
		current->left = NULL;
		current->right = NULL;

		//data has been inserted, therefore return true
		return true;

	}
	else if (*(data) < *(current->data))	// data should be inserted to the left of current node
	{
		insertHelper(current->left, data);
	}
	else if (*(data) > *(current->data))	//data should be inserted to the right of the current node
	{
		insertHelper(current->right, data);
	}
	else
	{
		// the data is equal to the currents data, 
		// therefore return false as it is not to be inserted
		return false;
	}
}

//------------------------- makeEmptyHelper ---------------------------------
// Recursive helper function for makeEmpty
// Traverses tree deleting leaves recursively
// Preconditions: None
// Postconditions: Tree will be empty. All of its nodes and the NodeData stored within each node is deleted
void BinTree::makeEmptyHelper(Node*& root)
{
	if (root != NULL)
	{

		//recursively gets to the leaves of the tree
		makeEmptyHelper(root->left);
		makeEmptyHelper(root->right);
		//deletes the dynamically allocated memory to the nodedata
		//and deletes the dangiling pointer to it
		delete root->data;
		root->data = NULL;
		//deletes the node and sets the pointer 
		delete root;
		root = NULL;

	}

}

//------------------------- copyHelper ---------------------------------
// Recursive helper function for copying other bintree to this bintree
// Traverses passed tree (by node) adding nodes and nodedata created in dynamic memory to implicit tree
// Preconditions: Implicit tree must be empty
// Postconditions: implicit tree will contain equivelent structure to the passed tree (by node)
void BinTree::copyHelper(Node *& thisCurrent, const Node* const copyCurrent)
{
	if (copyCurrent == NULL)	//passed pointer to node to copy is NULL
	{

		//if the pointer to the copy node is NULL 
		//than implicit pointer must also point to NULL
		thisCurrent = NULL;

	}
	else
	{

		//creates a new node to be pointed to for implicit tree
		//and copies the data of the copy nodes data to it
		thisCurrent = new Node();
		thisCurrent->data = new NodeData(*(copyCurrent->data));

		//recursive call to copy constructor 
		//for further copying of passed nodes left and right 
		copyHelper(thisCurrent->left, copyCurrent->left);
		copyHelper(thisCurrent->right, copyCurrent->right);

	}
}

//------------------------- equalityHelper ---------------------------------
// Recursive helper function for overloaded equality operators 
// Traverses trees parrallely, testing each node for equality
// Preconditions: None
// Postconditions: returns true if passed trees (by roots) are equal
bool BinTree::equalityHelper(const Node* const thisCurrent, const Node* const passedCurrent) const
{
	//if both passed pointers are not NULL
	if (thisCurrent == NULL && passedCurrent == NULL)
	{
		//recursion has reached passed the leaves
		//therefore the path followed is 
		return true;

	}
	else if (thisCurrent != NULL && passedCurrent != NULL)
	{
		//returns the result of comparing the Node's NodeData and recursive calls for further comparisons  
		//because of short circuit AND operator, recursive calls will not be called if Node's NodeData is not equivelant
		return(*(thisCurrent->data) == *(passedCurrent->data) && equalityHelper(thisCurrent->left, passedCurrent->left) && equalityHelper(thisCurrent->right, passedCurrent->right));

	}
	else
	{
		//one of the parallel Node pointers is assigned to NULL and the other is not
		//therefore the two BinTrees are not equal and return false
		return false;

	}

}

//------------------------- getHeightHelper ---------------------------------
// Recursive helper function for getHeight
// Traverses tree to find the passed nodedata for height information and returns the maximum height of each path of the tree
// Preconditions: None
// Postconditions: returns the height of the passed nodedata
int BinTree::getHeightHelper(const NodeData& data, const Node* const root) const
{
	if (root == NULL)
	{
		//At the end of the tree, NodeData was not found path of tree
		//therefore return 0
		return 0;
	}
	else if (*(root->data) == data)
	{
		//NodeData is found in the tree at current Node
		//therefore return the count from this node down
		//by calling helper function that returns max levels down from here
		return getHeightHelperHelper(data, root, 0);
	}
	else
	{
		//recursively find the NodeData for each branch of the root
		//
		int leftBranch = getHeightHelper(data, root->left);
		int rightBranch = getHeightHelper(data, root->right);

		//return the maximum of the height found for the NodeData found from each branch
		return(leftBranch > rightBranch ? leftBranch : rightBranch);
	}
}

//------------------------- getHeightHelperHelper ---------------------------------
// Recursive helper function for getHeight
// Traverses from found nodedata node down counting the path to its lowest leaf
// Preconditions: None
// Postconditions: returns the height of passed nodedata
int BinTree::getHeightHelperHelper(const NodeData & data, const Node * const root, int count) const
{
	if (root == NULL)
	{
		//At the end of the tree 
		//therefore return the count of the levels from NodeData to here
		return count;
	}
	else
	{
		//recursively find the height of the NodeData for each branch of the root
		//incrementing count by 1 each level down
		int leftBranch = getHeightHelperHelper(data, root->left, count + 1);
		int rightBranch = getHeightHelperHelper(data, root->right, count + 1);

		//return the maximum of the height found for the NodeData found from each branch
		return(leftBranch > rightBranch ? leftBranch : rightBranch);
	}
}

//------------------------- retrieveHelper ---------------------------------
// Recursive helper function for retrieve
// Traverses tree to find the nodedata to retrieve
// Preconditions: None
// Postconditions: returns a pointer to the passed nodedata if it is the tree
bool BinTree::retrieveHelper(const NodeData & data, NodeData *& ptrToData, const Node* const root)
{

	if (root == NULL)
	{
		//reached the end of the tree and NodeData was not found
		//therefore return false
		return false;
	}
	else if (data == *(root->data))
	{
		//assign the passed pointer to point to found NodeData to found NodeData
		ptrToData = root->data;

		//return true as the NodeData was found and is pointed to by the passed pointer
		return true;
	}
	else if (data < *(root->data))
	{
		//passed data to retrieve is less than the data pointed to by root
		//therefore recursive traverse left of the tree
		return retrieveHelper(data, ptrToData, root->left);
	}
	else
	{
		//passed data to retrieve is greater than the data pointed to by root
		//therefore recursive traverse the right path of the tree
		return retrieveHelper(data, ptrToData, root->right);
	}

}

//------------------------- overloadedOutputHelper ---------------------------------
// Recursive helper function for the overloaded output operator
// Traverses tree in inorder traversal outputing the nodedata of each node
// Preconditions: None
// Postconditions: passed ostream will be streamed each of the nodedata's of the tree in inorder traversal
void BinTree::overloadedOutputHelper(ostream & output, const Node* const root) const
{
	if (root != NULL)
	{
		//inorder traversal of tree
		//streams out NodeData to ostream refrence 
		overloadedOutputHelper(output, root->left);
		output << *(root->data) << ' ';
		overloadedOutputHelper(output, root->right);
	}
}

//------------------------- bstreeToArrayHelper ---------------------------------
// Recursive helper function for bstreeToArray
// inserts pointers to nodedata of tree to array and than empties tree
// Preconditions: array passed must be of size no greater than 100 and contain all NULL values, bintree must be in sorted order
// Postconditions: nodedata from tree will be pointed to by the array in sorted order. Tree will be empty
void BinTree::bstreeToArrayHelper(NodeData* arr[], int& indexTracker, Node*& root)
{
	if (root != NULL)
	{
		//inorder taversal for inserting into the array
		bstreeToArrayHelper(arr, indexTracker, root->left);
		//assign array element at index tracked to the roots data
		//and increment index
		arr[indexTracker] = root->data;
		indexTracker++;
		//inorder traversal for right path of tree
		bstreeToArrayHelper(arr, indexTracker, root->right);
		//deletes root and assigns root to a NULL pointer
		delete root;
		root = NULL;
	}
}

//------------------------- arrayToBSTreeHelper ---------------------------------
// Recursive helper function for arrayToBSTree
// insertes all nodedata pointed to by the array into the tree
// Preconditions: array passed must be of size no greater than 100 and be sorted
// Postconditions: tree will contain all Nodedata pointed to by the array. tree will be balanced 
void BinTree::arrayToBSTreeHelper(NodeData* arr[], Node*& root, int low, int high)
{
	//finds the balancing index of the passed sorted array to insert NodeData* 
	int mid = (low + high) / 2;
	//creates new node for insertation at root
	//assigns roots data to the NodeData pointer at array 
	if (high >= low)
	{
		root = new Node();
		root->data = arr[mid];
		root->left = NULL;
		root->right = NULL;
		//assigns the element of the array to NULL after NodeData pointer of element was inserted into the tree
		arr[mid] = NULL;
		//recursivily insertests from array to BST maintaining balance 
		arrayToBSTreeHelper(arr, root->left, low, mid - 1);
		arrayToBSTreeHelper(arr, root->right, mid + 1, high);

	}
}

//------------------------- operator<< ---------------------------------
// overloaded operator<< 
// outputs tree in inorder sequence
// Preconditions: None
// Postconditions: outputs tree in inorder sequence. returns ostream for further outputing 
ostream & operator<<(ostream& output, const BinTree & b)
{
	//modifies ostream to hold 
	b.overloadedOutputHelper(output, b.root);
	//returns the ostream reference for further outputting 
	output << endl;
	return output;

}
