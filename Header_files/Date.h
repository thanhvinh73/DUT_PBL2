#pragma once
#include <string>
using namespace std;
string distance(int = 65);
void Standardized(string&);

class Date
{
    private:
        int Day, Month, Year;
        int hour, minute, second;
    public:
        static bool Check_full_real_time;
        Date(int = 1, int = 1, int = 2022);
        ~Date();

        void Input();
        void Input_from_file(fstream&);
        void str_to_Date(string);
        void str_to_Date_has_hour(string);
        void Output();
        void Output_to_file(ofstream&);

        bool Check_Leap_Year();
        int Month_Day();
        void Check_Valid();
        const Date& operator= (const Date&);
        bool operator< (const Date&);
        bool operator> (const Date&);

        void Set_day(const int&);
        void Set_month(const int&);
        void Set_year(const int&);

        int Get_day() const;
        int Get_month() const;
        int Get_year() const;
        int Get_hour() const;
        int Get_minute() const;
        int Get_second() const;

        string to_String();
        string to_String_has_hour();
        void Set_full_real_time();
        void Set_day_real_time();
};