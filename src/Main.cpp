
#include <iostream>
#include <fstream>
#include <climits>
#include "BST.h"
#include "Customer.h"
#include "List.h"
#include "Product.h"
#include "Order.h"
#include "HashTable.h"
#include "Heap.h"

using namespace std;

//Menu operation
void fileInputProduct(string inputfileName, BST<Product> &ProductList1, BST<Product> &ProductList2, vector<Product> &ProductList3);
void fileOutputProduct(string outputfileName,BST<Product> ProductList1);
void fileInputOrder(string inputfileName,vector<Order> &OrderList);
void fileInputCustomer(string inputfileName,HashTable &customerTable);
void fileOutputCustomer(string outputfileName,HashTable customerTable);
void fileOutputOrder(string outputfileName,vector<Order> &allOrderList);
void productSearch(BST<Product> ProductList1, BST<Product> ProductList2, Customer &c1,vector<Order> &Orderlist,vector<Order> &allOrderlist);
void productSearchByName(BST<Product> ProductList1, Customer &c1,vector<Order> &Orderlist,vector<Order> &allOrderlist);
void productSearchByID(BST<Product> ProductList2, Customer &c1,vector<Order> &Orderlist,vector<Order> &allOrderlist);
void printList(BST<Product> ProductList1,BST<Product> ProductList2);
//customer Menu
void addOrder(Product p1, Customer c1, vector<Order> &orderList,vector<Order> &allOrderlist);
void displayByGender(vector<Product> ProductList3,string gender);
void displayOrders(ostream&out,vector<Order> Orderlist);

void customerOrderOperation(vector<Order> &Orderlist, vector<Order> &allOrderlist);
void customerOrderlist(vector<Order> &Orderlist,Customer c1,vector<Order> &personalOrderlist);
void customerMenu(Customer c1);
//Login Menu
void createAccount(HashTable &customerTable);
void signIn(HashTable customerTable,Customer &c1,bool &login);
void employeeLogin(bool &logincheck);
void loginMenu(HashTable &customerTable,Customer &c1);
//Employee Menu
void employeeMenu();
void searchCustomer(HashTable customerinfo);

void employeeProductOperation(BST<Product> &ProductList1,BST<Product> &ProductList2);
void shippedOrderSeparation(vector<Order> &allOrderlist,vector<Order> &Orderlist,vector<Order> &ShippedOrderlist);

void fileOutputProduct(string outputfileName,BST<Product> ProductList1){
	ofstream fout(outputfileName);
	ProductList1.inOrderPrint(fout);
	fout.close();
}


int main() {
	HashTable customerTable;
	Customer c1;

	cout <<"\n\n   -=Welcome to=-"<<endl
		 <<"-==The Fashionista==-"<<endl;

	loginMenu(customerTable,c1);

}


//Menu
void loginMenu(HashTable &customerTable,Customer &c1){
	string userreply;
	do{

		cout<<"\n*****Login*****\n\n";
		cout<<"1. Create an account\n";
		cout<<"2. Customer Login\n";
		cout<<"3. Employee Login\n";
		cout<<"4. Quit\n\nEnter your choice: ";
		cin>>userreply;
		if(userreply == "1"){
			fileInputCustomer("Customer.txt",customerTable);
			createAccount(customerTable);
			fileOutputCustomer("Customer.txt",customerTable);

		} else if (userreply == "2"){
			bool unlogin;
			fileInputCustomer("Customer.txt",customerTable);
			signIn(customerTable,c1,unlogin);
			if(!unlogin){
				customerMenu(c1);
			}

		} else if (userreply == "3"){
			bool logincheck = false;
			employeeLogin(logincheck);
			if (logincheck){employeeMenu();}
		} else if (userreply == "4"){
			cout<<"\nSee you next Time!!\n";
		} else{
			cout<<"\nInvalid Input. Please try again!\n";

		}
	}while(userreply != "4");
}
void customerMenu(Customer c1){
		string inputfileName1 = "Product.txt";
		string userreply;
		BST<Product> ProductList1;
		BST<Product> ProductList2;
		vector<Product> ProductList3;
		vector<Order> Orderlist;
		vector<Order> allOrderlist;

		fileInputProduct(inputfileName1, ProductList1, ProductList2, ProductList3);
		fileInputOrder("Order.txt",allOrderlist);
		customerOrderlist(allOrderlist,c1,Orderlist);

		do {
			cout << "\n*****Customer Menu******\n\n";
			cout << "1. Order Product\n";
			cout << "2. View Inventory List\n";
			cout << "3. Display Women's Clothing\n";
			cout << "4. Display Men's Clothing\n";
			cout << "5. View your Orders\n";
			cout << "6. Exit\n\nEnter your choice: ";
			cin >> userreply;
			if (userreply == "1") {  // option 1 Customer interface
				productSearch(ProductList1,ProductList2,c1,Orderlist,allOrderlist);
			} else if ( userreply == "2"){
				printList(ProductList1,ProductList2);
			} else if(userreply == "3"){
				cout << "\n*****Women's Clothing*****\n\n";
				displayByGender(ProductList3,"Female");
			} else if(userreply == "4"){
				cout << "\n*****Men's Clothing*****\n\n";
				displayByGender(ProductList3,"Male");
			} else if(userreply == "5"){
				customerOrderOperation(Orderlist,allOrderlist);
			} else if(userreply == "6"){
				cout << "\nThank you for shopping!\n";
				userreply = "loop";
			} else {
				cout<<"\nInvalid input\n";
				userreply = "invalid";
			}

		} while (userreply != "loop");
}

