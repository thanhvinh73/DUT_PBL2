#include "../Header_files/Date.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

string distance(int length)
{
    string dis = "";
    for (int i = 0; i < length; i++)
        dis += " ";
    return dis;
}
void Standardized(string &s)
{
    while (!(s.empty()) && s[0] == ' ') s.erase(0, 1);
    while (!(s.empty()) && s[s.length() - 1] == ' ') s.erase(s.length() - 1, 1);
    int i = 1;
    while (!(s.empty()) && i < s.length())
    {
        if (s[i] == ' ' && s[i + 1] == ' ') s.erase(i+1, 1);
        else i++;
    }
    s[0] = toupper(s[0]);
    for (int i = 1; i < s.length(); i++)
    {
        if (s[i] == ' ') 
        {
            s[i+1] = toupper(s[i+1]);
        }
        else if (s[i-1] != ' ') s[i] = tolower(s[i]);
    }
}
bool Date::Check_full_real_time = false;
Date::Date(int day, int month, int year)
{
    this->hour = 0;
    this->minute =0;
    this->second = 0;
    this->Day = day;
    this->Month = month;
    this->Year = year;
    this->Check_Valid();
}
void Date::Input()
{
    string date;
    int count = 0;
    do
    {
        try
        {
            if (count == 0)
            {
               cout << "(dd/mm/yyyy): "; getline(cin, date); 
               count++;
            }   
            else 
            {
                cout << distance() << "(dd/mm/yyyy): "; getline(cin, date); 
            }
            if (date[2] != '/' || date[5] != '/' || date.length() != 10)
            {
                throw string("Dinh dang ngay khong dung...");
            }
            this->Day = stoi(date.substr(0,2));
            this->Month = stoi(date.substr(3,2));
            this->Year = stoi(date.substr(6, date.length() - 6));
            this->Check_Valid();
            break;
        }
        catch(string e)
        {
            cout << distance() << e << endl;
        }
    }while(1);
}
void Date::Input_from_file(fstream &file_in)
{
    string date;
    getline(file_in, date, '\n');
    if (date[2] != '/' || date[5] != '/' || date.length() != 10)
    {
        throw string("Dinh dang ngay khong dung...");
    }
    this->Day = stoi(date.substr(0,2));
    this->Month = stoi(date.substr(3,2));
    this->Year = stoi(date.substr(6, date.length() - 6));
    this->Check_Valid();
}
void Date::str_to_Date(string date)
{
    if (date[2] != '/' || date[5] != '/' || date.length() != 10)
    {
        throw string("Dinh dang ngay khong dung...");
    }
    this->Day = stoi(date.substr(0,2));
    this->Month = stoi(date.substr(3,2));
    this->Year = stoi(date.substr(6, date.length() - 6));
    this->Check_Valid();
}
void Date::str_to_Date_has_hour(string date)
{
    string time;
    int count = 0;
    for (int i = 0; i < date.length(); i++)
    {
        if (date[i] == ':') count++;
        else if (date[i] == '|') 
        {
            time = date.substr(0, i);
            date = date.substr(i+1, 10);
            break;
        }
    }
    if (count != 2 || date[2] != '/' || date[5] != '/' || date.length() != 10)
        throw string("Thoi gian khong hop le...");
    count = 0;
    int temp;
    for (int i = 0; i < time.length(); i++)
    {
        if (time[i] == ':')
        {
            count++;
            if (count == 1) 
            {
                this->hour = stoi(time.substr(0,i));
                temp = i;
            }
            else if (count == 2) 
            {
                this->minute = stoi(time.substr(temp+1, i - temp - 1));
                this->second = stoi(time.substr(i+1, time.length() - i - 1));
                break;
            }
        }
    }
    this->Day = stoi(date.substr(0,2));
    this->Month = stoi(date.substr(3,2));
    this->Year = stoi(date.substr(6, date.length() - 6));
    this->Check_Valid();
    
}
void Date::Output()
{
    if (Check_full_real_time == false)
    {
        if (this->Day < 10) cout << "0" << this->Day; 
        else cout << this->Day;
        cout << "/";
        if (this->Month < 10) cout << "0" << this->Month;
        else cout << this->Month;
        cout << "/";
        cout << this->Year << endl; 
    }
    else
        cout << "Gio: " << this->hour << ":" << this->minute << ":" << this->second << " Ngay:"
        << this->Day << "/" << this->Month << "/" << this->Year << endl;
}
void Date::Output_to_file(ofstream& out)
{
    if (Check_full_real_time == false)
    {
        if (this->Day < 10) out << "0" << this->Day; 
        else out << this->Day;
        out << "/";
        if (this->Month < 10) out << "0" << this->Month;
        else out << this->Month;
        out << "/";
        out << this->Year << endl; 
    }
    else
        out << "Gio: " << this->hour << ":" << this->minute << ":" << this->second << " Ngay:"
        << this->Day << "/" << this->Month << "/" << this->Year << endl;
}
bool Date::Check_Leap_Year()
{
    return ((this->Year % 4 == 0 && this->Year % 100 != 0) || (this->Year % 400 == 0));
}
int Date::Month_Day()
{
    int monthDay;
    if (((this->Month < 8) && (this->Month % 2 != 0)) || ((this->Month >= 8) && (this->Month % 2 == 0)))
        monthDay = 31;
    else if (this->Month == 2)
    {
        monthDay = (this->Check_Leap_Year() == true) ? 29 : 28;
    }
    else
        monthDay = 30;
    return monthDay;
}
void Date::Check_Valid()
{
    if ((this->Day < 1) || (this->Day > this->Month_Day()) || (this->Month < 1) || (this->Month > 12) || (this->Year < 1))
        throw string("Ngay khong hop le...");
}
const Date& Date::operator=(const Date& d)
{
    this->Check_full_real_time = d.Check_full_real_time;
    this->hour = d.hour;
    this->minute = d.minute;
    this->second = d.second;
    this->Day = d.Day;
    this->Month = d.Month;
    this->Year = d.Year;
    return (*this);
}
bool Date::operator< (const Date& d)
{
    if (this->Year > d.Year) return false;
    else if (this->Year < d.Year) return true;
    else if (this->Month > d.Month) return false;
    else if (this->Month < d.Month) return true;
    else if (this->Day > d.Day) return false;
    else if (this->Day < d.Day) return true;
    return true;
}
bool Date::operator>(const Date& d)
{
    if (this->Year > d.Year) return true;
    else if (this->Year < d.Year) return false;
    else if (this->Month > d.Month) return true;
    else if (this->Month < d.Month) return false;
    else if (this->Day > d.Day) return true;
    else if (this->Day < d.Day) return false;
    return true;
}

