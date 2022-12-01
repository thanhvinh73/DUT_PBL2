#include "../Header_files/Bill.h"
//========================================= Class Bill ============================================

Bill::Bill() : ID(""), Customer_of_bill(nullptr), Payment_status(false)
{}
Bill::Bill(string id, Customer* cus, Date date, vector<Goods *> g, bool status) : ID(id), Customer_of_bill(cus), Date_of_bill(date), g(g), Payment_status(status)
{}
Bill::~Bill()
{
}
void Bill::Set_ID(Date Real_time)
{
    string str = "";
    str += to_string(Real_time.Get_hour());
    str += to_string(Real_time.Get_minute());
    str += to_string(Real_time.Get_second());
    str += to_string(Real_time.Get_day());
    str += to_string(Real_time.Get_month());
    str += to_string(Real_time.Get_year());
    this->ID = str;
}
void Bill::Add_customer(Customer* cus)
{
    this->Customer_of_bill = cus;
}
void Bill::Set_date_of_bill(const Date& _date)
{
    this->Date_of_bill = const_cast<Date&>(_date);
}
void Bill::Add_goods(Goods * g)
{
    this->g.push_back(g);
}
void Bill::Add_expAmount(const int& expAmount)
{
    this->Export_amount.push_back(expAmount);
}
void Bill::Set_PayStatus(bool status)
{
    this->Payment_status = status;
}
string Bill::Get_ID() const
{
    return this->ID;
}
Customer* Bill::Get_customer()
{
    return this->Customer_of_bill;
}
Date Bill::Get_date_of_bill()
{
    return this->Date_of_bill;
}
bool Bill::Get_PayStatus() const
{
    return this->Payment_status;
}
void Bill::Input_from_file(fstream& in,GoodsManagement &g, ListCustomer &lc)
{
    getline(in, this->ID, ',');

    //input payment status
    string payment;
    getline(in, payment, ',');
    this->Payment_status = (payment.compare("1") == 0) ? true : false;

    //input date of bill
    string date;
    getline(in, date, ',');
    this->Date_of_bill.str_to_Date_has_hour(date);
    this->Date_of_bill.Check_full_real_time = true;

    //input vector goods*
    int length, index;
    in >> length; in.ignore();
    for (int i = 0; i < length; i++)
    {
        string goods_id;
        getline(in, goods_id, '-');
        index = g.Find_id(goods_id);
        if (index == -1) throw string("Khong tim thay mat hang trong hoa don...");
        this->g.push_back(&g[index]);

        int expAmount;
        in >> expAmount; in.ignore();
        this->Export_amount.push_back(expAmount);
    }

    //input customer* pointer
    string cus_id;
    getline(in, cus_id, '\n');
    index = lc.Find_id(cus_id);
    if (index == -1) throw string("Khach hang cua hoa don khong tim thay...");
    lc[index].Add_bill(*this);
}

