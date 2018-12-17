// Description:
// Date: 14JUN2018
// Group Project - Clothing
// Authors:

#include "Order.h"

using namespace std;

// Constructor
Order::Order() {

	Customer customerInfo;
	Product productInfo;
	orderNum = 0;
	//price = 0.00;
	shipStatus = false;
}
Order::Order(Customer customerInfo, Product productInfo){

	this->customerInfo = customerInfo;
	this->productInfo = productInfo;
	this->orderNum = 0;
	//this->price = 0.00;
	this->shipStatus = false;
}

// Accessors
int Order::getOrderNum() const {

	return orderNum;
}

//double Order::getPrice() const {

	//return price;
//}

Product Order::getProductInfo() const{

	return productInfo;
}

Customer Order::getCustomerInfo() const {

	return customerInfo;
}

bool Order::getShipStatus() const {

	return shipStatus;
}

// Mutators

//void Order::setPrice(double price) {

	//this->price = price;
//}

void Order::setNewOrderNum(vector<Order> &orderHistory, int shipPriority) {

	int nightNum = 0;									// Last overnight orderNum
	int rushNum = 0;									// Last rush order orderNum
	int stdNum = 0;										// Last std order orderNum


	for (unsigned int i = 0; i < orderHistory.size(); i++) {
		if (orderHistory[i].getOrderNum() <= 39999 && orderHistory[i].getOrderNum() >= 30000) {
			if (orderHistory[i].getOrderNum() < nightNum||nightNum==0)
				nightNum = orderHistory[i].getOrderNum();

		}
		else if (orderHistory[i].getOrderNum() <= 29999 && orderHistory[i].getOrderNum() >= 20000) {
			if (orderHistory[i].getOrderNum() < rushNum || rushNum==0)
				rushNum = orderHistory[i].getOrderNum();

		}
		else if(orderHistory[i].getOrderNum() <= 19999 && orderHistory[i].getOrderNum() >= 10000) {
			if (orderHistory[i].getOrderNum() < stdNum || stdNum == 0)
				stdNum = orderHistory[i].getOrderNum();

		}
	}

	if (shipPriority == 1){								// Customer choice: Overnight Delivery
		if(nightNum == 0){
			nightNum = 40000;
		}
		this->orderNum = nightNum - 1;
	}else if (shipPriority == 2){
		if(rushNum == 0){
			rushNum = 30000;
		}// Customer choice: Rush Delivery
		this->orderNum = rushNum - 1;
	}else{
		if(stdNum == 0){
			stdNum = 20000;
		}// Customer choice: Standard Delivery
		this->orderNum = stdNum - 1;
	}


}

void Order::setOrderNum(int orderNum) {

	this->orderNum = orderNum;
}

void Order::setCustomerInfo(Customer customerInfo) {

	this->customerInfo = customerInfo;
}
void Order::setProductInfo(Product productInfo) {

	this->productInfo = productInfo;
}

void Order::setShipStatus(bool status) {

	this->shipStatus = status;
}

// Other Functions

void Order::outputOrder(ostream &out) {

	Customer customerInfo = getCustomerInfo();
	Product productInfo = getProductInfo();

	out <<endl
		<<customerInfo.getUserName()<<endl
		<<customerInfo.getPassword()<<endl
		<<customerInfo.getFirstName()<<endl
		<<customerInfo.getLastName()<<endl
		<<customerInfo.getAddress()<<endl
		<<customerInfo.getCity()<<endl
		<<customerInfo.getState()<<endl
		<<customerInfo.getZip()<<endl;


	out <<productInfo.getName()<<endl
		<<productInfo.getType()<<endl
		<<productInfo.getGender()<<endl
		<<productInfo.getColor()<<endl
		<<productInfo.getSize()<<endl
		<<productInfo.getPrice()<<endl
		<<productInfo.getProductID()<<endl
		<<getOrderNum()<<endl;
	if (getShipStatus())
		out <<"1"<<endl;
	else
		out <<"0"<<endl;
}

bool Order::operator>(const Order &orderInfo) {

	return orderNum > orderInfo.orderNum;

}

bool Order::operator<(const Order &orderInfo) {

	return orderNum < orderInfo.orderNum;
}

bool Order::operator==(const Order &orderInfo) {

	return (orderNum == orderInfo.orderNum);
}

ostream& operator<<(ostream &os, const Order &orderInfo) {

		Customer customerInfo = orderInfo.getCustomerInfo();
		Product productInfo = orderInfo.getProductInfo();

		os <<"Order Number: #"<<orderInfo.getOrderNum()<<endl
		   <<"--------------------------------------"<<endl
		   <<"Username: "<<customerInfo.getUserName()<<endl
		   <<"Product: "<<productInfo.getName()<<endl
		   <<"Product ID: "<<productInfo.getProductID()<<endl
		   <<"Price: $"<<productInfo.getPrice()<<endl
		   <<"Name: " <<customerInfo.getFirstName()<<" "<<customerInfo.getLastName()<<endl
		   <<"Address: "<<customerInfo.getAddress()<<endl
		   <<"City: "<<customerInfo.getCity()<<endl
		   <<"State: "<<customerInfo.getState()<<endl
		   <<"Zip Code: "<<customerInfo.getZip()<<endl;
		os <<"Shipping Priority: ";
		if (orderInfo.getOrderNum() >= 30000)
			os <<"Overnight Shipping"<<endl;
		else if (orderInfo.getOrderNum() >= 20000)
			os <<"Rush Shipping"<<endl;
		else
			os <<"Standard Shipping"<<endl;
		os <<"Shipping Status: ";
		if (orderInfo.getShipStatus() == true)
			os <<"Order Shipped"<<endl;
		else
			os <<"Awaiting Processing"<<endl;
		os<<"-------------------------------------\n\n";

		return os;
}