void Date::Set_day(const int& day)
{
    this->Day = day;
    this->Check_Valid();
}   
void Date::Set_month(const int& month)
{
    this->Month = month;
    this->Check_Valid();
}
void Date::Set_year(const int& year)
{
    this->Year = year;
    this->Check_Valid();
}
int Date::Get_day() const
{
    return this->Day;
}
int Date::Get_month() const
{
    return this->Month;
}
int Date::Get_year() const
{
    return this->Year;
}
int Date::Get_hour() const
{
    return this->hour;
}
int Date::Get_minute() const
{
    return this->minute;
}
int Date::Get_second() const
{
    return this->second;
}
string Date::to_String()
{
    string date_str = "";
    date_str += (this->Day < 10) ? ("0" + to_string(this->Day)) : to_string(this->Day);
    date_str += "/";
    date_str += (this->Month < 10) ? ("0" + to_string(this->Month)) : to_string(this->Month);
    date_str += "/";
    date_str += to_string(this->Year);
    return date_str;
}
string Date::to_String_has_hour()
{
    string date_str = "";
    date_str += to_string(this->hour);
    date_str += ":";
    date_str += to_string(this->minute);
    date_str += ":";
    date_str += to_string(this->second);
    date_str += "|";
    date_str += (this->Day < 10) ? ("0" + to_string(this->Day)) : to_string(this->Day);
    date_str += "/";
    date_str += (this->Month < 10) ? ("0" + to_string(this->Month)) : to_string(this->Month);
    date_str += "/";
    date_str += to_string(this->Year);
    return date_str;
}
void Date::Set_full_real_time()
{
    Check_full_real_time = true;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    this->hour = ltm->tm_hour;
    this->minute = ltm->tm_min;
    this->second = ltm->tm_sec;
    this->Day = ltm->tm_mday;
    this->Month = ltm->tm_mon + 1;
    this->Year = 1900 + ltm->tm_year;
}
void Date::Set_day_real_time()
{
    Check_full_real_time = false;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    this->Day = ltm->tm_mday;
    this->Month = ltm->tm_mon + 1;
    this->Year = 1900 + ltm->tm_year;
}
Date::~Date(){
}
