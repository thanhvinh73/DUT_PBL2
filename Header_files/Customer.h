#pragma once
#include <string>
#include "Goods.h"
#include "Bill.h"
using namespace std;
class Bill;
class ListBill;
class Customer
{
private:
	string ID;
	string Name;
	string Address;
	string PhoneNumber;
    vector<Bill> Lb;
public:
	Customer(string = "", string = "", string = "", string = "");
	~Customer();

	void Set_Name(string);
	void Set_Address(string);
	void Set_PhoneNumber(string);
	void Add_bill(Bill&);

	string Get_ID() const;
	string Get_name() const;
	string Get_address() const;
	string Get_PhoneNumber() const;
	vector<Bill>& Get_vector();

	void Update_bill(Bill);
	void Input_from_file(fstream&);
	Customer& operator=(Customer&);
	friend istream& operator>>(istream&, Customer&);
	friend ostream& operator<<(ostream&, const Customer&);
};

class ListCustomer
{
private:
	vector<Customer> List;
public:
	ListCustomer();
	~ListCustomer();
	int Get_length() const;
	bool Check_valid_ID(string);
	Customer& operator[](int);
	int Find_id(string);
	void Input_from_file(string);
	void Add(const Customer&);
	void Update(int, int);
	void Delete(string);
	void Show_information(string = "");
};