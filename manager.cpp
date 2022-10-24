#include "manager.h"
using namespace std;

//class Shelf
Shelf::Shelf(string name, string pos, int amount)
{
    this->Shelf_name = name;
    this->Area = pos;
    this->Remaning_amount = amount; 
}
void Shelf::Shelf_in(ifstream& in)
{
    getline(in, this->Shelf_name, '-');
    getline(in, this->Area, '-');
    in >> this->Remaning_amount;

}
void Shelf::Shelf_out( int n)
{
    cout << "\n ===== SHELF =====\n";
    for(int i = 1; i < n; i++)
    {
        cout << " " << "Shelf of name: " << this->Shelf_name << endl;
        cout << " " << "Area: " << this->Area << endl;
        cout << " " << "Remaning amount: " << this->Remaning_amount << endl;
    }
}
// string Shelf::Get_area()
// {
//     return this->Area;
// }
// string Shelf::Get_shelf_name()
// {
//     return this->Shelf_name;
// }
void Shelf::Set_amount(int amount)
{
    //Xây dựng hàm trả về số lượng hàng hoá còn lại trên kệ
    //Tuỳ vào loại hàng thì sức chứa của kệ sẽ khác nhau
    // => làm sao để biết sức chứa của từng kệ 
}
Shelf::~Shelf(){

}

//class Depot
Depot::Depot()
{
    this->Shelf_amount = 0;
}
Depot::Depot(vector<Shelf> allShelf, int amount)
{
    this->All_shelf = allShelf;
    this->Shelf_amount = amount;
}
void Depot::Depot_in(ifstream& in)
{
    int i = 0;
    while(!in.eof())
    {   
        i++;
        Shelf s;
        s.Shelf_in(in); 
        in.ignore();
        this->All_shelf.push_back(s);
    }
}
void Depot::Depot_out(string pos)
{
    //
}
void Depot::Empty_position(string pos)
{

}

Depot::~Depot(){

}
//class 
Date::Date(){

};
Date::Date(int day, int month, int year){
    this->Day = day;
    this->Month = month;
    this->Year = year;
}
void Date::Date_in()
{
    //cout << "Enter a date:" << endl;
    cout << "Day: " ; cin >> this->Day;
    cout << "Month: "; cin >> this->Month;
    cout << "Year: "; cin >> this->Year;
    //kiem tra ngay do co ton tai hay khong 
}
void Date::Date_out()
{
    if(this->Day < 10)
        cout << "0" << this->Day << "/";
    else 
        cout << this->Day << "/";
    if(this->Month < 10)
        cout << "0" << this->Month << "/";
    else 
        cout << this->Month << "/";
    cout << this->Year << endl;
}
Date::~Date(){

}
//class Import
Import::Import(){

}
Import::Import(string batch, int amount, float cost)
{
    this->Batch = batch;
    this->Import_amount = amount;
    this->Import_cost = cost;
    //this->Import_date = date;
}
void Import::Import_in()
{
    cout << " ===== ENTER INFORMATION ===== " << endl;
    cout << "Batch: "; cin >> this->Batch;
    cout << "Amount: "; cin >> this->Import_amount;
    cout << "Cost: "; cin >> this->Import_cost;
    this->Import_date.Date_in();
}
void Import::Import_out()
{
    cout << " ===== ALL INFORMATION ===== " << endl;
    cout << " Batch: " << this->Batch << ",";
    cout << " Amount: " << this->Import_amount << ", ";
    cout << " Cost: " << this->Import_cost << ", ";
    cout << " Date:"; this->Import_date.Date_out();
    cout << endl;
}
float Import::Get_cost()
{
    return this->Import_cost;
}
Import::~Import(){

}

//class Goods
Goods::Goods(string name, string type, string origin)
{
    this->Goods_name = name;
    this->Type = type;
    this->Origin = origin;
}
void Goods::Goods_in()
{
    cout << " ===== ENTER GOODS INFORMATION ===== " << endl;
    cout << " Name: "; getline(cin,this->Goods_name);
    cout << " Origin: "; getline(cin,this->Origin);
    //cin.ignore();
    cout << " Type: "; cin >> this->Type;
    cout << " EXP "; this->EXP.Date_in();
}
void Goods::Goods_show()
{
    cout << " ===== GOODS INFORMATION ===== " << endl;
    cout << " Name: " << this->Goods_name << endl;
    cout << " Origin: " << this->Origin << endl;
    cout << " Type: " << this->Type << endl;
    cout << " EXP: "; this->EXP.Date_out();
}
Goods::~Goods(){

}

//class Export
Export::Export(int amount, float cost)
{
    this->Export_amount = amount;
    this->Export_cost = cost;
}
void Export::Export_in(const float ogrCost)
{
    float cost;
    cout << " ===== ENTER EXPORT INFORMATION ===== " << endl;
    this->Export_date.Date_in();
    cout << "\n Enter amount: "; cin >> this->Export_amount; cout << endl;
    float minSellCost = (this->Export_amount) * ogrCost + (this->Export_amount) * ogrCost * 0.05;
    cout << " Minimum selling price: " << minSellCost << endl;
    cout << " Enter selling price: "; cin >> cost;
    if(cost <= minSellCost)
    {
        cout << "\n Are you sure? ";
        cout << "\n 1.Yes.";
        cout << "\n 2.No and change." << endl;
        int select;
        do{
            cin >> select;
            cout << "\n Select again ...." << endl;
        } while (select < 1 || select > 2);
        switch (select)
            {
            case 1:
                this->Export_cost = cost;
                break;
            case 2:
                cout << "\n Enter selling price again: "; 
                cin >> this->Export_cost;
            default:
                break;
            }
    }
    cout << "\n Selling price: " << this->Export_cost << endl;
}
void Export::Export_out()
{
    cout << "===== EXPORT INFORMATION =====" << endl;
    cout << " Amount: " << this->Export_amount << endl;
    cout << " Cost: " << this->Export_cost << endl;
    cout << " Date: "; this->Export_date.Date_out();
}
Export::~Export(){

}

