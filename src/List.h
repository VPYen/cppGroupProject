// Description:
// Date: 14JUN2018
// Group Project - Clothing
// Authors:

#ifndef LIST_H_
#define LIST_H_

#include <cstddef> //for NULL
#include "assert.h"
#include <fstream>
using namespace std;

template<class listdata> // list stores generic listdata, not any specific C++ type
class List {

private:
	struct Node {
		listdata data;
		Node* next;
		Node* previous;

		Node(listdata newData) {
			data = newData;
			next = NULL;
			previous = NULL;
		}
	};

	// Private Variables
	Node* start;
	Node* stop;
	Node* iterator;
	int length;

	// Private Prototypes
	void displayReverse(Node* node, ostream& out) const;
	//Helper function for the public displayReverse wrapper function.
	//Recursively prints the data in a List in reverse.

	bool isSorted(Node* node) const;
	//Helper function for the public isSorted() function.
	//Recursively determines whether a list is sorted in ascending order.

	int binarySearch(int low, int high, listdata data) const;
	//Recursively search the list by dividing the search space in half
	//Returns the index of the element, if it is found in the List
	//Returns -1 if the element is not in the List
	//Post: The iterator location has not been changed

public:

	/**Constructors and Destructors*/

	List();
	//Default constructor; initializes and empty list
	//Postcondition: Dynamically allocates memory for new linked-list.
	//Start/stop/iterator pointers are initialized with NULL values.

	List(const List &list);
	//Copy constructor; creates a deep copy of a given linked-list
	//Postcondition: Dynamically allocates memory for new linked-list.
	//Start/stop/iterator pointers are initialized with NULL values.

	~List();
	//Destructor. Frees memory allocated to the list
	//Postcondition: Deallocates memory created for dynamically allocated Node containing new int.

	/**Accessors*/

	listdata getStart() const;
	//Returns the data at the start of the list
	//Precondition: Takes no parameters. Start node must exist. Node must have data to return.

	listdata getStop() const;
	//Returns the data at the end of the list
	//Precondition: Takes no parameters. Last node must exist. Node must have data to return.

	listdata getIterator() const;
	//Returns the data pointed to by the iterator.
	//Precondition: Iterator must point to a node containing data. Iterator must not be NULL.

	int getLength() const;
	//Returns the size of the list
	//Postcondition: Returns a number equal to current list size.

	int getIndex() const;
	//Indicates the index of the Node where the iterator is currently pointing
	//Nodes are numbered starting at 1 through the size of the list
	//Pre: !offEnd()

	bool isEmpty() const;
	//Determines whether a list is empty.
	//Precondition: Takes no parameters.
	//Postcondition: Returns 1 if list is empty or 0 if list is not empty.

	/**Manipulation Procedures*/

	void removeIterator();
	//Removes data pointed to by the iterator.
	//Preconditon: Iterator must point to a node containing data. Iterator must not be NULL.
	//Postcondition: Node pointed to by iterator is removed. Iterator is set to NULL.
	//void IteratorToNull();

	void removeStart();
	//Removes the value stored in first node in the list
	//Precondition: First node must exist. Start pointer must be on first node.
	//Postcondition: First node is removed from list and previous second node becomes first node.
	//				 If list contains only one node, last node is removed and start/stop pointers are set to NULL to indicate empty list and length is set to 0.
	//				 If list is empty (length == 0), message indicates list is empty.

	void removeStop();
	//Removes the value stored in the last node in the list
	//Precondition: Last node should point to NULL value. Last node must exist.
	//Postcondition: Last node is removed from list and second to last node becomes current last node.
	//				 If list is empty (length == 0), message indicates list is empty.
	//				 If list contains only one node, last node is removed and start/stop pointers are set to NULL to indicate empty list and length is set to 0.

	void insertIterator(listdata data);
	//Inserts a new node after node pointed to by iterator.
	//Precondition: Iterator must point to a node containing data. Iterator must be within the list.
	//Postcondition: If new node is at the end, it becomes the stop node.
	// 				 New node previous pointer must point to node at iterator.

	void insertStart(listdata data);
	//Inserts a new data at the beginning of the list
	//If the list is empty, the new data becomes both start and stop
	//Postcondition: If node is first and last node in list, start and stop pointer points to new node and node will point to null.
	//				 If node existed for first node, the new node will point to the previous first node.
	//				 Start pointer will point to new first node.
	//				 Length of list is incremented.

