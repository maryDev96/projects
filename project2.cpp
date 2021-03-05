#include <iostream>
#include <exception>
#include <string>
#include <chrono>
#include <random>
#include <fstream>

using namespace std; 

void printDebug(int* arr, int size)
{
	cout << "\n";
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
}

void makeNearlySorted(int* arr, int size)
{
	int spoiler = arr[size / 2];
	for (int i = size / 6; i < size;)
	{
		arr[i] = spoiler;
		spoiler -= 30;
		i += size / 3;
	}
}

void copy(int* copyArr, int* scr, int size)
{
	for (int i = 0; i < size; i++)
		copyArr[i] = scr[i];
}

struct AVLNode {
	int val;
	int height;
	AVLNode* left;
	AVLNode* right;
	AVLNode(int x) {
		val = x;
		left = right = nullptr;
		height = 1;
	}
};

int subtreeHeight(AVLNode* ptr)
{
	if (ptr == nullptr)
		return 0;
	else
		return ptr->height;
}

int getBalance(AVLNode* ptr)
{
	return subtreeHeight(ptr->right) - subtreeHeight(ptr->left);
}

void setBalance(AVLNode* ptr)
{
	ptr->height = 1 + max(subtreeHeight(ptr->left), subtreeHeight(ptr->right));
}

AVLNode* rightRotate(AVLNode* ptr)
{
	AVLNode* newPtr = ptr->left;
	ptr->left = newPtr->right;
	newPtr->right = ptr;
	setBalance(ptr);
	setBalance(newPtr);

	return newPtr;
}

AVLNode* leftRotate(AVLNode* ptr)
{
	AVLNode* newPtr = ptr->right;
	ptr->right = newPtr->left;
	newPtr->left = ptr;
	setBalance(ptr);
	setBalance(newPtr);

	return newPtr;
}


AVLNode* insert(AVLNode* parent, int x) {
	if (parent == nullptr)
		return new AVLNode(x);

	if (x < parent->val)
		parent->left = insert(parent->left, x);
	else if (x > parent->val)
		parent->right = insert(parent->right, x);

	setBalance(parent);

	if (getBalance(parent) == 2)
	{
		if (getBalance(parent->right) < 0)
			parent->right = rightRotate(parent->right);
		return leftRotate(parent);
	}

	if (getBalance(parent) == -2)
	{
		if (getBalance(parent->left) > 0)
			parent->left = leftRotate(parent->left);
		return rightRotate(parent);
	}

	return parent;
}


void printValue(AVLNode* node) {
	if (node == nullptr)
		cout << "nullptr";
	else
		cout << node->val;
	cout << "\n";
}

void printTree(AVLNode* node, bool isRight, string beginChar) {
	if (node != nullptr)
		printTree(node->left, false, beginChar + (isRight ? "  |      " : "         "));
	cout << beginChar;
	if (isRight)
		cout << "  '-";
	else
		cout << "  ,-";
	cout << "-----> ";
	printValue(node);
	if (node != nullptr)
		printTree(node->right, true, beginChar + (isRight ? "         " : "  |      "));
}

void printTree(AVLNode* node)
{
	if (node != nullptr)
	{
		printTree(node->left, false, "");
		printValue(node);
		printTree(node->right, true, "");
	}
	else
		throw logic_error("\nThe binary tree is empty!");
}

void delete_tree(AVLNode* node)
{
	if (node == nullptr)
		return;
	//cout << "\nDeleting tree" << endl;
	delete_tree(node->left);
	delete_tree(node->right);
	delete node;
}

bool search(AVLNode* parent, int x)
{
	while (parent != nullptr)
	{
		if (x < parent->val)
			parent = parent->left;
		else if (x > parent->val)
			parent = parent->right;
		else if (x == parent->val)
			return true;
	}

	return false;
}


struct Node {
	int value = 0;
	Node* left = nullptr;
	Node* right = nullptr;
};


struct BST {
private:
	Node* root = nullptr;
public:
	BST() {
		root = new Node;
		root->value = 0;
		root->left = nullptr;
		root->right = nullptr;
	}

	BST(int x) {
		root = new Node;
		root->value = x;
		root->left = nullptr;
		root->right = nullptr;
	}

