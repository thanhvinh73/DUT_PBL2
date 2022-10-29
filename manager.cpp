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
//class Date
Date::Date(){

};
Date::Date(int day, int month, int year){
    this->Day = day;
    this->Month = month;
    this->Year = year;
}
void Date::Date_in()
{
    int day, month, year, dayMax = 0;
    bool check = false;
    //cout << "Enter a date:" << endl;
    do{
        cout << "\nDay: " ; cin >> day;
        cout << "Month: "; cin >> month;
        cout << "Year: "; cin >> year;
        if(day < 0 || day > 32 || month < 0 || month > 12 || year < 0)
        {
            cout << "Invalid date....." << endl;
        }
        else
        {
            switch (month)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                dayMax = 31;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                dayMax = 30;
                break;
            case 2:
                if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                    dayMax = 29;
                else 
                    dayMax = 28;
                break;
            }
            if(day <= dayMax)
            {
                this->Day = day;
                this->Month = month;
                this->Year = year;
                check = true;
            }
            else 
                cout << "Invalid date....." << endl;
        }
    } while( check == false);
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
    cout << " ===== ENTER INFORMATION IMPORT ===== " << endl;
    cout << " Batch: "; cin >> this->Batch;
    cout << " Amount: "; cin >> this->Import_amount;
    cout << " Cost: "; cin >> this->Import_cost;
    this->Import_date.Date_in();
    cout << endl;
}
void Import::Import_out()
{
    cout << " ===== ALL INFORMATION IMPORT ===== " << endl;
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
    cout << " Type: "; cin >> this->Type;
    cout << " EXP "; this->EXP.Date_in();
}
void Goods::Goods_show()
{
    //cout << " ===== GOODS INFORMATION ===== " << endl;
    cout << " Name: " << this->Goods_name << endl;
    cout << " Origin: " << this->Origin << endl;
    cout << " Type: " << this->Type << endl;
    cout << " EXP: "; this->EXP.Date_out();
    
}
string Goods::Get_good_name()
{
    return this->Goods_name;
}
string Goods::Get_type()
{
    return this->Type;
}
string Goods::Get_origin()
{
    return this->Origin;
}
// Date Goods::Get_EXP()
// {
//     return this->EXP;
// }
Goods::~Goods(){

}

//class Export
Export::Export(int amount, float cost)
{
    this->Export_amount = amount;
    this->Export_cost = cost;
}
//orgCost ở đây là giá gốc của một kiện hàng
void Export::Export_in(const float ogrCost, float shipCost)
{
    float cost;
    cout << " ===== ENTER EXPORT INFORMATION ===== " << endl;
    this->Export_date.Date_in();
    cout << "\n Enter amount: "; cin >> this->Export_amount; cout << endl;
    float minSellCost = (this->Export_amount) * ogrCost + (this->Export_amount) * ogrCost * 0.05 + shipCost;
    cout << " Minimum selling price: " << minSellCost << endl;
    float listPrice = minSellCost + (minSellCost) * 0.2;
    cout << " List price: " << listPrice << endl;
    cout << " Enter selling price: "; cin >> cost;
    if(cost <= listPrice)
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

//class GoodsManagement
GoodsManagement::GoodsManagement()
{
    this->Import_length = 0;
    this->Export_length = 0;
}
GoodsManagement::GoodsManagement(int importL, int exportL)
{
    //this->g = g;
    this->Import_length = importL;
    this->Export_length = exportL;
}
int GoodsManagement::Get_import_length()
{
    return this->Import_length;
}
int GoodsManagement::Get_export_length()
{
    return this->Export_length;
}
void GoodsManagement::Goods_import()
{
    int n;
    cout << " ===== GOODS IMPORT ===== " << endl;
    cout << "Enter item number: "; cin >> n;
    this->Import_length = n;
    for(int i = 0; i < this->Import_length; i++)
    {
        cout << " " << i + 1 << ". " << endl;
        Goods s;
        cin.ignore();
        s.Goods_in();
        s.Import_in();
        this->All_goods.push_back(s);
    } 
}
void GoodsManagement::Import_print()
{
    int count = 0;
    cout << " ===== LIST IMPORT INFORMATION ===== " << endl;
    for(Goods i : this->All_goods)
    {
        count++;
        i.Goods_show();
        i.Import_out();
        if(count != this->Import_length)
            cout << " ========== END! ==========" << endl;
    }
}
void GoodsManagement::Import_bill(ofstream& out)
{
    double totalBill = 0;
    int count = 0;
    Get_real_time();
    cin.ignore();
    Information_of_customer();
    cout << "\n ========================================== BILL =========================================== "
         << "\n  STT    Ten san pham          Nguon goc              So Luong       Thanh tien "
         << "\n ___________________________________________________________________________________________ ";
    out << "\n ========================================== BILL =========================================== "
        << "\n  STT    Ten san pham          Nguon goc              So Luong       Thanh tien "
        << "\n ___________________________________________________________________________________________ ";
    for(Goods i : this->All_goods)
    {
        count++;
        cout << "\n   " << count << ".     " << i.Get_good_name() << "         " << i.Get_origin() << "          " << this->Import_length << "     "  << setprecision(20) << i.Get_cost() << endl;
        out << "\n   " << count << ".     " << i.Get_good_name() << "         " << i.Get_origin() << "          " << this->Import_length << "     "  << setprecision(20) <<i.Get_cost() << endl;
        totalBill += i.Get_cost();
        if(count != this->Import_length)
        {
            
        }
    }
    cout << "\n =========================================================================================== \n";
    out << "\n =========================================================================================== \n";
    cout << "Total: " << setprecision(20) << totalBill << endl;
    out << "Total: " << setprecision(20) << totalBill << endl;
    
}
//chua viet 
void GoodsManagement::Goods_export()
{
    int n;
    cout << " ===== GOODS EXPORT ===== " << endl;
    cout << " Enter imtem number: "; cin >> n;
    this->Export_length = n;
    for(int i = 0; i < this->Export_length; i++)
    {
        cout << " " << i + 1 << ". " << endl;
        Goods s;
        cout << "Enter name item: ";
        // Nhap vao ten loai hang hoa 
        // Nhap vao so luong
        // Nhap vao gia ban 
    }
}
// chua viet
void GoodsManagement::Export_print()
{

}
// chua biet 
void GoodsManagement::Export_bill(ofstream& out)
{
    //In ra file hoa don xuat hang
    // cout ngay thuc te hoa don duoc tao
    //Tinh trang thanh toan
    // Ten khach hang 
    // Dia chi khách hàng 
    // số điện thoại của khách hàng 
    // Tổng số tiền cần thanh toán
    // Tên người xuất
    // Ten khách hàng 
}

// bool GoodsManagement::Check_ID(const string id)
// {
//     //Kiem tra xem id co hop le hay khong 
// }
GoodsManagement::~GoodsManagement(){

}

//friend function

void Information_of_customer()
{
    string name, address, phoneNumber;
    cout << " ===== ENTER IFORMATION OF CUSTUMER ===== " << endl;
    cout << " Full name: "; getline(cin, name);
    cout << " Address: "; getline(cin, address);
    cout << " Phone number: "; getline(cin, phoneNumber);
}
void Get_real_time()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << "Time: " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << " Date:"
         << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
}
bool check(string s)
{
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == ' ') return false;
    }
    return true;
}
void Standardized(string &s, int maxLength)
{
    int size = s.length();
    while (size <= maxLength)
    {
        s.push_back(' ');
        size++;
    }
}
