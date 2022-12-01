#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include "Goods.h"
#include "Bill.h"
#include "Customer.h"
class ListBill;
class ListCustomer;
class GoodsManagement
{
    private:
        vector<Goods> All_goods;
        int Import_length;
        int Export_length;
    public:
        GoodsManagement();
        GoodsManagement(int, int);
        ~GoodsManagement();
        
        int Find_id(string);
        bool Find_name_goods(string);
        bool Find_type_goods(string);
        bool Find_batch_goods(string);
        void Input();
        void Input_from_file(string);
        void Export(ListCustomer&, ListBill&);
        void Export_from_file(string, ListCustomer&, ListBill&);
        void Update(int, int);
        void Delete(string);
        void Sort(int(*func) (GoodsManagement&, bool, int, int), bool ascORdesc, int left, int right);
        void Search(map<int,string>&, string, int);
        void Show_information();
        Goods& operator[](int);

        int Get_import_length() const;
        int Get_export_length() const;
        int Get_length() const;
        void Print_list_ID();    


};
int Sort_by_name(GoodsManagement& g, bool ascORdesc, int left, int right);
int Sort_by_EXP(GoodsManagement& g, bool acsORdesc, int left, int right);
int Sort_by_impDate(GoodsManagement& g, bool ascORdesc, int left, int right);
int Sort_by_type(GoodsManagement& g, bool ascORdesc, int left, int right);