void employeeMenu(){
	string userreply;
		do{
			HashTable customerinfo;
			BST<Product> ProductList1;
			BST<Product> ProductList2;
			vector<Product> ProductList3;
			vector<Order> Orderlist;
			vector<Order> ShippedOrderlist;
			vector<Order> allOrderlist;

			fileInputCustomer("Customer.txt",customerinfo);
			fileInputProduct("Product.txt", ProductList1, ProductList2, ProductList3);
			fileInputOrder("Order.txt",allOrderlist);
			shippedOrderSeparation(allOrderlist,Orderlist,ShippedOrderlist);
			Order empty;
			Orderlist.insert(Orderlist.begin(),empty);//Heap has no element at the first index
			Heap OrderPriority(Orderlist);

			cout << "\n*****Employee Menu******\n\n";
			cout << "1. Search for Customer by Username\n";
			cout << "2. Display all Customer Info\n";
			cout << "3. Order Display and Operation\n";
			cout << "4. Display Inventory\n";
			cout << "5. Edit Inventory\n";
			cout << "6. Exit\n\n";
			cout << "Enter your choice: ";
			cin>>userreply;
			if(userreply=="1"){
				searchCustomer(customerinfo);
			}else if(userreply=="2"){
				cout<<"\n*****List of Customer Info*****\n\n";
				customerinfo.printCustomerList(cout);
			}else if(userreply=="3"){
				do{
					cout<<"\n*****Order/Shipping Operations*****\n\n";
					if (OrderPriority.get_size() > 0) {
							int n =  OrderPriority.sort().size()-1;
							for(int i = OrderPriority.sort().size()-1;i>0;i--){
								cout<<OrderPriority.sort().size()-n<<": "<<OrderPriority.sort()[i];
								n--;
							}

						cout<<"\n\n-----Ship an order-----\n";
						cout<<"1. Ship order of highest priority\n";
						cout<<"2. Return to previous page\n";
						cout<<"Enter you choice: ";
						cin>>userreply;
						if(userreply=="1"){
							Order temp = OrderPriority.get_max();
								temp.setShipStatus(1);
								cout<<endl<<"Order shipped:"<< temp;//set status to ship

								ShippedOrderlist.push_back(temp);
								OrderPriority.remove(1);
								OrderPriority.build_heap();

						} else if(userreply=="2"){
							cout<<"\nReturning to previous page.\n";
							Orderlist = OrderPriority.sort();
							Orderlist.erase(Orderlist.begin());
							vector<Order> temp;
							temp.reserve(Orderlist.size()+ShippedOrderlist.size());
							temp.insert(temp.end(),Orderlist.begin(),Orderlist.end());
							temp.insert(temp.end(),ShippedOrderlist.begin(),ShippedOrderlist.end());
							allOrderlist = temp;
							fileOutputOrder("Order.txt",allOrderlist);
						}
					}
					else {
						cout <<"All existing orders have already been shipped.\n\n";
						userreply = "2";
					}
				}while(userreply!="2");
			}else if(userreply=="4"){
				printList(ProductList1,ProductList2);
			} else if(userreply=="5"){
				employeeProductOperation(ProductList1,ProductList2);
			} else if(userreply=="6"){
				cout <<"\nReturning to the previous page!\n";
			} else {
				cout<<"\nInvalid Input!\n";
			}
		}while(userreply!="6");
}


