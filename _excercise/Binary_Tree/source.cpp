#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

struct Node{
	int data;
	Node *left;
	Node *right;
};

Node *root;

void initTree(int data) {
	Node *New;
	New = (Node*)(malloc(sizeof(Node)));
	root = New;
	root->data = data;
	New->left = NULL;
	New->right = NULL;
}

int gCount = 0;

Node* AddChild(Node* parent, int data) {
	
	gCount++;

	if (data < parent->data && (parent->left != NULL)) {
		AddChild(parent->left, data);
	}
	else if (data > parent->data && (parent->right != NULL)) {
		AddChild(parent->right, data);
	}
		

	Node *New;
	New = (Node*)(malloc(sizeof(Node)));
	New->left = NULL;
	New->right = NULL;
	New->data = data;
	if (parent->left == NULL && data < parent->data) {
		parent->left = New;

	}
	else if (parent->right == NULL && data > parent->data) {
		parent->right = New;

	}


	return New;
}




int main() {
	


	vector <int> keys;
	
	keys.push_back(1);
	keys.push_back(2);
	keys.push_back(3);

	if (keys.size() == 0)
		return 0;

	initTree(keys[0]);
	cout << gCount << endl;

	for (int i = 1; i < keys.size(); i++) {
		AddChild(root, keys[i]);
		cout << gCount << endl;
	}


	

	

	return 0;
}

