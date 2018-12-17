/*
 * Product.h
 *
 *  Created on: 2018��6��8��
 *      Author: User
 */

#ifndef PRODUCT_H_
#define PRODUCT_H_

#include<iostream>
#include<cstddef>
#include<assert.h>
using namespace std;

class Product{
private:

	string Name;
	string Type;
	string Gender;
	string Color;
	string Size;
	string ProductID;
	double price;
	string operatercontrol;

public:

	Product();
	Product(string Name, string Type, string Gender, string Color, string Size, string ProductID,double price,string operatercontrol);


	void setName (string &Name);
	void setType(string &Type);
	void setGender(string &Gender);
	void setColor(string &Color);
	void setSize(string &Size);
	void setProductID(string &ProductID);
	void setOperatercontrol(string& operatercontrol);
	void setPrice(double price);


	string getName() const;
	string getType()const;
	string getGender()const;
	string getColor()const;
	string getSize()const;
	string getProductID()const;
	string getOperatercontrol() const;
	double getPrice() const;
	bool operator==(const Product& p1);
	bool operator<(const Product& p1);
	bool operator>(const Product& p1);
	//void printInfo(ostream &os) const;
	friend ostream& operator<<(ostream& os, const Product& p);




};




#endif /* PRODUCT_H_ */