	void insertStop(listdata data);
	//Inserts a new data at the end of the list
	//If the list is empty, the new data becomes both start and stop
	//Postcondition: Start pointer and stop pointer will point to new node if it is the only node in list.
	//				 New node will point to null and previous last node will point to new node.
	//				 Stop pointer will point to new last node.
	//				 Length of list is incremented.

	/**Additional List Operations*/

	void startIterator();
	//Places iterator at beginning of list.
	//Precondition: List must not be empty.
	//Postcondition: Iterator points to start node.

	void moveIterNext();
	//Moves iterator to next node.
	//Precondition: Iterator cannot be NULL.
	//Postcondition: Iterator points to the node after its previous. If previous node was stop, iterator is now NULL.

	void moveIterPrevious();
	//Moves iterator to previous node.
	//Precondition: Iterator cannot be NULL.
	//Postcondition: Iterator points to node before its previous. If previous node was start, iterator is now NULL.

	void moveToIndex(int index);
	//Moves the iterator to the node whose index number is specified in the parameter
	//Nodes are numbered starting at 1 through the size of the List
	//Pre: size != 0
	//Pre: index <= size

	bool offEnd() const;
	//Checks if iterator is off the list.
	//Postcondition: Returns true or false on check if iterator is NULL.
	//				 If iterator points to a node, function returns false.

	bool operator==(const List& list);
	//Checks if two lists are equal in content.
	//Precondition: Must receive two lists to check. Both lists must contain the same data type.
	//Postcondition: Returns true if both lists are equal in content; otherwise, function returns false.

	bool isSorted() const;
	//Wrapper function that calls the isSorted helper function to determine whether
	//a list is sorted in ascending order.
	//We will consider that a list is trivially sorted if it is empty.
	//Therefore, no precondition is needed for this function

	int linearSearch(listdata data) const;
	//Iteratively searchs the list, element by element, from the start of the List to the end of the List
	//Returns the index of the element, if it is found in the List
	//Does not call the indexing functions in the implementation
	//Returns -1 if the element is not in the List
	//Pre: length != 0
	//Post: The iterator location has not been changed

	int binarySearch(listdata data) const;
	//Returns the index where data is located in the List
	//Calls the private helper function binarySearch to perform the search
	//Pre: length != 0
	//Pre: List is sorted (must test on a sorted list)
	//Post: The iterator location has not been changed

	void displayList(ostream &out) const;
	//Prints to the console the value of each data in the list sequentially
	//and separated by a blank space
	//Prints nothing if the list is empty
	//Prints a empty newline character if it's empty..

	void displayReverse(ostream& out) const;
	//Wrapper function that calls the private displayReverse helper function to print a list in reverse
	//prints nothing if the List is empty

	void displayNumberedList(ostream &out) const;
	//Prints a incremented number for each element in a list starting with 1.
	//Each printed element is ended with a new line.
	//After the last element is printed a blank new line is printed.
	//Prints new line character if list is empty
	void IteratorToNull();

};



template<class listdata>
List<listdata>::List() {
	start = NULL;
	stop = NULL;
	iterator = NULL;
	length = 0;
}

template<class listdata>
List<listdata>::List(const List &list) {

	if (list.start == NULL) //If the original list is empty, make an empty list for this list
	{
		start = stop = iterator = NULL;
	} else {
		start = new Node(list.start->data); //calling Node constructor
		Node* temp = list.start; //set a temporary node pointer to point at the start of the original list
		iterator = start; //set iterator to point to the start node of the new list

		while (temp->next != NULL) {

			temp = temp->next; //advance up to the next node in the original list
			iterator->next = new Node(temp->data); //using node constructor to create new node w/ copy of data
			iterator->previous = iterator;
			iterator = iterator->next; //advance to this new node

		}

		stop = iterator; //Why do I need this line of code? Loops ends with the iterator on the last element.
		iterator = NULL;

	}

	length = list.length;
}

template<class listdata>
List<listdata>::~List()	// Iterates through entire list and deletes every node dynamically allocated while iterating.
{
	Node* b = start;
	Node* a = NULL; //a stands for "after" (i.e. after b)
	while (b != NULL) {
		a = b->next; //move a to node after b
		delete b; //remove b (you know it is not NULL from if)
		b = a; //b "catches up" with a (both point to same place in list)
	}
}

