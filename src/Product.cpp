/*
 * Product.cpp
 *
 *  Created on: 2018��6��9��
 *      Author: User
 */


#include "Product.h"
#include <iostream>
#include <iomanip>
using namespace std;
Product::Product() {
	Name = " ";
	Type = " ";
	Gender = " ";
	Color = " ";
	Size = " ";
	ProductID = " ";
	price = 0.0;
	operatercontrol = " ";
}

Product::Product(string Name, string Type, string Gender, string Color,
		string Size, string ProductID,double price,string operatercontrol) {
	this->Name = Name;
	this->Type = Type;
	this->Gender = Gender;
	this->Color = Color;
	this->Size = Size;
	this->ProductID = ProductID;
	this->price = price;
	this->operatercontrol = operatercontrol;
}

void Product::setName(string &Name) {
	this->Name = Name;
}
void Product::setType(string &Type) {
	this->Type = Type;
}
void Product::setGender(string &Gender) {
	this->Gender = Gender;
}
void Product::setColor(string &Color) {
	this->Color = Color;
}
void Product::setSize(string &ize) {
	this->Size = Size;
}
void Product::setProductID(string &ProductID) {
	this->ProductID = ProductID;
}
void Product::setOperatercontrol(string &operatercontrol) {
		this->operatercontrol =operatercontrol;
}
string Product::getName() const {
	return Name;
}
string Product::getType() const {
	return Type;
}
string Product::getGender() const {
	return Gender;
}
string Product::getColor() const {
	return Color;
}
string Product::getSize() const {
	return Size;
}
string Product::getProductID() const {
	return ProductID;
}
string Product::getOperatercontrol() const {
	return operatercontrol;
}
double Product::getPrice() const {
		return price;
}
void Product::setPrice(double price) {
		this->price = price;
}

bool Product::operator==(const Product& p1){
	if(p1.getOperatercontrol() == "primary"){
		return (Name == p1.Name);
	} else {
		return (ProductID == p1.ProductID);
	}
}
bool Product::operator<(const Product& p1){
	if(p1.getOperatercontrol() == "primary"){
			return (Name < p1.Name);
		} else {
			return (ProductID < p1.ProductID);
		}
}
bool Product::operator>(const Product& p1){
	if(p1.getOperatercontrol() == "primary"){
			return (Name > p1.Name);
		} else {
			return (ProductID > p1.ProductID);
		}
}
ostream& operator<<(ostream& os, const Product& p){
	os<<"Product name: " + p.Name;
	os<<"\nType: " + p.Type;
	os<<"\nGender: "+ p.Gender;
	os<<"\nColor: "+p.Color;
	os<<"\nSize: "+ p.Size;
	os<<"\nID: "+p.ProductID;
	os<<"\nPrice:$ "<<fixed<<setprecision(2)<<p.price<<endl;
	return os;
}
