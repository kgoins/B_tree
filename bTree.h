#ifndef bTree_H_
#define bTree_H_

#include <iostream>
#include <string>
using namespace std;

class bTreeNode {

	const int degree;  // Max number of children the node can have
	int active;        // Current number of keys
	bool leaf;         // Is true when node is leaf. Otherwise false

	string* keys;
	string* values;
	bTreeNode** children; // child pointers


    ////////////////////////////
    // System Util Functions //
    //////////////////////////

	// directly removes a key-value pair from the node's internal arrays
	void removeFromLeaf(int index);

    // performs all needed splits, merges and fills to 
    // ensure a key-value pair can be removed from a non-leaf node
	void removeFromNonLeaf(int index);

	// grabs the key from the tree that lexicographically proceeds
    // the key at index
	string getPrev(int index);

    // grabs the key from the tree that lexicographically follows
    // the key at index
	string getNext(int index);

	// fills a child node with less than (degree/2)-1
    // elements to meet the minimum number of elements required
	void fill(int index);

	// steals a key from the left child of index and places
	// it in the node at index
	void fromPrev(int index);

    // steals a key from the right child of index and places
	// it in the node at index
	void fromNext(int index);

	// merges the child of the calling node specified by index
    // with the right child of that node
	void merge(int index);

public:

	bTreeNode(int d, bool l) : degree(d), active(0), leaf(l) {
		// initialize keys and values arrays
        keys = new string[degree -1];
        values = new string[degree -1];
		for (int i = 0; i < degree - 1; ++i) {
            keys[i] = "";
            values[i] = "";
		}

		// set child pointers to 0
		children = new bTreeNode*[degree];
		for (int i = 0; i < degree; i++)
			children[i] = 0;
	}

	inline ~bTreeNode() {delete[] children;}

	// Traverses all nodes, placing each node's keys in a returned string
	string traverse(string* result);

	// Searches for key in tree
	bool find(string key, string* value);

	// inserts in place a new key-value pair into the calling node
	void insertElement(string key, string value);

	// splits the child y of this node. index is index
	// of y in this node's array of children; y must be full when this
	// function is called
	void split(int index, bTreeNode *y);

	// removes the specified key from this node; failing that, 
    // it contains logic to pass the function to the correct node
	bool remove(string key);

	friend class bTree;
};

class bTree {
	bTreeNode* root; // Pointer to root node
	int degree;  // Minimum degree
	string toString; // stores the result of toStr
	bool changed;  // true if the tree has been modified
public:

	bTree(int d) : root(0),toString(""),changed(false) {
        if (d % 2 != 0)
            d++;
        degree = d;
    }

	// returns a string containing the results of an in-order 
    // traversal of the tree
	string toStr();

	bool find(string key,string* value);

	void insert(string key, string value);

	bool delete_key(string key);
};

#endif 
