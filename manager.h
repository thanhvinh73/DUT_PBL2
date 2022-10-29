#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include <iomanip>
using namespace std;

class Shelf
{
    private: 
        string Shelf_name;
        string Area;
        int Remaning_amount;
    public:
        Shelf(string = "", string = "", int = 0);
        void Shelf_in(ifstream& );
        void Shelf_out(int = 0);
        void Set_amount(int = 0);
        // string Get_shelf_name();
        // string Get_area();
        ~Shelf();
};
class Depot
{
    private:
        vector<Shelf> All_shelf;
        int Shelf_amount;
        static int Max_amount;
    public:
        Depot();
        Depot(vector<Shelf>, int);
        void Depot_in(ifstream& in);
        void Depot_out(string = "");
        void Empty_position(string = "");
        ~Depot();
};
class Date
{
    private:
        int Day;
        int Month;
        int Year;
    public:
        Date();
        Date(int, int, int);
        void Date_in();
        void Date_out();
        ~Date();
};
class Import
{
    private: 
        string Batch;
        int Import_amount;
        float Import_cost;
        Date Import_date;
    public:
        Import();
        Import(string, int, float);
        void Import_in();
        void Import_out();
        float Get_cost();
        ~Import();
};
class Export
{
    private:
        int Export_amount;
        float Export_cost;
        Date Export_date;
    public:
        Export(int = 0, float = 0);
        void Export_in(const float ogrCost, float shipCost);
        void Export_out();
        ~Export();
};
class Goods : public Import, public Export
{
    private:
        string Goods_name;
        string Type;
        string Origin;
        Date EXP;
    public:
        Goods(string = "", string = "",string = "");
        void Goods_in();
        void Goods_show();
        string Get_good_name();
        string Get_type();
        string Get_origin();
        //Date Get_EXP();
        ~Goods();
};
class GoodsManagement
{
    private:
        vector<Goods> All_goods;
        int Import_length;
        int Export_length;
    public:
        GoodsManagement();
        GoodsManagement(int, int);
        //void Import_bill();
        void Import_bill(ofstream& out);
        void Import_print();
        void Goods_import();
        void Export_bill(ofstream& out);
        void Export_print();
        void Goods_export();
        int Get_import_length();
        int Get_export_length();
        //bool Check_ID(const string id);
        ~GoodsManagement();
        friend void Information_of_customer();
        friend void Get_real_time();
        friend void Standardized(string&, int);
};

void Information_of_customer();
void Get_real_time();
bool check(string);
void Standardized(string&, int);