void Bill::Print(string fileName)
{
    ofstream out;
    out.open(fileName, ios::trunc);
    double totalBill = 0;
    this->Date_of_bill.Output_to_file(out);
    out         << "Khach hang: " << this->Customer_of_bill->Get_name() << "         SDT: " << this->Customer_of_bill->Get_PhoneNumber()
        << endl << "                                       HOA DON                                         "
        << endl << " ------------------------------------------------------------------------------------- "
        << endl << "| STT |                 Ten san pham                | So Luong |      Thanh tien      |"
        << endl << " _____________________________________________________________________________________ ";
    int count = 0;
    for (int i = 0; i < this->g.size(); i++)
    {
        count++;
        out << endl << "|" << setw(4) << count << " |" << setw(44) << (*this)[i]->Get_good_name() 
            << " |" << setw(9) << this->Export_amount[i] << " |"  
            << setw(18) << setprecision(18) << (*this)[i]->Get_sale_cost() * this->Export_amount[i] << "    |" << endl;
        out << " _____________________________________________________________________________________ ";
        totalBill += (*this)[i]->Get_sale_cost() * this->Export_amount[i];
    }
    out << endl << " ------------------------------------------------------------------------------------- " << endl;
    out << "Tong: " << setprecision(20) << totalBill << endl;
}
void Bill::Show()
{
    double totalBill = 0;
    cout << distance(); this->Date_of_bill.Output();
    cout        << distance() << "Khach hang: " << this->Customer_of_bill->Get_name() << "         SDT: " << this->Customer_of_bill->Get_PhoneNumber()
        << endl << distance() << "                                       HOA DON                                         "
        << endl << distance() << " ------------------------------------------------------------------------------------- "
        << endl << distance() << "| STT |                 Ten san pham                | So Luong |      Thanh tien      |"
        << endl << distance() << " _____________________________________________________________________________________ ";
    for (int i = 0; i < this->g.size(); i++)
    {
        cout << endl << distance() << "|" << setw(4) << i+1 << " |" << setw(44) << (*this)[i]->Get_good_name() 
             << " |" << setw(9) << this->Export_amount[i] << " |"  
             << setw(18) << setprecision(18) << (*this)[i]->Get_sale_cost() * this->Export_amount[i] << "    |" << endl;
        cout << distance() << " _____________________________________________________________________________________ ";    
        totalBill += (*this)[i]->Get_sale_cost() * this->Export_amount[i];
    }
    cout << endl << distance() << " ------------------------------------------------------------------------------------- " << endl;
    cout << distance() << "Tong: " << setprecision(20) << totalBill << endl;
}
Goods* Bill::operator[](int index)
{
    if (index > this->g.size() || index < 0)
    {
        static Goods * g = new Goods;
        return g;
    }
    else return this->g.at(index);

}
Bill& Bill::operator=(Bill& _other)
{
    if (this != &_other)
    {
        this->ID = _other.ID;
        if (this->Customer_of_bill != nullptr) delete this->Customer_of_bill;
        this->Customer_of_bill = _other.Customer_of_bill;
        this->Date_of_bill = _other.Date_of_bill;
        this->g = _other.g;
        this->Export_amount = _other.Export_amount;
        this->Payment_status = _other.Payment_status;
    }
    return (*this);
}
vector<Goods*>& Bill::Get_vector()
{
    return this->g;
}
vector<int>& Bill::Get_vector_expAmount()
{
    return this->Export_amount;
}

//========================================= Class ListBill ============================================

ListBill::~ListBill() {}
void ListBill::Input_from_file(string filename,GoodsManagement& g, ListCustomer& lc)
{
    fstream file_in;
    file_in.open(filename, ios::in);
    if(!file_in.good())
    {
        throw string("Khong tim thay File nay!");
    }
    while (!file_in.eof())
    {
		Bill b;
        b.Input_from_file(file_in, g, lc);
        this->bill.push_back(b);
    }
    file_in.close();
}
int ListBill::Find_id(string id)
{
    for (int i = 0; i < this->bill.size(); i++)
    {
        if ((*this)[i].Get_ID().compare(id) == 0)
        {
            return i;
        }
    }
    return -1;
}
void ListBill::Add(const Bill& b)
{
    this->bill.push_back(b);
}
void ListBill::Delete(string Bill_id)
{
    int index = this->Find_id(Bill_id);
    if (index == -1)
        throw string("Khong tim thay hoa don nay!");
    else{}
        this->bill.erase(index);
}
void ListBill::Show()
{
    for (int i = 0; i < this->bill.size(); i++)
    {
        (*this)[i].Show();
    }
}
vector<Bill>& ListBill::Get_vector()
{
    return this->bill;
}
Bill& ListBill::operator[](int index)
{
    if (index > this->bill.size() || index < 0)
    {
        static Bill temp;
        return temp;
    }
    else return this->bill.at(index);
}
Bill& ListBill::Get_bill(string id)
{
    int index = this->Find_id(id);
    if (index == -1)
    {
        static Bill temp;
        return temp;
    }
    return (*this)[index];
}