//login Menu
void fileInputCustomer(string inputfileName,HashTable &customerTable){
	ifstream fin(inputfileName);
	string u,p,f,l,a,c,s,z,b;

	while(fin.peek() != EOF){

		getline(fin,u);//cout<<"test"<<u<<endl;
		getline(fin,p);//cout<<"test"<<p<<endl;
		fin>>f>>l;//cout<<"test"<<f<<endl;cout<<"test"<<l<<endl;
		fin.clear();
		fin.ignore(INT_MAX,'\n');
		getline(fin,a);//cout<<"test"<<a<<endl;
		getline(fin,c);//cout<<"test"<<c<<endl;
		getline(fin,s);//cout<<"test"<<s<<endl;
		getline(fin,z);//cout<<"test"<<z<<endl;
		Customer c1(u,p,f,l,a,c,s,z);
		customerTable.insert(c1);
		getline(fin,b);

	}
}

void fileOutputCustomer(string outputfileName,HashTable customerTable){
	ofstream fout(outputfileName);
	customerTable.printEntireTable(fout);
}


void employeeLogin(bool &logincheck){
	string superusername = "employee##";
	string superpassword = "employee123";
	string usernameEnter,userpassword;
	bool back = false;
	do{
		cout<<"\n*****Employee Login*****\n\n";
		cout<<"\nPlease enter employee username:";
		cin>>usernameEnter;
		cout<<"Please enter your password:";
		cin>>userpassword;
		if(usernameEnter!=superusername || userpassword!=superpassword){
			do{
			cout<<"\nInvalid input! Would you like to try again? (Y/N)";
			cin>>usernameEnter;
			}while (usernameEnter != "Y" && usernameEnter != "y" && usernameEnter != "yes" && usernameEnter != "Yes" && usernameEnter != "YES" && usernameEnter != "N" && usernameEnter != "NO" && usernameEnter != "n" && usernameEnter != "no" && usernameEnter != "No");
			if(usernameEnter == "Y" || usernameEnter == "y" || usernameEnter== "yes"|| usernameEnter== "Yes" ||usernameEnter == "YES"){
				back = true;
			} else if(usernameEnter == "N" || usernameEnter == "NO" || usernameEnter == "n"|| usernameEnter == "no" || usernameEnter == "No") {
				cout<<"You entered No! Returning to previous page\n";
				back = false;

			} else {
				cout<<"Invalid input! Please enter Yes or No!\n";
				back = true;
			}
		} else{
			cout<<"\nYou have logged in as an employee!\n";
			logincheck = true;
			back = false;
		}

	}while(back);
}

void createAccount(HashTable &customerTable){
	Customer c1;
	string userreply;
	bool accountExistence = false;
	do{
		accountExistence = false;
		cout <<"\n*****Create Account*****\n";
		cout<<"\nPlease enter a username for your account: ";
		cin>>userreply;
		c1.setUserName(userreply);
		if(customerTable.search(c1)!=-1){
			cout<<"\nThe username you have entered already exists! Please try again!\n\n";
			accountExistence = true;
		}
	}while(accountExistence);
	cout<<"\nPlease create a password for your account: ";
	cin>>userreply;
	c1.setPassword(userreply);
	cout<<"\nPlease enter you first name: ";
	cin.clear();
	cin.ignore(INT_MAX,'\n');
	getline(cin,userreply);
	c1.setFirstName(userreply);
	cout<<"\nPlease enter you last name: ";
	getline(cin,userreply);
	c1.setLastName(userreply);
	cout<<"\nPlease enter you address: ";
	getline(cin,userreply);
	c1.setAddress(userreply);
	cout<<"\nPlease enter the city for your address: ";
	getline(cin,userreply);
	c1.setCity(userreply);
	cout<<"\nPlease enter the state for your address: ";
	getline(cin,userreply);
	c1.setState(userreply);
	cout<<"\nPlease enter the zip code for your address: ";
	getline(cin,userreply);
	c1.setZip(userreply);
	cout << "\n\nYour account has been created successfully!\n";
	customerTable.insert(c1);


}
void signIn(HashTable customerTable, Customer &c1,bool &login){
	bool loop = false;
	do{
		string userreply;
		cout <<"\n\n*****Sign In*****\n";
		cout<<"\nPlease enter your username:";
		cin>>userreply;
		c1.setUserName(userreply);
		cout<<"Please enter your password:";
		cin>>userreply;
		c1.setPassword(userreply);
		if(customerTable.search(c1)==-1 || !customerTable.checkPassword(c1)){
			do {
			cout<<"\nThe username or password you have entered is incorrect!\n";
			cout<<"Would you like to try again? (Y/N):";
			cin>>userreply;
			}while(userreply != "Y" && userreply != "y" && userreply != "yes" && userreply != "Yes" && userreply != "YES" && userreply != "N" && userreply != "NO" && userreply != "n" && userreply != "no" && userreply != "No");
			if (userreply == "Y" || userreply == "y" || userreply == "yes"|| userreply == "Yes" || userreply == "YES"){
				loop = true;
			} else if(userreply == "N" || userreply == "NO" || userreply == "n"|| userreply == "no" || userreply == "No") {
				cout<<"You entered No! Returning to previous page\n";
				loop = false;
				login = true;
			} else {
				cout<<"Invalid input! Please enter Yes or No!";
				loop = true;
			}
		} else {
			c1 = customerTable.dataSearch(c1);
			cout<<"\nLogin Successful!\n";
			loop = false;
			login = false;
		}
	}while(loop);

}
//Customer Menu