	void insert(int x) {
		Node* parent = nullptr;
		Node* ptr = root;

		while (ptr != nullptr)
		{
			if (x < ptr->value)
			{
				parent = ptr;
				ptr = ptr->left;
			}
			else
			{
				parent = ptr;
				ptr = ptr->right;
			}
		}

		Node* inserted = new Node;
		inserted->value = x;

		if (parent == nullptr)
			root = inserted;
		else
		{
			if (x < parent->value)
				parent->left = inserted;
			else
				parent->right = inserted;
		}
	}

	bool search(int x)
	{
		Node* parent = nullptr;
		Node* ptr = root;
		while (ptr != nullptr)
		{
			if (x < ptr->value)
			{
				parent = ptr;
				ptr = ptr->left;
			}
			else if (x > ptr->value)
			{
				parent = ptr;
				ptr = ptr->right;
			}
			else if (x == ptr->value)
				return true;
		}

		return false;
	}

	void printValue(Node* node) {
		if (node == nullptr)
			cout << "nullptr";
		else
			cout << node->value;
		cout << "\n";
	}

	void printTree(Node* node, bool isRight, string beginChar) {
		if (node != nullptr)
			printTree(node->left, false, beginChar + (isRight ? "  |      " : "         "));
		cout << beginChar;
		if (isRight)
			cout << "  '-";
		else
			cout << "  ,-";
		cout << "-----> ";
		printValue(node);
		if (node != nullptr)
			printTree(node->right, true, beginChar + (isRight ? "         " : "  |      "));
	}

	void printTree()
	{
		if (root != nullptr)
		{
			printTree(root->left, false, "");
			printValue(root);
			printTree(root->right, true, "");
		}
		else
			throw logic_error("\nThe binary tree is empty!");
	}

	void delete_tree(Node* node)
	{
		if (node == NULL)
			return;
		delete_tree(node->left);
		delete_tree(node->right);
		delete node;
	}

	void delete_tree()
	{
		if (root == NULL)
			return;
		delete_tree(root);
	}
};

const int start = -2000;
const int limit = 2000;
const int maxTimes = 100;
const int needleExcluded = 2001;

