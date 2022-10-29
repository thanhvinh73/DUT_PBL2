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
    // x.Shelf_out(10);
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
    // a.Import_in();
    // //float cost = a.Get_cost();
    // cout << "     " << a.Get_cost();
    // a.Goods_show();
    // a.Import_out();
    // Export a;
    // a.Export_in(12000,5000);
    // a.Export_out();
    // Information_of_customer();
    // GoodsManagement a;
    // a.Import_in();
    // Get_real_time();

    GoodsManagement g;
    g.Goods_import();
    //cout << "Successful..." << endl;
    g.Import_print();
    ofstream out("billImport.txt", ios::app);
    g.Import_bill(out);
    //g.Import_bill();
    cout << "Successful 5....." << endl;
    //out.close();
    in.close();
    return 0;
}