void productSearch(BST<Product> ProductList1,
		BST<Product> ProductList2, Customer &c1,vector<Order> &Orderlist,vector<Order> &allOrderlist) {
	string userreply;
	do {
		cout << "\n*****Item Order******\n";
		cout << "Search By:\n1. Clothing Name\n";
		cout << "2. Product ID\n";
		cout << "3. Return to previous page.\n\nEnter your choice: ";
		cin >> userreply;
		if (userreply == "1") {     // 1 option in search
			productSearchByName(ProductList1,c1,Orderlist,allOrderlist);
		} else if (userreply == "2") {    // option 2 in userreply == "1"
			productSearchByID(ProductList2,c1,Orderlist,allOrderlist);
		} else {
			if(userreply != "3"){
				cout <<"\nInvalid input!";
			}
		}
	} while (userreply != "3");
}
void addOrder(Product p1, Customer c1,vector<Order> &orderList,vector<Order> &allOrderlist){
	Order order(c1,p1);
	string userreply;
	do{
		cout<<"\nPlease select shipping priority:\n"
		<<"1. Overnight Delivery\n"<<"2. Rush Delivery\n"<<"3. Standard Delivery\n";
		cout <<"Please enter you choice:";
		cin >> userreply;
		if(userreply == "1"){
			order.setNewOrderNum(allOrderlist,1);
			orderList.push_back(order);
			allOrderlist.push_back(order);
			cout<<"\nYou have selected Overnight Delivery.\n";
		}else if(userreply == "2"){
			order.setNewOrderNum(allOrderlist,2);
			orderList.push_back(order);
			allOrderlist.push_back(order);
			cout<<"\nYou have selected Rush Delivery.\n";
		} else if(userreply == "3"){
			order.setNewOrderNum(allOrderlist,3);
			orderList.push_back(order);
			allOrderlist.push_back(order);
			cout<<"\nYou have selected Standard Delivery.\n";
		} else{
			cout<<"\nInvalid input. Please enter 1, 2 or 3!\n";
		}
	}while(userreply != "1" && userreply != "2" && userreply != "3");
}

