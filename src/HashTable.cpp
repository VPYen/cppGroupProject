// Description:
// Date: 14JUN2018
// Group Project - Clothing
// Authors:

#include "HashTable.h"

/**Access Functions*/

int HashTable::hash(Customer customerInfo) const {
    string key = customerInfo.getUserName();
	int index, sum;
    sum = 0;
    for (unsigned int i = 0; i < key.length(); i++) {
        sum += int(key[i]);
    }
    index = sum % SIZE;
    return index;
}

int HashTable::countBucket(int index) const {
    assert(0 <= index && index < SIZE);
    int sum = 0;
    sum = Table[index].getLength();
    return sum;
}

int HashTable::search(Customer c) const {
    int index = hash(c);
    if (Table[index].isEmpty()) {
        return -1;
    } else {
        if (Table[index].linearSearch(c) != -1) {
            return index;
        } else {
            return -1;
        }
    }
}

/**Manipulation Procedures*/

void HashTable::insert(Customer c) {
    int index = hash(c);
    Table[index].insertStop(c);
}

void HashTable::remove(Customer c) {
    assert(search(c) != -1);
    int index = hash(c);
    Table[index].moveToIndex(Table[index].linearSearch(c));
    Table[index].removeIterator();

}

/**Additional Functions*/

void HashTable::printBucket(ostream& out, int index) const {
    assert(0 <= index && index < SIZE);
    	Table[index].displayList(out);

}

void HashTable::printTable(ostream& out) const {
    for (int i = 0; i < SIZE; i++) {
        if (!Table[i].isEmpty()) {
            out << "Group" << i + 1;
            out << Table[i].getStart()<<endl;
            out << "+" << Table[i].getLength() - 1 << " more Customer(s)"
                    << endl << endl;
        }
    }
}

Customer HashTable::dataSearch(Customer c1) {
	assert(search(c1)!=-1);
	Customer temp;
	int index = hash(c1);


	Table[index].moveToIndex(Table[index].linearSearch(c1));
	temp =Table[index].getIterator();
	Table[index].IteratorToNull();
	return temp;
}

void HashTable::printEntireTable(ostream& out) const{
	for (int i = 0; i < SIZE; i++) {
	        if (!Table[i].isEmpty()) {
	            Table[i].displayList(out);
	        }
	    }
}

bool HashTable::checkPassword(Customer c1){
	assert(search(c1) != -1);
	Customer temp = dataSearch(c1);
	if(c1.getPassword() == temp.getPassword()){
		return true;
	} else {
		return false;
	}
}
void HashTable::printCustomerList(ostream& out){
	for (int i = 0; i < SIZE; i++) {
		  if (!Table[i].isEmpty()) {
		      Table[i].startIterator();
		      while(!Table[i].offEnd()){
		    	  Table[i].getIterator().displayCustomer(out);
		    	  Table[i].moveIterNext();
		      }
		      Table[i].IteratorToNull();
		  }
	}
}
