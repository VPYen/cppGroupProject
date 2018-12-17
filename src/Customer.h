// Description:
// Date: 14JUN2018
// Group Project - Clothing
// Authors:

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


class Customer {

private:

	// Variables
	string username;
	string password;
	string first_name;
	string last_name;
	string address;
	string city;
	string state;
	string zip;


public:

	// Constructor
	Customer() {
		username = "noUsername";
		password = "noPassword";
		first_name = "noFirstname";
		last_name = "noLastname";
		address = "noAddress";
		city = "noCity";
		state = "noState";
		zip = "noZip";
	}
	Customer(string username,string password,string first_name,string last_name,string address,string city,string state,string zip){
			this->username =username;
			this->password =password;
			this->first_name =first_name;
			this->last_name = last_name;
			this->address = address;
			this->city =city;
			this->state =state;
			this->zip =zip;

		}
	Customer(const Customer &customerInfo) {
		this->username = customerInfo.username;
		this->password = customerInfo.password;
		this->first_name = customerInfo.first_name;
		this->last_name = customerInfo.last_name;
		this->address = customerInfo.address;
		this->city = customerInfo.city;
		this->state = customerInfo.state;
		this->zip = customerInfo.zip;
	}

	// Accessors
	string getUserName() const {
		return username;
	}

	string getPassword() const {
		return password;
	}


	string getFirstName() const {
		return first_name;
	}

	string getLastName() const {
		return last_name;
	}

	string getState() const {
		return state;
	}

	string getCity() const {
		return city;
	}

	string getAddress() const {
		return address;
	}

	string getZip() const {
		return zip;
	}

	// Mutators

	void setUserName(string username) {
		for (auto &c:username)
			c = tolower(c);
		this->username = username;
	}

	void setPassword(string password) {
		this->password = password;
	}

	void setAddress(string address) {
		this->address = address;
	}


	void setCity(string city) {
		this->city = city;
	}


	void setFirstName(string firstName) {
		first_name = firstName;
	}

	void setLastName(string lastName) {
		last_name = lastName;
	}

	void setState(string state) {
		this->state = state;
	}


	void setZip(string zip) {
		this->zip = zip;
	}

	// Other Functions
 	bool operator==(const Customer& customerInfo) {
    return (username == customerInfo.username);
 	}
 	friend ostream& operator<<(ostream &out, Customer customerInfo) {
 		out <<customerInfo.getUserName()<<endl<<customerInfo.getPassword()<<endl
			<<customerInfo.getFirstName()<<" "<<customerInfo.getLastName()<<endl
 			<<customerInfo.getAddress()<<endl
			<<customerInfo.getCity()<<endl
			<<customerInfo.getState()<<endl
			<<customerInfo.getZip()<<endl<<endl;

 		return out;
 	}
 	void displayCustomer(ostream &out){
 		out	<<"Customer Username: "<<getUserName()<<endl
 			<<"Name: "<<getFirstName()<<" "<<getLastName()<<endl
 		 	<<"Address: "<<getAddress()<<endl
 			<<"City: "<<getCity()<<endl
 			<<"State: "<<getState()<<endl
 			<<"Zip code: "<<getZip()<<endl<<endl;
 	}
};

#endif /* CUSTOMER_H_ */
