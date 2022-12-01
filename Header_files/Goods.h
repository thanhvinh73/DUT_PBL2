#pragma once
#include "Date.h"
#include "Vector.h"
class Goods
{
    private:
        string ID;
        string Batch;
        string Goods_name;
        string Type;
        string Origin;
        Date EXP;
        int Amount;
        Date Import_date;
        float Cost;
        float Sale_cost;
        void Set_id();
        void Set_sale_cost();
    public:
        Goods();
        Goods(string, string, string, string, string, Date, int, Date, float, float);
        ~Goods();
        void Input();
        void Input_from_file(fstream &file_in);
        void Output();

        void Set_batch(string);
        void Set_goods_name(string);
        void Set_type(string);
        void Set_origin(string);
        void Set_EXP(string);
        void Set_amount(int);
        void Set_import_date(string);
        void Set_cost(float);

        string Get_id() const;
        string Get_batch() const;
        string Get_good_name() const;
        string Get_type() const;
        string Get_origin() const;
        Date& Get_EXP();
        int Get_amount() const;
        Date& Get_import_date();
        float Get_cost() const;
        float Get_sale_cost() const;

        Goods& operator= (const Goods&);
};

template<class T> bool Asc(T a, T b)
{
    return (a < b);
}
template<class T> bool Desc(T a, T b)
{
    return (a > b);
}
template<class T> bool Compare(bool(*func) (T, T), T a, T b)
{
    return func(a, b);
}
template<class T> void Swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}