/*
 * BST.h
 *
 *  Created on: 2018年6月9日
 *      Author: User
 */

#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <string>
#include <assert.h>
#include <cstdlib>
#include <iostream>

using namespace std;


template<class bstdata>
class BST {
private:
	struct Node {
		bstdata data;
		Node* left;
		Node* right;

		Node(bstdata newdata) {
			data = newdata;
			left = NULL;
			right = NULL;
		}
	};

	Node* root;

	/**Private helper functions*/
	void insertHelper(Node* root, bstdata data);
	//private helper function for insert
	//recursively inserts a value into the BST

	void inOrderPrintHelper(ostream& out, Node* root) const;
	//private helper function for inOrderPrint
	//recursively prints tree values in order from smallest to largest

	void preOrderPrintHelper(ostream& out, Node* root) const;
	//private helper function for preOrderPrint
	//recursively prints tree values in pre order

	void postOrderPrintHelper(ostream& out, Node* root) const;
	//private helper function for postOrderPrint
	//recursively prints tree values in post order

	void copyHelper(Node* copy);
	//recursive helper function to the copy constructor

	void destructorHelper(Node* root);
	//private helper function for the destructor
	//recursively frees the memory in the BST

	bool searchHelper(Node* root, bstdata data) const;
	//recursive helper function to search
	//returns whether the value is found in the tree
	bstdata dataSearchHelper(Node* root, bstdata data) const;
		//recursive helper function to search
		//returns whether the value is found in the tree

	bstdata minimumHelper(Node* root) const;
	//recursive helper function to minimum
	//returns the minimum value in the tree

	bstdata maximumHelper(Node* root) const;
	//recursive helper function to maximum
	//returns the maximum value in the tree

	Node* removeHelper(Node* root, bstdata data);
	//recursive helper function to remove
	//removes data from the tree

	void getSizeHelper(Node* root, int& size) const;
	//recursive helper function to the size function
	//calculates the size of the tree
	//stores the result in size

	int getHeightHelper(Node* root) const;
	//recursive helper function to the height function
	//returns the height of the tree

public:

	/**constructors and destructor*/

	BST();
	//Instantiates a new BST

	BST(const BST &bst);
	//copy constructor

	~BST();
	//deallocates the tree memory

	/**access functions*/

	bstdata minimum() const;
	//returns the minimum value in the BST
	//pre: !empty()

	bstdata maximum() const;
	//returns the maximum value in the BST
	//pre: !empty()

	bool isEmpty() const;
	//determines whether the BST is empty

	int getSize() const;
	//returns the size of the tree

	bstdata getRoot() const;
	//returns the value stored at the root of the BST
	//pre: !isEmpty()

	int getHeight() const;
	//returns the height of the tree

	bool search(bstdata data) const;
	//returns whether the data is found in the tree
	//pre: !isEmpty()
	bstdata dataSearch(bstdata data) const;
		//returns whether the data is found in the tree
		//pre: !isEmpty()

	/**manipulation procedures*/

	void insert(bstdata data);
	//inserts new data into the BST

	void remove(bstdata data);
	//removes the specified value from the tree
	//pre: data is located in the tree
	//pre: !isEmpty()

	/**additional functions*/

	void inOrderPrint(ostream& out) const;
	//calls the inOrderPrint function to print out the values
	//stored in the BST

	void preOrderPrint(ostream& out) const;
	//calls the reOrderPrint function to print out the values
	//stored in the BST

	void postOrderPrint(ostream& out) const;
	//calls the postOrderPrint function to print out the values
	//stored in the BST
};

/**constructors and destructor*/

template<class bstdata>
BST<bstdata>::BST() {
	root = NULL;
}

template<class bstdata>
BST<bstdata>::BST(const BST &bst) { //copy constructor
	root = NULL;
	copyHelper(bst.root);
}

template<class bstdata>
void BST<bstdata>::copyHelper(Node* copy) {
	if (copy == NULL) {
		return;
	} else {
		insert(copy->data);
		copyHelper(copy->left);
		copyHelper(copy->right);
	}

}

template<class bstdata>
BST<bstdata>::~BST() {	//deallocates the tree memory
	destructorHelper(root);
}

template<class bstdata>
void BST<bstdata>::destructorHelper(Node* root) {
	if (root == NULL) {
		return;
	}
	destructorHelper(root->left);
	destructorHelper(root->right);
	delete root;
}

/**access functions*/

template<class bstdata>
bool BST<bstdata>::isEmpty() const {
	return root == NULL;

}

template<class bstdata>
bstdata BST<bstdata>::minimum() const {
	assert(!isEmpty());
	return minimumHelper(root);
}
template<class bstdata>
bstdata BST<bstdata>::minimumHelper(Node* root) const {
	if (root->left == NULL) {
		return root->data;
	} else {
		return minimumHelper(root->left);
	}

}

