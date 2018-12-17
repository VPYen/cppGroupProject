// Description:
// Date: 14JUN2018
// Group Project - Clothing
// Authors:

#ifndef ORDER_H_
#define ORDER_H_

#include <vector>
#include "Customer.h"
#include "Product.h"

using namespace std;

class Order {

protected:

	Product productInfo;
	Customer customerInfo;
	//double price;
	int orderNum;										// orderNum designates shipping priority
	bool shipStatus;

public:

	// Constructor
	Order();
	Order(Customer customerInfo, Product productInfo);

	// Accessors
	int getOrderNum() const;
	//double getPrice() const;
	Product getProductInfo() const;
	Customer getCustomerInfo() const;
	bool getShipStatus() const;

	// Mutators
	void setOrderNum(int orderNum);
	void setPrice(double price);
	void setNewOrderNum(vector<Order> &orderHistory, int shipPriority);
	void setCustomerInfo(Customer customerInfo);
	void setProductInfo(Product productInfo);
	void setShipStatus(bool status);

	// Other Functions
	void outputOrder(ostream &out);
	bool operator<(const Order &orderInfo);
	bool operator>(const Order &orderInfo);
	bool operator==(const Order &orderInfo);
	friend ostream& operator<<(ostream &os, const Order &orderInfo);
};


#endif /* ORDER_H_ */