void productSearchByName(BST<Product> ProductList1, Customer &c1,vector<Order> &Orderlist,vector<Order> &allOrderlist) {
	string userreply="";
	Product temp;
	string name = "";
	string p = "primary";
	cout << "Please enter the name of the product: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, name);
	temp.setName(name);
	temp.setOperatercontrol(p);
	if (!ProductList1.search(temp)) {
		cout << "\nSorry we do not have this item in inventory!\n\nReturning to previous page\n";
	} else {
		do {
			Product selectP = ProductList1.dataSearch(temp);
			cout << "\nItem info: \n\n" << selectP;
			cout << "\nWould you like to order this product?\nEnter you choice(Y/N): ";
			cin >> userreply;
			if (userreply == "Y" || userreply == "y" || userreply == "yes"|| userreply == "Yes" || userreply == "YES") {
				addOrder(selectP,c1,Orderlist,allOrderlist);
				cout<< selectP.getName() + " has been added to your list of orders!\n";


			} else if (userreply == "N" || userreply == "NO" || userreply == "n"
					|| userreply == "no" || userreply == "No") {
				cout << "\nReturning to previous page\n";

			} else {
				cout << "\nInvalid input please enter Y/N:\n";
				userreply = "loop";
			}
		} while (userreply == "loop");
	}
}
void productSearchByID(BST<Product> ProductList2, Customer &c1,vector<Order> &Orderlist,vector<Order> &allOrderlist) {
	string userreply;
	Product temp;
	string ID;
	string p = "secondary";
	cout << "Please enter the ID of the product: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, ID);
	temp.setProductID(ID);
	temp.setOperatercontrol(p);
	if (ProductList2.search(temp) ==  0) {
		cout << "\nSorry the product ID your entered is invalid!\n\nReturning to previous page\n";
	} else {
		do {
			Product order = ProductList2.dataSearch(temp);
			cout << "\nItem info: \n\n" << order;
			cout << "\nWould you like to order this product?\nEnter you choice(Y/N): ";
			cin >> userreply;
			if (userreply == "Y" || userreply == "y" || userreply == "yes"|| userreply == "Yes" || userreply == "YES") {
				addOrder(order,c1,Orderlist,allOrderlist);
				cout<< order.getName() + " has added into your order List!\n";
			} else if (userreply == "N" || userreply == "NO" || userreply == "n"|| userreply == "no" || userreply == "No") {
				cout << "\nReturning to previous page\n";
			} else {
				cout << "\nInvalid input please enter Y/N:\n";
				userreply = "loop";
			}
		} while (userreply == "loop");
	}
}
void printList(BST<Product> ProductList1,BST<Product> ProductList2){
	string userreply;
	do{
		cout<<"\n*****Clothing Inventory*****\n\n";
		cout<<"View By: \n1. Sorted by Clothing Name\n";
		cout<<"2. Sorted by Product ID\n";
		cout<<"3. Back to previous page\n\nEnter your choice: ";
		cin>>userreply;
		if(userreply == "1"){
			cout<<"\n\n******List of Clothes By Name******\n\n";
			ProductList1.inOrderPrint(cout);
		} else if(userreply == "2"){
			cout<<"\n\n******List of Clothes By ID******\n\n";
			ProductList2.inOrderPrint(cout);
		} else {
			if(userreply != "3"){
				cout <<"\nInvalid input!";
			}
		}
	}while(userreply != "3");

}

void displayByGender(vector<Product> ProductList3,string gender){
	for(unsigned int i = 0;i < ProductList3.size();i++){
		if(gender == "Male" && ProductList3[i].getGender()=="Male"){
			cout<<ProductList3[i]<<endl;
		} else if(gender == "Female" && ProductList3[i].getGender()=="Female"){
			cout<<ProductList3[i]<<endl;
		}
	}
}
void displayOrders(ostream& out,vector<Order> Orderlist){
	if(Orderlist.size()==0){
		cout<<"\nCurrently no orders available!\n";
	}
	for(unsigned int i = 0; i<Orderlist.size();i++){
		out<<i+1<<": "<<Orderlist[i]<<endl;
	}
}



