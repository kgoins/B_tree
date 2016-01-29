#include "bTree.h"
using namespace std;

string bTree::toStr() {
	if (!changed)
		return toString;
	if (changed && root != 0) {
        toString = "";
		toString = root->traverse(&toString);
    }

	changed = false;
	return toString;
}

// search for a key in tree
bool bTree::find(string key, string* value) {
	return (root == 0) ? 0 : root->find(key, value);
	changed = false;
}

// insert key-value pair in tree
void bTree::insert(string key, string value) {

	if (root == 0) {
		// Create root
		root = new bTreeNode(degree, true);

		//insert key and value
		root->keys[0] = key;
		root->values[0] = value;
		root->active = 1;  // Update number of elements in root
	}
	else { 

		// push new root up
		if (root->active == degree -1) {
			bTreeNode* newRoot = new bTreeNode(degree, false);

			newRoot->children[0] = root;

			newRoot->split(0, root);

            // give new key to correct child
			int index = 0;
			if (newRoot->keys[0] < key)
				index++;
			newRoot->children[index]->insertElement(key, value);

			root = newRoot;
		}

		// if root is not full
		else { root->insertElement(key, value);}
	}
	changed = true;
}

bool bTree::delete_key(string key) {
	if (!root)
		return false;

	root->remove(key);

	// If the root node has 0 elements, make its first child as the new root
	//  if it has a child, otherwise set root as 0
	if (root->active == 0) {
		bTreeNode* temp = root;
		if (root->leaf)
			root = 0;
		else
			root = root->children[0];

		// remove old root
		delete temp;
	}
	changed = true;
	return true;
}

///////////////////////////
/// *START bTreeNODE* ////
/////////////////////////


// A function to remove the key from the sub-tree rooted with this node
bool bTreeNode::remove(string key) {

	// find key's index in node or which child it's in
	int id = 0;
	while (id < active && keys[id] < key)
			++id;

	// if the key to be removed is in this node
	if (id < active && keys[id] == key) 
        (leaf) ? removeFromLeaf(id) : removeFromNonLeaf(id);

	//if it's not in this node
	else {
		if (leaf)
			return false;

		// flag indicates whether the key is in right-most child
		bool flag = (id == active) ? true : false;

		if (children[id]->active < degree/2)
			fill(id); // make sure target has min # of elements

		if (flag && id > active)
			children[id -1]->remove(key);
		else
			children[id]->remove(key);
    }
	return true;
}

void bTreeNode::removeFromLeaf(int id) {

	// move all elements after id one place backward
	for (int i = id +1; i < active; ++i) {
		keys[i-1] = keys[i];
		values[i-1] = values[i];
	}

	active--;

	return;
}

void bTreeNode::removeFromNonLeaf(int id) {

	string key = keys[id];

	if (children[id]->active >= degree/2) {
		string prev = getPrev(id);
		keys[id] = prev;
		children[id]->remove(prev);
	}

	else if (children[id +1]->active >= degree/2) {
		string succ = getNext(id);
		keys[id] = succ;
		children[id +1]->remove(succ);
	}

	else {
		merge(id);
		children[id]->remove(key);
	}

	return;
}

// return last key of rightmost leaf (after id) of this node
string bTreeNode::getPrev(int id) {

	bTreeNode* current = children[id];
	while (!current->leaf)
		current = current->children[current->active];

	return current->keys[current->active -1];
}

// return first key of leftmost node (before id) of this node
string bTreeNode::getNext(int id) {

	bTreeNode* current = children[id +1];
	while (!current->leaf)
		current = current->children[0];

	return current->keys[0];
}

// fill target node to min number of elements
void bTreeNode::fill(int id) {

    // select either left or right child to borrow elements from
    // depending on which has available elements to take
	if (id != 0 && children[id -1]->active >= (degree/2)-1)
		fromPrev(id);

	else if (id != active && children[id +1]->active >= (degree/2)-1)
		fromNext(id);

    // if neither have extra, merge right (or left if needed)
	else {
		if (id != active)
			merge(id);
		else
			merge(id -1);
	}
	return;
}

void bTreeNode::fromPrev(int id) {

	bTreeNode* child = children[id];
	bTreeNode* sibling = children[id -1];

	// move all keys one step ahead
	for (int i = child->active -1; i >= 0; --i) {
		child->keys[i +1] = child->keys[i];
		child->keys[i +1] = child->keys[i];
	}

	// if children[id] is not a leaf move all child pointers one step ahead
	if (!child->leaf) {
		for (int i = child->active; i >= 0; --i)
			child->children[i +1] = child->children[i];
	}

	child->keys[0] = keys[id -1];
	child->values[0] = values[id -1];

	if (!leaf)
		child->children[0] = sibling->children[sibling->active];

	keys[id -1] = sibling->keys[sibling->active -1];
	values[id -1] = sibling->values[sibling->active -1];

	child->active += 1;
	sibling->active -= 1;

	return;
}