template<class bstdata>
bstdata BST<bstdata>::maximum() const {
	assert(!isEmpty());
	return maximumHelper(root);
}
template<class bstdata>
bstdata BST<bstdata>::maximumHelper(Node* root) const {
	if (root->right == NULL) {
		return root->data;
	} else {
		return maximumHelper(root->right);
	}

}
template<class bstdata>
bstdata BST<bstdata>::dataSearch(bstdata data) const{
	if (data == root->data){
		    return root->data;
		}else{
			return dataSearchHelper(root, data);
		}
}
template<class bstdata>
bstdata BST<bstdata>::dataSearchHelper(Node* root, bstdata data) const{
	assert(search(data));
	if (root->data == data) {
		return root->data;
	} else if (root->data > data) {
		return dataSearchHelper(root->left, data);
	} else {
		return dataSearchHelper(root->right, data);
	}


}

template<class bstdata>
bool BST<bstdata>::search(bstdata data) const {
	if (data == root->data){
	    return true;
	}else{
		return searchHelper(root, data);
	}
}
template<class bstdata>
bool BST<bstdata>::searchHelper(Node* root, bstdata data) const {
	if (root->data == data) {
		return 1;
	} else if (root->data > data) {
		if (root->left == NULL) {
			return 0;
		} else {
		return searchHelper(root->left, data);
		}
	} else {
		if (root->right == NULL) {
			return 0;
		} else {
		return searchHelper(root->right, data);
		}
	}
	return 0;
}

template<class bstdata>
int BST<bstdata>::getSize() const {
	int size = 0;
	getSizeHelper(root, size);
	return size;
}
template<class bstdata>
void BST<bstdata>::getSizeHelper(Node* root, int& size) const {
	if (root == NULL) {
		return;
	} else {
		getSizeHelper(root->left, size);
		getSizeHelper(root->right, size);
		size++;
	}
}
//returns the size of the tree

template<class bstdata>
bstdata BST<bstdata>::getRoot() const {
	assert(!isEmpty());
	return root->data;

}
template<class bstdata>
int BST<bstdata>::getHeight() const {
	assert(!isEmpty());
	return getHeightHelper(root);

}
template<class bstdata>
int BST<bstdata>::getHeightHelper(Node* root) const {
	if (root == NULL) {
		return -1;
	}
	int left = getHeightHelper(root->left) + 1;
	int right = getHeightHelper(root->right) + 1;
	if (left > right) {
		return left;
	} else if (left < right) {
		return right;
	} else {
		return left;
	}

}

/**manipulation procedures*/
template<class bstdata>

void  BST<bstdata>::insert(bstdata data){
	if (root == NULL){
		root = new Node(data);
	} else {
	 insertHelper(root,data);
	}
}
template<class bstdata>
void BST<bstdata>::insertHelper(Node* root, bstdata data) {

if (data == root->data) {
		return;
	} else if (data < root->data) {
		if (root->left == NULL) {
			root->left = new Node(data);
		} else {
			insertHelper(root->left, data);
		}
	} else {
		if (root->right == NULL) {
			root->right = new Node(data);
		} else {
			insertHelper(root->right, data);
		}
	}

}

template<class bstdata>
void BST<bstdata>::remove(bstdata data) {
	assert(!isEmpty());
	assert(search(data));
	root = removeHelper(root, data);
}

template<class bstdata>
typename BST<bstdata>::Node* BST<bstdata>::removeHelper(Node* root,bstdata data) {
	if (root == NULL) {
		return root;
	} else if (root->data < data) {
		root->right = removeHelper(root->right, data);
	} else if (root->data > data) {
		root->left = removeHelper(root->left, data);
	} else if (root->data == data) {
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		} else if (root->left == NULL) {
			Node* temp = root;
			root = root->right;
			delete temp;
		} else if (root->right == NULL) {
			Node* temp = root;
			root = root->left;
			delete temp;
		} else if (root->right != NULL && root->left != NULL) {
			Node* min = root->right;
			while (min->left != NULL) {
				min = min->left;
			}
			root->data = min->data;
			root->right = removeHelper(root->right, min->data);
		}
	}
	return root;

}

/**additional functions*/

template<class bstdata>
void BST<bstdata>::inOrderPrint(ostream& out) const {
	inOrderPrintHelper(out, root);
	out<<endl;
	}

template<class bstdata>
void BST<bstdata>::inOrderPrintHelper(ostream& out, Node* root) const {
	if (root == NULL) {
		return;
	}
	inOrderPrintHelper(out, root->left);
	out << root->data<< endl;
	inOrderPrintHelper(out, root->right);
}

template<class bstdata>
void BST<bstdata>::preOrderPrint(ostream& out) const {
	preOrderPrintHelper(out, root);
	out<<endl;
}

template<class bstdata>
void BST<bstdata>::preOrderPrintHelper(ostream& out, Node* root) const {
	if (root == NULL) {
		return;
	}
	out << root->data << " ";
	preOrderPrintHelper(out, root->left);
	preOrderPrintHelper(out, root->right);
}

template<class bstdata>
void BST<bstdata>::postOrderPrint(ostream& out) const {
	postOrderPrintHelper(out, root);
	out<<endl;
}
template<class bstdata>
void BST<bstdata>::postOrderPrintHelper(ostream& out, Node* root) const {
	if (root == NULL) {
		return;
	}
	postOrderPrintHelper(out, root->left);
	postOrderPrintHelper(out, root->right);
	out << root->data << " ";
}

#endif /* BST_H_ */