void fileInputProduct(string inputfileName, BST<Product> &ProductList1,
		BST<Product> &ProductList2,vector<Product> &ProductList3 ) {

	string p1 = "primary";
	int i = 2;
	do {
		inputfileName = "Products.txt";
		ifstream fin;
		string n, t, g, c, s, pid,skip;
		double price;

		fin.open(inputfileName.c_str());
		if (fin.fail()) {
			cout << "Sorry " + inputfileName + " not found!\n";
		}
		while (!getline(fin, skip,' ').eof()) {
			getline(fin, skip,' ');
			getline(fin, n);
			getline(fin, skip,' ');
			getline(fin, t);
			getline(fin, skip,' ');
			getline(fin, g);
			getline(fin, skip,' ');
			getline(fin, c);
			getline(fin, skip,' ');
			getline(fin, s);
			getline(fin, skip,' ');
			getline(fin, pid);
			getline(fin, skip,' ');
			fin >> price;
			getline(fin, skip);
			fin.clear();
			fin.ignore(INT_MAX, '\n');
			//cout<<n<<endl<<t<<endl<<g<<endl<<c<<endl<<s<<endl<<pid<<endl<<price<<endl;
			Product p(n, t, g, c, s, pid, price, p1);
			if (p1 == "primary") {
				ProductList1.insert(p);
				ProductList3.push_back(p);
			} else {
				ProductList2.insert(p);
			}

		}
		p1 = "secondary";
		i--;
	} while (i == 1);

}
void customerOrderlist(vector<Order> &Orderlist,Customer c1,vector<Order> &personalOrderlist){
	for(unsigned int i = 0;i<Orderlist.size();i++){
		if(Orderlist[i].getCustomerInfo() == c1){
			personalOrderlist.push_back(Orderlist[i]);
		}
	}
}
void fileInputOrder(string inputfileName,vector<Order> &OrderList){
	ifstream fin(inputfileName);
	string blank, user, pass,Last,first,address,city,state,zip,pname,type,gender,color,size,id;
	double price;
	int shipStatus,orderNum;
	while(fin.peek() != EOF){
		getline(fin,blank);
		getline(fin,user);
		getline(fin,pass);
		getline(fin,first);
		getline(fin,Last);
		getline(fin,address);
		getline(fin,city);
		getline(fin,state);
		getline(fin,zip);
		getline(fin,pname);
		getline(fin,type);
		getline(fin,gender);
		getline(fin,color);
		getline(fin,size);
		fin>>price;
		fin.clear();
		fin.ignore(INT_MAX, '\n');
		getline(fin,id);
		fin>>orderNum>>shipStatus;
		getline(fin,blank);
		Customer c1(user,pass,first,Last,address,city,state,zip);
		Product p1(pname,type,gender,color,size,id,price,"");
		Order o1(c1,p1);
		o1.setOrderNum(orderNum);
		o1.setShipStatus(shipStatus);
		OrderList.push_back(o1);

	}
}
//void orderOutPutFileCustom(vector<Order> &allOrderlist){
	/*for(unsigned int i = 0; i< Orderlist.size();i++){
		bool existOrder = false;
		for(unsigned int j = 0; j< allOrderlist.size();j++){
			if(allOrderlist[j]==Orderlist[i]){
				existOrder = true;
			}
		}
		if(!existOrder){
			allOrderlist.push_back(Orderlist[i]);
		}
	}*/




//}
void fileOutputOrder(string outputfileName,vector<Order> &allOrderlist){
	ofstream fout(outputfileName);
	for(unsigned int a = 0; a< allOrderlist.size();a++){
				allOrderlist[a].outputOrder(fout);
		}
		fout.close();
}


void customerOrderOperation(vector<Order> &Orderlist,vector<Order> &allOrderlist){
	string userreply;
	do{
				cout<<"\n*****Your Orders*****\n\n";
				displayOrders(cout,Orderlist);
				if(Orderlist.size() > 0){
					cout<<"\nWould you like to remove an item from order list?\nEnter(Y/N): ";
					cin>>userreply;
					if(userreply == "Y" || userreply == "y" || userreply == "yes"|| userreply == "Yes" || userreply == "YES"){
						cout<<"Please enter the number of item on the list that you would like to remove"<<Orderlist.size()<<"): ";
						int option;
						cin>>option;
						if(cin.fail()){
							cout<<"\nInvalid Input!!!\n";
							userreply = "loop";

						} else {
							if(!Orderlist[option-1].getShipStatus()){
								cout<<endl<<option<<": "<<Orderlist[option-1].getProductInfo().getName()<<"has been removed from the order list\n";

									for(unsigned int j = 0; j <allOrderlist.size();j++){
										if(allOrderlist[j]==Orderlist[option-1]){
											allOrderlist.erase(allOrderlist.begin()+j);
									}

								}
								Orderlist.erase(Orderlist.begin()+(option-1));
								userreply ="loop";
							} else {
								cout<<"Sorry! "<<option<<": "<<Orderlist[option-1].getProductInfo().getName()<<"has been shipped and cannot be removed!\n";
							}

						}
					} else if(userreply == "N" || userreply == "NO" || userreply == "n"|| userreply == "no" || userreply == "No") {
						fileOutputOrder("Order.txt",allOrderlist);
						cout<<"\nYou choose No. Your order has been processed! Returning to previous page.\n";
					} else {
						cout<<"\nInvalid Input!!!Please enter Yes or No!\n";
						userreply = "loop";
					}
				}

			}while(userreply == "loop");
}