// steal key from right child and pace in this node
void bTreeNode::fromNext(int id) {

	bTreeNode* child = children[id];
	bTreeNode* sibling = children[id +1];

	// elements[id] is inserted as the last key in children[id]
	child->keys[(child->active)-1] = keys[id];
	child->values[(child->active)-1] = values[id];

	// right child's first child is inserted as the last child
	// of children[id]
	if (!(child->leaf))
		child->children[(child->active) +1] = sibling->children[0];

	keys[id] = sibling->keys[0];
	values[id] = sibling->values[0];

	// move elements in sibling one step back
	for (int i = 1; i < sibling->active; ++i) {
		sibling->keys[i -1] = sibling->keys[i];
		sibling->values[i -1] = sibling->values[i];
	}

	// move child pointers one step back
	if (!sibling->leaf) {
		for (int i = 1; i <= sibling->active; ++i)
			sibling->children[i -1] = sibling->children[i];
	}

	child->active += 1;
	sibling->active -= 1;

	return;
}

// merge target child with it's right child
void bTreeNode::merge(int id) {

	bTreeNode* child = children[id];
	bTreeNode* sibling = children[id+1];

	child->keys[(degree/2) -1] = keys[id];
	child->values[(degree/2) -1] = values[id];

	// copy elements from right child to target child
	for (int i = 0; i < sibling->active; ++i) {
		child->keys[i + degree/2] = sibling->keys[i];
		child->values[i + degree/2] = sibling->values[i];
	}

	// copy children from right child to target child
	if (!child->leaf) {
		for (int i = 0; i <= sibling->active; ++i)
			child->children[i + degree/2] = sibling->children[i];
	}

    // fill the gap created by moving the elements
	for (int i = id +1; i < active; ++i) {
		keys[i-1] = keys[i];
		values[i-1] = values[i];
	}

    // move all children after id+1 one step back
	for (int i = id + 2; i <= active; ++i)
		children[i -1] = children[i];

	child->active += sibling->active +1;
	active--;

	delete sibling;
}

// insert a new key in current node
// if full, pass to a node that can insert it
void bTreeNode::insertElement(string key, string value) {

	int index = active -1;

	if (leaf == true) {

		while (index >= 0 && keys[index] > key) {
			keys[index +1] = keys[index];
			values[index +1] = values[index];
			index--;
		}

		// Insert the new key at index

		keys[index +1] = key;
		values[index +1] = value;
		active++;
	}

	else { 

		// pass to the next node that might take the key
		while (index >= 0 && keys[index] > key)
			index--;

		if (children[index +1]->active == degree -1) {

			// if the child is full split it
			split(index +1, children[index +1]);

            // give new key to appropriate child
			if (keys[index +1] < key)
				index++;
		}
		children[index +1]->insertElement(key, value);
	}
}

// split the child y of this node
void bTreeNode::split(int index, bTreeNode* y) {

	// create a new node to store degree/2 elements of y
	bTreeNode* z = new bTreeNode(y->degree, y->leaf);
	z->active = (degree / 2) -1;

	// copy the last degree/2 -1 elements of y to z
	for (int j = y->active -1, i = 0; j > (degree / 2) -1; j--, i++) {
		z->keys[i] = y->keys[j];
		z->values[i] = y->values[j];

		y->active = y->active -1;
	}

	// copy the first degree/2 children of y to z
	if (y->leaf == false)
		for (int j = 0; j < (degree / 2); j++)
			z->children[j] = y->children[j];

	// create space for new child
	for (int j = active; j >= index +1; j--)
		children[j +1] = children[j];

	children[index +1] = z;

	// find location of new key and move all 
    // greater elements one space ahead
	for (int j = active -1; j >= index; j--) {
		keys[j +1] = keys[j];
		values[j +1] = values[j];
	}

	// push up y's middle key
	keys[index] = y->keys[(degree / 2) -1];
	values[index] = y->values[(degree / 2) -1];

	// delete copied keys and values from y
	y->keys[(degree / 2) -1] = "";
	y->values[(degree / 2) -1] = "";
	y->active = y->active -1;

	active = active +1;
}

// traverse the tree
string bTreeNode::traverse(string* result) {
	int i = 0;
	for (i = 0; i < active; i++) {
		if (leaf == false)
			children[i]->traverse(result); // left subtree
		*result += keys[i] + "\n"; //action (me)
	}

	if (leaf == false)
		children[i]->traverse(result); // right subtree
	return *result;
}

// find key in tree and assign it's value to 'value' if found
bool bTreeNode::find(string key, string* value) {
	int i = 0;
	while (i < active && key > keys[i])
		i++;

	if (keys[i] == key) {
        *value = values[i];
		return true;
    }

	// if this a leaf and it's not here, it's not in the tree
    if (leaf == true)
		return false;

	return children[i]->find(key, value);
}
