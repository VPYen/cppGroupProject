// Description:
// Date: 14JUN2018
// Group Project - Clothing
// Authors:

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#include "List.h"
#include "Customer.h"

using namespace std;

class HashTable {
public:
    /**Constructors*/

    HashTable() {};
    //constructor

    ~HashTable() {};
    //destructor

    /**Access Functions*/

    int hash(Customer customerInfo) const;

    int countBucket(int index) const;

    int search(Customer c) const;

    /**Manipulation Procedures*/

    void insert(Customer c);

    void remove(Customer c);

    /**Additional Functions*/

    void printBucket(ostream& out, int index) const;

    void printTable(ostream& out) const;
    void printEntireTable(ostream& out) const;

    Customer dataSearch(Customer c1);

    bool checkPassword(Customer c1);
    void printCustomerList(ostream& out);

private:
    static const int SIZE = 200;
    List<Customer> Table[SIZE];
};


#endif /* HASHTABLE_H_ */