void employeeProductOperation(BST<Product> &ProductList1,BST<Product> &ProductList2){
	string reply;
	do{
		Product p1;
		cout<<"\n\n*****Product list operation*****\n\n"
			<<"1. Add Product\n"
			<<"2. Remove product\n"
			<<"3. Return to previous page\n"
			<<"Enter your choice:";
		cin.clear();
		cin.ignore(10000,'\n');
		getline(cin,reply);
		if(reply=="1"){
			cout<<"\n-----Add Product-----\n\n";
			cout<<"Please enter the Name of the product:";
			getline(cin,reply);
			p1.setName(reply);
			cout<<"Please enter the Type of the product:";
			getline(cin,reply);
			p1.setType(reply);
			cout<<"Please enter the Gender of the product:";
			getline(cin,reply);
			p1.setGender(reply);
			cout<<"Please enter the Color of the product:";
			getline(cin,reply);
			p1.setColor(reply);
			cout<<"Please enter the Size of the product:";
			getline(cin,reply);
			p1.setSize(reply);
			cout<<"Please enter the ID of the product:";
			getline(cin,reply);
			p1.setProductID(reply);
			cout<<"Please enter the Price of the product:";
			double price;
			cin>>price;
			p1.setPrice(price);
			reply="primary";
			string operater2 = "second";
			Product p2 = p1;
			p2.setOperatercontrol(operater2);
			p1.setOperatercontrol(reply);
			if(ProductList1.search(p1) || ProductList2.search(p2) ){
				cout<<"\n!!!Failed to add the Product! "<<"<Product Name: "<<p1.getName()<<" or Product ID:"<<p1.getProductID()<< "> already in the product list\n";
			} else {
				ProductList1.insert(p1);
				ProductList2.insert(p2);
				cout<<"\nProduct #"+p1.getProductID() +": "<<p1.getName()<<" was successfully added to the product List!\n";
			}
		}else if(reply=="2"){
			do{
				cout<<"\n-----Remove Product-----\n\n";
				cout<<"1. Remove by product name\n"
					<<"2. Remove by product ID\n"
					<<"3. Return to previous page\n"
					<<"Enter your choice: ";

				getline(cin,reply);
				if (reply == "1") {     // 1 option in search
					cout<<"Please enter the product name:";
					getline(cin,reply);
					p1.setName(reply);
					reply = "primary";
					p1.setOperatercontrol(reply);
					if(!ProductList1.search(p1)){
						cout<<"\nFailed to remove product! "<<p1.getName()<<" is not in inventory!\n";
					} else {
						ProductList1.remove(p1);
						cout<<"\nYou have removed "<<p1.getName()<<" in the product list!\n";
					}

				} else if (reply == "2") {    // option 2 in userreply == "1"
					cout<<"Please enter the product ID:";
					getline(cin,reply);
					p1.setName(reply);
					reply = "second";
					p1.setOperatercontrol(reply);
					if(!ProductList2.search(p1)){
						cout<<"\nFailed to remove product! "<<p1.getProductID()<<" is not in inventory!\n";
					} else {
					ProductList2.remove(p1);
					cout<<"You have removed "<<p1.getProductID()<<" from inventory!\n";
					}
				} else {
					if(reply != "3"){
						cout <<"\nInvalid input!";
					}
				}
				//remind to add output product here
			} while (reply != "3");
		}
		fileOutputProduct("Products.txt",ProductList1);
	}while(reply != "3");
}

void shippedOrderSeparation(vector<Order> &allOrderlist,vector<Order> &Orderlist,vector<Order> &ShippedOrderlist){
	for(unsigned int i = 0; i< allOrderlist.size();i++){
		if(allOrderlist[i].getShipStatus()){
			ShippedOrderlist.push_back(allOrderlist[i]);
		} else {
			Orderlist.push_back(allOrderlist[i]);
		}
	}
}

void searchCustomer(HashTable customerinfo){

	string userreply;
	do{
		Customer temp;
		cout<<"\n*****Search Customer*****\n\n";
		cout<<"Please enter the customer's username:";
		cin>>userreply;
		temp.setUserName(userreply);
		if(customerinfo.search(temp)==-1){
			cout<<"\nSorry the username does not exist!\n";
			userreply="loop";
		} else {
			customerinfo.dataSearch(temp).displayCustomer(cout);
		}
	}while(userreply =="loop");
}