template<class listdata>
void List<listdata>::insertStart(listdata data)	// Creates a new node and places it the front of the list
		{
	Node* N = new Node(data);// Creates new node N that will become first node in list
	if (length == 0)// If list is empty, new node N will become first and last item in list.
			{
		start = stop = N;
		start->previous = stop->previous = NULL;
		start->next = stop->next = NULL;
	} else {
		start->previous = N;
		N->next = start;	// New node N points to previous first node in list.
		start = N;					// New node N is set to first node in list.
		start->previous = NULL;
	}
	length++;						// List size counter is increased.
}

template<class listdata>
void List<listdata>::insertStop(listdata data) // Inserts a new node with data from the end of list by moving previous last node back
		{						// and replacing previous last node's position.
	Node *newNode = new Node(data);
	newNode->next = NULL;// Set newNode's next as NULL to indicate it will be last element in list

	if (length == 0)// If list is empty newNode will become first and last node in list.
			{
		start = stop = newNode;
		start->previous = stop->previous = NULL;
		start->next = stop->next = NULL;
	} else {
		stop->next = newNode; // Previous last node(stop) *next pointer will point to newNode.
		newNode->previous = stop; // newNode's *previous pointer will point to previous last node(stop).
		stop = newNode;		   		// newNode becomes the last node in list

	}
	length++;				   		// List size counter is increased.
}

template<class listdata>
void List<listdata>::insertIterator(listdata data) {

	Node* newNode = new Node(data);

	assert(!offEnd());
	if (iterator == stop) {
		insertStop(data);
	} else {
		newNode->previous = iterator;// Set newNode's previous pointer points to iterator's current node.
		newNode->next = iterator->next;	// Set newNode's next pointer points to iterator's next node in current list.
		iterator->next->previous = newNode;	// Set iterator's next node's previous pointer to point to new Node
		iterator->next = newNode;	// Set iterator's next node to be newNode
	}
	length++;
}

template<class listdata>
void List<listdata>::removeIterator() {
	assert(!offEnd());
	if (iterator == start) {
		removeStart();
	} else if (iterator == stop) {
		removeStop();
	} else {
		iterator->previous->next = iterator->next;// Set iterator previous node's next pointer to be iterator's next node.
		iterator->next->previous = iterator->previous;// Set iterator next node's previous pointer to be iterator's previous node.
		delete iterator;									// Remove iterator.
		length--;
	}
	iterator = NULL;								// Reset iterator to NULL.

}

template<class listdata>
listdata List<listdata>::getIterator() const {
	assert(!offEnd());
	return iterator->data;			// Return data pointed to by the iterator.
}

template<class listdata>
void List<listdata>::startIterator() {
	assert(!isEmpty());
	iterator = start;			// Set iterator's position to the start node.
}

template<class listdata>
void List<listdata>::moveIterNext() {

	iterator = iterator->next;		// Set iterator's position to its next node.
}

template<class listdata>
void List<listdata>::moveIterPrevious() {
	assert(!offEnd());
	iterator = iterator->previous;// Set iterator's position to its previous node.
}

template<class listdata>
void List<listdata>::moveToIndex(int index) {
	assert(!(index > getLength()));
	int count = 1;						// Initialize counter to start index.
	iterator = start;						// Initialize iterator with start.

	while (count != index)// Iterate through list using counter until index is reached.
	{
		iterator = iterator->next;
		count++;
	}
}

template<class listdata>
bool List<listdata>::offEnd() const {
	return iterator == NULL;
}

template<class listdata>
void List<listdata>::removeStart() {
	assert(!isEmpty());
	if (length == 1) {
		delete start;				// Removes first node in list.
		start = stop = NULL; // Sets start and stop value to NULL, indicating empty list.
	} else {
		Node* temp = start;	// Create temporary node to as place holder of start node.
		start = start->next;		// Assign start to be second node.
		start->previous = NULL;
		delete temp;				// Remove temporary node.
	}
	length--;				// Reduce list length by one after removing node.
}

template<class listdata>
void List<listdata>::removeStop() {
	assert(!isEmpty());
	if (length == 1) {

		delete stop;				// Remove last node.
		start = stop = NULL;// Set start and stop to NULL, signifying empty list.
	} else {
		Node* temp = stop;

		stop = stop->previous;// Set stop to be the former second to last node stored in temp
		delete temp;				// Remove last node.
		stop->next = NULL; // Set pointer to point at NULL rather than deallocated memory
	}
	length--;			// Reduce list length by one after removing last node.
}

template<class listdata>
bool List<listdata>::isEmpty() const// Returns 0 if list is not empty. Returns 1 if list is empty.
{
	return length == 0;
}

