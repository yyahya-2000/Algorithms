// B_Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream> 
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// our b-tree node
class BTreeNode
{
	pair<int, int>* keysValues;  // dynamic array of keys and values
	int t;     //number of keys from the user
	BTreeNode** children; // dynamic array of children pointers 
	int cntKeys;     // number of keys 
	bool isLeaf; // if nood is leaf
public:
	//constructor
	BTreeNode(int given_t, bool is_leaf)
	{
		t = given_t;
		isLeaf = is_leaf;
		keysValues = new pair<int, int>[2 * t - 1];
		children = new BTreeNode * [2 * t];
		cntKeys = 0;
	}

	pair<int, int>* getKeysValues() {
		return keysValues;
	}

	int getN() {
		return cntKeys;
	}

	// insert new key when the node is non-full  
	void insertNonFull(pair<int, int> kv)
	{
		// rightmost index 
		int i = cntKeys - 1;
		if (isLeaf == true) // if node is leaf
		{
			while (i >= 0 && keysValues[i].first > kv.first)
			{
				keysValues[i + 1] = keysValues[i];
				i--;
			}
			keysValues[i + 1] = kv;
			cntKeys = cntKeys + 1;
		}
		else // if this node is not leaf 
		{
			// find the child which will have the new key and value 
			while (i >= 0 && keysValues[i].first > kv.first)
				i--;
			if (children[i + 1]->cntKeys == 2 * t - 1)
			{
				// split the child, if he's full 
				splitChild(i + 1, children[i + 1]);
				if (keysValues[i + 1].first < kv.first)
					i++;
			}
			children[i + 1]->insertNonFull(kv);
		}
	}

	//Utility function to split the y child of this node.i - index y in the child array C[].
	//The child element y must be filled when this function is called
	void splitChild(int i, BTreeNode* y)
	{
		BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
		z->cntKeys = t - 1; 
		for (int j = 0; j < t - 1; j++)
			z->keysValues[j] = y->keysValues[j + t];

		if (y->isLeaf == false)
		{
			for (int j = 0; j < t; j++)
				z->children[j] = y->children[j + t];
		}
		y->cntKeys = t - 1;
		for (int j = cntKeys; j >= i + 1; j--)
			children[j + 1] = children[j];
		children[i + 1] = z;
		for (int j = cntKeys - 1; j >= i; j--)
			keysValues[j + 1] = keysValues[j];
		keysValues[i] = y->keysValues[t - 1];
		cntKeys = cntKeys + 1;
	}

	//search a key 
	BTreeNode* search(int k)
	{
		int i = 0;
		while (i < cntKeys - 1 && k > keysValues[i].first)
			i++;
		if (keysValues[i].first == k)
			return this;
		if (isLeaf == true)
			return NULL;
		return children[i]->search(k);
	}

	friend class BTree;
};

//our tree
class BTree
{
	BTreeNode* root;
	int t;
public:
	// Constructor
	BTree(int _t)
	{
		root = NULL;  t = _t;
	}

	// function to search a key in this tree 
	BTreeNode* search(int k)
	{
		return (root == NULL) ? NULL : root->search(k);
	}

	// The main function that inserts a new key in this B-Tree 
	void insert(pair<int, int> kv)
	{
		// If tree is empty 
		if (root == NULL)
		{
			root = new BTreeNode(t, true);
			root->keysValues[0] = kv;
			root->cntKeys = 1;
		}
		else // If tree is not empty 
		{
			// If root is full
			if (root->cntKeys == 2 * t - 1)
			{
				BTreeNode* s = new BTreeNode(t, false);
				s->children[0] = root;
				s->splitChild(0, root);
				int i = 0;
				if (s->keysValues[0].first < kv.first)
					i++;
				s->children[i]->insertNonFull(kv);


				root = s;
			}
			else
				root->insertNonFull(kv);
		}
	}
};


//splitting the input line 
void split_line(string& line, string* subline) {
	if (line[line.length() - 1] == ' ') {
		line = line.substr(0, line.length() - 1);
	}
	size_t current, previous = 0;
	current = line.find(' ');

	size_t index = 0;
	while (current != string::npos) {
		*(subline + index) = line.substr(previous, current - previous);
		previous = current + 1;
		current = line.find(' ', previous);
		index++;
	}
	*(subline + index) = line.substr(previous, current - previous);
}

//reading test from the test file and writting the answer
void read_test_and_write_result_immediately(int t, string testPath, string answerPath) {
	BTree bTree(t);
	try {
		ifstream myTest;
		myTest.open(testPath);

		ofstream myAnswer;
		myAnswer.open(answerPath);

		string line = "";

		if (!myTest) {
			cout << "Unable to open file";
			exit(1);
		}
		string subline[3];
		while (getline(myTest, line))
		{
			split_line(line, subline);
			if (subline[0] == "insert") {
				if (bTree.search(stoi(subline[1])) == NULL) {
					pair<int, int > insertMe;
					insertMe.first = stoi(subline[1]);
					insertMe.second = stoi(subline[2]);
					bTree.insert(insertMe);
					myAnswer << "true" << endl;
					continue;
				}
				myAnswer << "false" << endl;
			}
			else if (subline[0] == "find") {
				int lookForMe = stoi(subline[1]);
				int value = NULL;
				BTreeNode* node = bTree.search(stoi(subline[1]));
				if (node == NULL) {
					myAnswer << "null" << endl;
					continue;
				}
				else {
					for (int i = 0; i < node->getN(); i++)
					{
						if (lookForMe == node->getKeysValues()[i].first) {
							value = node->getKeysValues()[i].second;
							break;
						}
					}
					myAnswer << value << endl;
				}
			}
		}
		myTest.close();
		myAnswer.close();
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
}

int main(int argc, char** args)
{
	try {
		read_test_and_write_result_immediately(stoi(args[1]), args[2], args[3]);
	}
	catch (exception) {
		cout << "wrong input!" << endl;
		cout << "the right input is: int_positive_value input/test{1-5}.txt output/answer{1-5}.txt " << endl;
	}
	return 0;
}
