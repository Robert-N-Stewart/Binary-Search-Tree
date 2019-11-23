#include "bintree.h"
#include <fstream>
#include <iostream>
using namespace std;

const int ARRAYSIZE = 100;

//global function prototypes
void buildTree(BinTree&, ifstream&);      // 
void initArray(NodeData*[]);             // initialize array to NULL

int main() {
	// create file object infile and open it
	// for testing, call your data file something appropriate, e.g., inputdata.txt
	ifstream infile("inputdata.txt");
	if (!infile) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	// the NodeData class must have a constructor that takes a string
	NodeData notND("not");
	NodeData andND("and");
	NodeData sssND("sss");
	NodeData ttttND("tttt");
	NodeData oooND("ooo");
	NodeData yND("y");
	NodeData eND("e");
	NodeData mND("m");
	NodeData tND("t");

	// nodedata pointers for insertation
	NodeData* p1 = new NodeData("aaaa");
	NodeData* p2 = new NodeData("bbbb");
	NodeData* p3 = new NodeData("ooo");
	NodeData* p4 = new NodeData("ccc");
	NodeData* p5 = new NodeData("dd");
	NodeData* p6 = new NodeData("ooo");
	NodeData* p7 = new NodeData("dd");
	NodeData* p8 = new NodeData("ffff");
	NodeData* p9 = new NodeData("ggg");

	//tests default constructors
	BinTree T, T2, dup;

	//test inserting nodedata pointers into the tree
	T.insert(p1);
	T.insert(p2);
	T.insert(p3);
	T.insert(p4);
	T.insert(p5);
	// tests for invalid insertation
	bool test = T.insert(p6);

	if (!test)
	{
		cout << "correct, inseret was invalid" << endl;
	}
	else
	{
		cout << "incorrect, insert was invalid" << endl;
	}
	T.insert(p7);
	T.insert(p8);
	T.insert(p9);

	cout << "Tree Inorder:" << endl << T;             // operator<< does endl
	T.displaySideways();

	cout << endl;

	NodeData* testRetrievalPtr;

	//tests for valid retrieval
	bool rebooltest = T.retrieve(*p1, testRetrievalPtr);
	cout << *testRetrievalPtr << "  "  << *p1 <<  " <- both should be aaaa" << endl;

	if (rebooltest)
	{
		cout << "correct retrieval was a sucess" << endl;
	}
	else
	{
		cout << "incorrect retrieval was a fail" << endl;
	}

	cout << endl;

	//tests for invalid retrieval
	bool rebooltest2 = T.retrieve(yND, testRetrievalPtr);
	cout << *testRetrievalPtr <<  "<- should still be aaa      " << yND << " <-should be y" << endl;

	if (rebooltest2)
	{
		cout << "incorrect retrieval was a sucess" << endl;
	}
	else
	{
		cout << "correct retrieval was a fail" << endl;
	}


	// array for testing
	NodeData* testArr[ARRAYSIZE];
	initArray(testArr);

	cout << T;
	// tests for valid transfer to array
	cout << "should be same as above^^^" << endl;
	T.bstreeToArray(testArr);
	int i = 0;
	while (testArr[i] != NULL)
	{
		cout << *(testArr[i]) << " ";
		i++;
	}

	cout << endl;

	// should be empty
	cout << "Tree Inorder:" << endl << T;             // operator<< does endl
	T.displaySideways();
	 
	cout << "^^should be empty" << endl;
	T.arrayToBSTree(testArr);
	// should be filled again
	cout << "Tree Inorder:" << endl << T;             // operator<< does endl
	T.displaySideways();

	cout << "^^should be filled again" << endl;

	//makes empty
	T.makeEmpty();

	p1 = NULL;
	p2 = NULL;
	p3 = NULL;
	p4 = NULL;
	p5 = NULL;
	p6 = NULL;
	p7 = NULL;
	p8 = NULL;
	p9 = NULL;
	testRetrievalPtr = NULL;

	cout << "---------------------------------------------------------------"
		<< endl;

	//tests copy constructor on 
	NodeData* ndArray[ARRAYSIZE];
	initArray(ndArray);
	cout << "Initial data:" << endl << "  ";
	buildTree(T, infile);              // builds and displays initial data
	cout << endl;
	BinTree first(T);                  // test copy constructor
	dup = dup = T;                     // test operator=, self-assignment
	while (!infile.eof()) {
		cout << "Tree Inorder:" << endl << T;             // operator<< does endl
		T.displaySideways();

		// test retrieve 
		NodeData* p;                    // pointer of retrieved object
		bool found;                     // whether or not object was found in tree
		found = T.retrieve(andND, p);
		cout << "Retrieve --> and:  " << (found ? "found" : "not found") << endl;
		found = T.retrieve(notND, p);
		cout << "Retrieve --> not:  " << (found ? "found" : "not found") << endl;
		found = T.retrieve(sssND, p);
		cout << "Retrieve --> sss:  " << (found ? "found" : "not found") << endl;

		// test getHeight 
		cout << "Height    --> and:  " << T.getHeight(andND) << endl;
		cout << "Height    --> not:  " << T.getHeight(notND) << endl;
		cout << "Height    --> sss:  " << T.getHeight(sssND) << endl;
		cout << "Height    --> tttt:  " << T.getHeight(ttttND) << endl;
		cout << "Height    --> ooo:  " << T.getHeight(oooND) << endl;
		cout << "Height    --> y:  " << T.getHeight(yND) << endl;

		// test ==, and != 
		T2 = T;
		cout << "T == T2?     " << (T == T2 ? "equal" : "not equal") << endl;
		cout << "T != first?  " << (T != first ? "not equal" : "equal") << endl;
		cout << "T == dup?    " << (T == dup ? "equal" : "not equal") << endl;
		dup = T;

		// somewhat test bstreeToArray and arrayToBSTree
		T.bstreeToArray(ndArray);
		T.arrayToBSTree(ndArray);
		T.displaySideways();

		T.makeEmpty();                  // empty out the tree
		initArray(ndArray);             // empty out the array

		cout << "---------------------------------------------------------------"
			<< endl;
		cout << "Initial data:" << endl << "  ";
		buildTree(T, infile);
		cout << endl;
	}

	return 0;
}

//------------------------------- buildTree ----------------------------------
//constructs a tree from text file
// reads strings from a line, terminating when "$$" is
// encountered
// Preconditions: text file must contain "$$" for ending sequence of inputs
// Postconditions: constructs tree from text data

void buildTree(BinTree& T, ifstream& infile) {
	string s;

	for (;;) {
		infile >> s;
		cout << s << ' ';
		if (s == "$$") break;                // at end of one line
		if (infile.eof()) break;             // no more lines of data
		NodeData* ptr = new NodeData(s);     // NodeData constructor takes string
											 // would do a setData if there were more than a string

		bool success = T.insert(ptr);
		if (!success)
			delete ptr;                       // duplicate case, not inserted 
	}
}

//------------------------- InitArray ---------------------------------
// assigns each element of passed nodedata pointer array to Null
// used for arrayToBSTree and bstreeToArray tests
// Preconditions: passed array must be of size 100
// Postconditions: passed array will contain all NULL elements 

void initArray(NodeData* ndArray[]) {
	for (int i = 0; i < ARRAYSIZE; i++)
		ndArray[i] = NULL;
}
