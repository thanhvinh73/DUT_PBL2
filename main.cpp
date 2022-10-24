#include <iostream>
#include <fstream>
#include "manager.h"
using namespace std;

int main()
{
    ifstream in;
    in.open("Shelf.txt");
    // Shelf x;
    // x.Shelf_in(in);
    // Depot x;
    // x.Depot_in(in);
    // cout << "Nhap thanh cong." << endl;
    //x.Shelf_out(10);
    // Date x;
    // x.Date_in();
    // x.Date_out();
    // Import a;
    // a.Import_in(); 
    // cout << "Nhap hoan tat...." << endl;
    // a.Import_out();
    // cout << a.Get_cost();
    // Goods a;
    // a.Goods_in();
    // a.Goods_show();
    Export a;
    a.Export_in(12000);
    a.Export_out();
    in.close();
    return 0;
}
