#pragma once
#include "Manage.h"
using namespace std;
class GoodsManagement;
class Customer;
class ListCustomer;
class Bill
{
    friend class Customer;
private:
    string ID;
    Customer* Customer_of_bill;
    Date Date_of_bill;
    vector<Goods *> g;
    vector<int> Export_amount;
    bool Payment_status;
    void Add_customer(Customer*);
public:
    Bill();
    Bill(string, Customer*, Date, vector<Goods *>, bool);
    ~Bill();

    void Set_ID(Date);
    void Set_date_of_bill(const Date&);
    void Add_goods(Goods *);
    void Add_expAmount(const int&);
    void Set_PayStatus(bool);

    string Get_ID() const;
    Customer* Get_customer();
    Date Get_date_of_bill();
    bool Get_PayStatus() const;
    vector<Goods *>& Get_vector();
    vector<int>& Get_vector_expAmount();
    
    void Input_from_file(fstream&,GoodsManagement&, ListCustomer&);
    void Print(string);
    void Show();
    Goods* operator[](int);
    Bill& operator=(Bill&);
    
};

class ListBill
{
private:
    vector<Bill> bill;
public:
    ~ListBill();
    void Input_from_file(string,GoodsManagement&, ListCustomer&);
    int Find_id(string);
    void Add(const Bill&);
    void Delete(string);
    void Show();
    vector<Bill>& Get_vector();
    Bill& operator[](int);
    Bill& Get_bill(string);
};

