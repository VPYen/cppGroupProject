// Description:
// Date: 14JUN2018
// Group Project - Clothing
// Authors:

#include "Heap.h"
#include <iostream>
#include <cmath>
#include <assert.h>
using namespace std;

/**Helper Functions*/

void Heap::heapify(int i) {
	int l = 2 * i;
	int r = 2 * i + 1;
	int maxIndex = i;
	if (l <= heap_size && (*heap)[l] > (*heap)[i]) { //while left child index within the vector size and compare it to it's parents
		maxIndex = l;
	}
	if (r <= heap_size && (*heap)[r] > (*heap)[maxIndex]) {
		maxIndex = r;
	}
	if (maxIndex != i) {
		Order temp = (*heap)[i];
		(*heap)[i] = (*heap)[maxIndex];
		(*heap)[maxIndex] = temp;
		heapify(maxIndex);
	}
}
//helper function to build_heap, remove, and sort
//bubbles an element down to its proper location within the heap

void Heap::heap_increase_key(int i, Order key) {
	if (key > (*heap)[i]) {
		(*heap)[i] = key;
	}
	while (i > 1 && (*heap)[floor(i / 2)] < (*heap)[i]) {
		Order temp = (*heap)[floor(i / 2)];
		(*heap)[floor(i / 2)] = (*heap)[i];
		(*heap)[i] = temp;
		i = floor(i / 2);
	}

}
//helper funciton to insert
//bubbles an element up to its proper location

/**Constructors*/

Heap::Heap(vector<Order> &v) {
	heap = &v;
	heap_size = v.size() - 1;
	build_heap();
}
//assigns heap to point to v, an unordered array
//calls build_heap to convert the unordered array into a valid max heap

/**Manipulation Procedures*/

void Heap::build_heap() {
	int n = heap_size;
	for (int i = floor(n / 2); i >= 1; i--) {
		heapify(i);
	}
}
//Takes an unordered vector and builds it into a heap
//Called as a helper function of the constructor
//Calls heapify as a helper function

void Heap::insert(Order value) {
	heap_size++;
	heap->push_back(value);
	heap_increase_key(heap_size, value);

}
//Inserts a new value onto the end of the heap and
//Bubbles it up to the correct location in the heap
//Calls heap_increase_key as a helper function

void Heap::remove(int index) {
	assert(1 <= index && index <= heap_size);

	Order temp = (*heap)[index];
	(*heap)[index] = (*heap)[heap_size];
	(*heap)[heap_size] = temp;
	heap->erase(heap->begin() + heap_size);
	heap_size--;
	heapify(index);

}
//removes the node at the provided index of the heap
//pre: 1 <= i <= get_size()

vector<Order> Heap::sort() {

	int n = heap_size;
	for (int i = n; i >= 2; i--) {
		Order temp = (*heap)[1];
		(*heap)[1] = (*heap)[i];
		(*heap)[i] = temp;
		heap_size--;
		heapify(1);
	}
	vector<Order> temp2 = *heap;
	heap_size = n;
	build_heap();

	return temp2;
}
//sorts a heap into ascending order
//returns the sorted array of values
//post: heap restored to max heap
//calls build heap as a helper function
//calls heapify as a helper function

/**Access Functions*/
Order Heap::get_max() const {
	assert(heap_size > 0);
	return (*heap)[1];
}
//returns the maximum value in the heap
//pre: heap_size > 0

Order Heap::get_parent(int i) const {
	assert(i > 0 && i <= heap_size);
	return (*heap)[floor(i / 2)];
}
//returns the location (index) of the element stored at index i
//pre: 0 < i <= heap_size

Order Heap::get_left(int i) const {
	assert(i > 0 && i <= heap_size);
	int leftchild = 2 * i;
	assert(leftchild > 0 && leftchild <= heap_size);
	return (*heap)[2 * i];
}
//returns the location (index) of the left child of the element stored at i
//pre: 0 < i <= heap_size

Order Heap::get_right(int i) const {
	assert(i > 0 && i <= heap_size);
	int rightchild = 2 * i + 1;
	assert(rightchild > 0 && rightchild <= heap_size);
	return (*heap)[rightchild];
}
//returns the location (index) of the right child of the element stored at i
//pre: 0 < i <= heap_size

int Heap::get_size() const {
	return heap_size;
}
//returns the heap_size (current number of elements

Order Heap::get_element(int i) const {
	assert(i > 0 && i <= heap_size);
	return (*heap)[i];
}
//returns the element at the specified index i
//pre: 0 < i <= heap_size

/**Additional Operations*/

void Heap::displayHeap(ostream& out) const {
	int level = 1;
	for (int i = 1; i <= heap_size; i++) {
		if (level == floor(log2(i) + 1)) {
			out << (*heap)[i] << " ";
		} else if (level + 1 == floor(log2(i) + 1)) {
			out << endl;
			level++;
			out << (*heap)[i] << " ";

		}

	}
}
//prints the heap in level order
//Hint: level = floor(log2(i) + 1)

void Heap::displayArray(ostream& out) const {
	for (int i = 1; i < heap_size; i++) {

		out << (*heap)[i] << ", ";
	}
	out <<(*heap)[heap_size]<< endl;
}
//prints each element in the array (heap) separated by a comma