template<class listdata>
int List<listdata>::getLength() const		// Returns current length of list.
{
	return length;
}

template<class listdata>
listdata List<listdata>::getStart() const// Returns value of start node if value exists, otherwise returns 0.
{
	assert(!isEmpty());
	return start->data;
}

template<class listdata>
listdata List<listdata>::getStop() const// Returns value of stop node if value exists, otherwise returns 0.
{
	assert(!isEmpty());
	return stop->data;
}

template<class listdata>
int List<listdata>::getIndex() const {
	assert(!offEnd());
	Node* temp = start;					// Initialize temp iterator to start.
	int index = 1;					// Initialize index counter to start index.

	while (temp != iterator)// Temporary pointer iterates through list until iterator is reached.
	{
		temp = temp->next;
		index++;
	}
	return index;
}

template<class listdata>
bool List<listdata>::operator==(const List& list) {
	if (length != list.length)
		return false;
	Node* temp1 = start;
	Node* temp2 = list.start;
	while (temp1 != NULL) {
		if (temp1->data != temp2->data)
			return false;
		temp1 = temp1->next;
		temp2 = temp2->next;
	}
	return true;
}

template<class listdata>
bool List<listdata>::isSorted(Node* node) const {
	if (node->next == NULL)
		return true;
	else {
		if (node->data <= node->next->data)
			return isSorted(node->next);
		else
			return false;
	}

}
template<class listdata>
bool List<listdata>::isSorted() const {
	Node* node = start;

	if (isEmpty()) {
		return false;
	} else if (isSorted(node)) {
		return true;
	}

	return false;

}

template<class listdata>
int List<listdata>::linearSearch(listdata data) const {
	assert(!isEmpty());
	Node* temp = start;				// Initialize temp pointer to start node.
	int index = 1;					// Initialize index iterator to start index.

	do {
		if (temp->data == data)	// If value exists in list, return index value.
				{
			return index;
		}
		temp = temp->next;
		index++;
	} while (index != getLength() + 1);

	return -1;
}

template<class listdata>
int List<listdata>::binarySearch(listdata data) const {
	assert(isSorted());

	return binarySearch(1, getLength(), data);
}

template<class listdata>
int List<listdata>::binarySearch(int low, int high, listdata data) const {
	Node* temp = start;
	int index = 1;

	if (high < low)
		return -1;

	int mid = low + (high - low) / 2;// Midpoint formula, add min value to account for end values of list.

	while (index != mid)	// Iterate temp pointer to midpoint in linked-list.
	{
		temp = temp->next;
		index++;
	}
	if (temp->data == data)	// If data at mid pointer is equal to sought data.
			{
		return index;
	} else if (data > temp->data)// If data at mid pointer is greater than sought data.
			{
		return binarySearch(mid + 1, high, data);
	} else					// If data at mid pointer is less than sought data.
	{
		return binarySearch(low, mid - 1, data);
	}
}

template<class listdata>
void List<listdata>::displayList(ostream &out) const// Iterates through entire linked-list and prints data corresponding to each node.
		{
	Node* temp = start;						// Create a temporary iterator
	while (temp != NULL) {
		out << temp->data;// Prints current data where temp is currently pointing.
		temp = temp->next;					// Moves temp pointer to next node.
	}
}

template<class listdata>
void List<listdata>::displayReverse(ostream &out) const	// Iterates through entire linked-list and prints data corresponding to each node. // @suppress("Ambiguous problem")
		{
	Node* temp = stop;// Create a temporary iterator to pass to private function displayReverse()

	if (isEmpty())				// Prints nothing if list is empty and returns.
	{
		return;
	} else// Call private function displayReverse() to display list in reverse (recursively)
	{
		displayReverse(temp, out);
	}
}

template<class listdata>
void List<listdata>::displayReverse(Node* node, ostream &out) const {
	if (node == NULL) {
		out << endl;
		return;
	} else {
		out << node->data << " ";
		displayReverse(node->previous, out);
	}

}

template<class listdata>
void List<listdata>::displayNumberedList(ostream &out) const {
	Node* temp = start;
	int num = 1;
	while (temp != NULL) {
		out << num << ": " << temp->data << endl;
		temp = temp->next;
		num++;
	}
	out << endl;
}

template<class listdata>
void List<listdata>::IteratorToNull(){
	iterator=NULL;
}
#endif /* LIST_H_ */
