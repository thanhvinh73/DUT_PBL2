#include "../Header_files/Goods.h"
#include <iostream>
#include <fstream>
#include <iomanip>
Goods::Goods()
{
    this->ID = "";
    this->Batch = "";
    this->Goods_name = "";
    this->Type = "";
    this->Origin = "";
    this->Amount = 0;
    this->Cost = 0;
    this->Sale_cost = 0;
}
Goods::Goods(string ID, string batch, string name, string type, string origin, Date exp, int amount, Date imp_date, float cost, float sale_cost)
{
    this->ID = ID;
    this->Batch = batch;
    this->Goods_name = name;
    this->Type = type;
    this->Origin = origin;
    this->EXP = exp;
    this->Amount = amount;
    this->Import_date = imp_date;
    this->Cost = cost;
    this->Sale_cost = sale_cost;
}
void Goods::Input()
{
    cout << distance() << " ------- THONG TIN NHAP HANG ------- " << endl;
    cout << distance() << " Lo: "; getline(cin, this->Batch); Standardized(this->Batch);
    cout << distance() << " Ten: "; getline(cin,this->Goods_name); Standardized(this->Goods_name);
    cout << distance() << " Nguon goc: "; getline(cin,this->Origin); Standardized(this->Origin);
    cout << distance() << " Loai: "; getline(cin, this->Type); Standardized(this->Type); 
    cout << distance() << " Han su dung"; this->EXP.Input();
    cout << distance() << " So luong nhap: "; cin >> this->Amount;
    cout << distance() << " Tong gia nhap: "; cin >> this->Cost; cin.ignore();
    cout << distance() << " Ngay nhap"; this->Import_date.Input();
    cout << distance() << " ----------------------------------- " << endl;

    this->Set_id();
    this->Set_sale_cost();
}
void Goods::Input_from_file(fstream &file_in)
{
    string date; 
    float cost;
    getline(file_in, this->Batch, ',');
    Standardized(this->Batch);
    getline(file_in, this->Goods_name, ',');
    Standardized(this->Goods_name);
    getline(file_in, this->Origin, ',');
    Standardized(this->Origin);
    getline(file_in, this->Type, ',');
    Standardized(this->Type);
    getline(file_in, date, ',');
    this->EXP.str_to_Date(date);
    file_in >> this->Amount; file_in.ignore();
    file_in >> cost;
    this->Set_cost(cost/this->Amount);
    file_in.ignore();
    getline(file_in, date, '\n');
    this->Import_date.str_to_Date(date);

    this->Set_id();
    this->Set_sale_cost();
}
void Goods::Output()
{
    cout << setw(7) << this->Batch << " |"
         << setw(44) << this->Goods_name << " |"
         << setw(12) << this->Origin << " |"
         << setw(18) << this->Type << " |"
         << "    " << this->EXP.to_String() << "  |";
    cout << setw(9) << this->Amount << " |"
         << "  " << this->Import_date.to_String() << " |"
         << setw(13) << setprecision(10) <<this->Cost << " |" << endl;
}
void Goods::Set_id()
{
    string temp = "";
    this->ID = "";
    this->ID += this->Batch;
    temp += (this->Goods_name)[0];
    for (int i = 1; i < (this->Goods_name).length(); i++) 
    {
        if ((this->Goods_name)[i] == ' ')
            temp += (this->Goods_name)[i+1];
    }
    this->ID += temp;
    temp = (this->EXP).to_String();
    temp.erase(2, 1);
    temp.erase(4, 1);
    this->ID += temp;
}
void Goods::Set_batch(string batch)
{
    this->Batch = batch;
}
void Goods::Set_goods_name(string name)
{
    this->Goods_name = name;
}
void Goods::Set_type(string type)
{
    this->Type = type;
}
void Goods::Set_origin(string origin)
{
    this->Origin = origin;
}
void Goods::Set_EXP(string exp)
{
    this->EXP.str_to_Date(exp);
}
void Goods::Set_amount(int amount)
{
    this->Amount = amount;
}
void Goods::Set_import_date(string impDate)
{
    this->Import_date.str_to_Date(impDate);
}
void Goods::Set_cost(float cost)
{
    this->Cost = cost;
}
void Goods::Set_sale_cost()
{
    this->Sale_cost = (this->Cost + this->Cost*15/100);
}
string Goods::Get_id() const
{
    return this->ID;
}
string Goods::Get_batch() const
{
    return this->Batch;
}
string Goods::Get_good_name() const
{
    return this->Goods_name;
}
string Goods::Get_type() const
{
    return this->Type;
}
string Goods::Get_origin() const
{
    return this->Origin;
}
Date& Goods::Get_EXP() 
{
    return this->EXP;
}
int Goods::Get_amount() const
{
    return this->Amount;
}
Date& Goods::Get_import_date() 
{
    return this->Import_date;
}
float Goods::Get_cost() const
{
    return this->Cost;
}
float Goods::Get_sale_cost() const
{
    return this->Sale_cost;
}
Goods& Goods::operator=(const Goods& other)
{
    this->ID = other.ID;
    this->Batch = other.Batch;
    this->Goods_name = other.Goods_name;
    this->Type = other.Type;
    this->Origin = other.Origin;
    this->EXP = other.EXP;
    this->Amount = other.Amount;
    this->Import_date = other.Import_date;
    this->Cost = other.Cost;
    this->Sale_cost = other.Sale_cost;
    return (*this);
}
Goods::~Goods(){
}