int main()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution <int> dist(start, limit);
	using chrono::nanoseconds;
	ofstream resultsInsert("results_insert_proj2.txt");
	ofstream resultsSearchExists("results_search_exists_proj2.txt");
	ofstream resultsSearchAbsent("results_search_absent_proj2.txt");
	resultsInsert << "size    bstrandom   bstordered   nearlyord_bst      avlrandom   avlordered   nearlyord_avl" << endl;
	resultsSearchExists << "size    bstrandom   bstordered   nearlyord_bst      avlrandom   avlordered   nearlyord_avl" << endl;
	resultsSearchAbsent << "size    bstrandom   bstordered   nearlyord_bst      avlrandom   avlordered   nearlyord_avl" << endl;
	nanoseconds bstRandom(0);
	nanoseconds avlRandom(0);
	nanoseconds bstOrdered(0);
	nanoseconds avlOrdered(0);
	nanoseconds nearlyOrd_bst(0);
	nanoseconds nearlyOrd_avl(0);
	nanoseconds bstRandomSearchInclude(0);
	nanoseconds avlRandomSearchInclude(0);
	nanoseconds bstOrderedSearchInclude(0);
	nanoseconds avlOrderedSearchInclude(0);
	nanoseconds nearlyOrd_bstSearchInclude(0);
	nanoseconds nearlyOrd_avlSearchInclude(0);
	nanoseconds bstRandomSearchExclude(0);
	nanoseconds avlRandomSearchExclude(0);
	nanoseconds bstOrderedSearchExclude(0);
	nanoseconds avlOrderedSearchExclude(0);
	nanoseconds nearlyOrd_bstSearchExclude(0);
	nanoseconds nearlyOrd_avlSearchExclude(0);


	for (int size = 50; size <= 2000; size += 50)
	{
		bstRandom = chrono::nanoseconds::zero();
		avlRandom = chrono::nanoseconds::zero();
		bstOrdered = chrono::nanoseconds::zero();
		avlOrdered = chrono::nanoseconds::zero();
		nearlyOrd_bst = chrono::nanoseconds::zero();
		nearlyOrd_avl = chrono::nanoseconds::zero();
		bstRandomSearchInclude = chrono::nanoseconds::zero();
		avlRandomSearchInclude = chrono::nanoseconds::zero();
		bstOrderedSearchInclude = chrono::nanoseconds::zero();
		avlOrderedSearchInclude = chrono::nanoseconds::zero();
		nearlyOrd_bstSearchInclude = chrono::nanoseconds::zero();
		nearlyOrd_avlSearchInclude = chrono::nanoseconds::zero();
		bstRandomSearchExclude = chrono::nanoseconds::zero();
		avlRandomSearchExclude = chrono::nanoseconds::zero();
		bstOrderedSearchExclude = chrono::nanoseconds::zero();
		avlOrderedSearchExclude = chrono::nanoseconds::zero();
		nearlyOrd_bstSearchExclude = chrono::nanoseconds::zero();
		nearlyOrd_avlSearchExclude = chrono::nanoseconds::zero();

		int* original = new int[size];
		for (int i = 0; i < size; i++)
			original[i] = i;

		int* arrInt = new int[size];

		for (int t = 0; t < maxTimes; t++)
		{
			for (int i = 0; i < size; i++)
				original[i] = dist(gen);

			
			copy(arrInt, original, size);
			int needle = arrInt[size / 3];

			//BST insert for random arrays
			BST treeBST(arrInt[0]);
			for (int i = 1; i < size - 1; i++)
				treeBST.insert(arrInt[i]);
			auto start = chrono::steady_clock::now();
			treeBST.insert(arrInt[size - 1]);
			auto end = chrono::steady_clock::now();
			bstRandom += end - start;

			//BST for searchig if the element exists for random arrays
			start = chrono::steady_clock::now();
			treeBST.search(needle);
			end = chrono::steady_clock::now();
			bstRandomSearchInclude += end - start;
			
			//BST for searchig if the element does not exist for random arrays
			start = chrono::steady_clock::now();
			treeBST.search(needleExcluded);
			end = chrono::steady_clock::now();
			bstRandomSearchExclude += end - start;

			treeBST.delete_tree();
			sort(arrInt, arrInt + size);

			//BST insert for sorted arrays
			BST treeBSTSort(arrInt[0]);
			for (int i = 1; i < size - 1; i++)
				treeBSTSort.insert(arrInt[i]);
			start = chrono::steady_clock::now();
			treeBSTSort.insert(arrInt[size - 1]);
			end = chrono::steady_clock::now();
			bstOrdered += end - start;

			//BST for searchig if the element exists for sorted arrays
			start = chrono::steady_clock::now();
			treeBSTSort.search(needle);
			end = chrono::steady_clock::now();
			bstOrderedSearchInclude += end - start;

			//BST for searchig if the element does not exist for sorted arrays
			start = chrono::steady_clock::now();
			treeBSTSort.search(needleExcluded);
			end = chrono::steady_clock::now();
			bstOrderedSearchExclude += end - start;

			treeBSTSort.delete_tree();
			makeNearlySorted(arrInt, size);

			//BST insert for nearly sorted arrays
			BST treeBSTNearlySort(arrInt[0]);
			for (int i = 1; i < size - 1; i++)
				treeBSTNearlySort.insert(arrInt[i]);
			start = chrono::steady_clock::now();
			treeBSTNearlySort.insert(arrInt[size - 1]);
			end = chrono::steady_clock::now();
			nearlyOrd_bst += end - start;

			//BST for searchig if the element exists for nearly sorted arrays
			start = chrono::steady_clock::now();
			treeBSTNearlySort.search(needle);
			end = chrono::steady_clock::now();
			nearlyOrd_bstSearchInclude += end - start;

			//BST for searchig if the element does not exist for nearly sorted arrays
			start = chrono::steady_clock::now();
			treeBSTNearlySort.search(needleExcluded);
			end = chrono::steady_clock::now();
			nearlyOrd_bstSearchExclude += end - start;

			treeBSTNearlySort.delete_tree();

			
			copy(arrInt, original, size);

			//AVL insert for random arrays
			AVLNode* treeAVL = new AVLNode(original[0]);
			for (int i = 1; i < size - 1; i++)
				insert(treeAVL, arrInt[i]);
			start = chrono::steady_clock::now();
			insert(treeAVL, arrInt[size - 1]);
			end = chrono::steady_clock::now();
			avlRandom += end - start;

			//AVL for searchig if the element exists for random arrays
			start = chrono::steady_clock::now();
			search(treeAVL, needle);
			end = chrono::steady_clock::now();
			avlRandomSearchInclude += end - start;

			//AVL for searchig if the element does not exist for random arrays
			start = chrono::steady_clock::now();
			search(treeAVL, needleExcluded);
			end = chrono::steady_clock::now();
			avlRandomSearchExclude += end - start;

			delete_tree(treeAVL);
			sort(arrInt, arrInt + size);

			//AVL insert for sorted arrays
			AVLNode* treeAVLSort = new AVLNode(arrInt[0]);
			for (int i = 1; i < size - 1; i++)
				insert(treeAVLSort, arrInt[i]);
			start = chrono::steady_clock::now();
			insert(treeAVLSort, arrInt[size - 1]);
			end = chrono::steady_clock::now();
			avlOrdered += end - start;

			//AVL for searchig if the element exists for sorted arrays
			start = chrono::steady_clock::now();
			search(treeAVLSort, needle);
			end = chrono::steady_clock::now();
			avlOrderedSearchInclude += end - start;

			//AVL for searchig if the element does not exist for sorted arrays
			start = chrono::steady_clock::now();
			search(treeAVLSort, needleExcluded);
			end = chrono::steady_clock::now();
			avlOrderedSearchExclude += end - start;

			delete_tree(treeAVLSort);
			makeNearlySorted(arrInt, size);

			//AVL insert for nearly sorted arrays
			AVLNode* treeAVLNearlySort = new AVLNode(arrInt[0]);
			for (int i = 1; i < size - 1; i++)
				insert(treeAVLNearlySort, arrInt[i]);
			start = chrono::steady_clock::now();
			insert(treeAVLNearlySort, arrInt[size - 1]);
			end = chrono::steady_clock::now();
			nearlyOrd_avl += end - start;

			//AVL for searchig if the element exists for nearly sorted arrays
			start = chrono::steady_clock::now();
			search(treeAVLNearlySort, needle);
			end = chrono::steady_clock::now();
			nearlyOrd_avlSearchInclude += end - start;

			//AVL for searchig if the element does not exist for nearly sorted arrays
			start = chrono::steady_clock::now();
			search(treeAVLNearlySort, needleExcluded);
			end = chrono::steady_clock::now();
			nearlyOrd_avlSearchExclude += end - start;
			
			delete_tree(treeAVLNearlySort);
		}

		resultsInsert << size << "       " << bstRandom.count() / maxTimes << "        " << bstOrdered.count() / maxTimes << "              "
			<< nearlyOrd_bst.count() / maxTimes << "            "<< avlRandom.count() / maxTimes << "           " << avlOrdered.count() / maxTimes << "         "
			<< nearlyOrd_avl.count() / maxTimes << endl;

		resultsSearchExists << size << "       " << bstRandomSearchInclude.count() / maxTimes << "        " << bstOrderedSearchInclude.count() / maxTimes << "              "
			<< nearlyOrd_bstSearchInclude.count() / maxTimes << "            " << avlRandomSearchInclude.count() / maxTimes << "           " << avlOrderedSearchInclude.count() / maxTimes << "         "
			<< nearlyOrd_avlSearchInclude.count() / maxTimes << endl;
		resultsSearchAbsent << size << "       " << bstRandomSearchExclude.count() / maxTimes << "        " << bstOrderedSearchExclude.count() / maxTimes << "              "
			<< nearlyOrd_bstSearchExclude.count() / maxTimes << "            " << avlRandomSearchExclude.count() / maxTimes << "           " << avlOrderedSearchExclude.count() / maxTimes << "         "
			<< nearlyOrd_avlSearchExclude.count() / maxTimes << endl;

		delete[] arrInt;
		delete[] original;
		
	}

	resultsInsert.close();
	resultsSearchExists.close();
	resultsSearchAbsent.close();

	return 0;
}

