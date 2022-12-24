#include "../Header_files/Customer.h"
#include "../Header_files/Date.h"
#include <string>
#include <iostream>
// #include "NumberDuck.h"
// #include <sstream>
// #include <stdio.h>

// using namespace NumberDuck;
using namespace std;

//========================================= Class Customer ============================================

Customer::Customer(string id, string name, string address, string phone)
{
	this->ID = id;
    this->Name = name;
    this->Address = address;
    this->PhoneNumber = phone;
}
Customer::~Customer()
{
}
void Customer::Set_Name(string name)
{
	this->Name = name;
}
void Customer::Set_Address(string add)
{
	this->Address = add;
}
void Customer::Set_PhoneNumber(string phone)
{
	this->PhoneNumber = phone;
}
void Customer::Add_bill(Bill& b)
{
	b.Add_customer(this);
	this->Lb.push_back(b);
}
string Customer::Get_ID() const
{
	return this->ID;
}
string Customer::Get_name() const
{
	return this->Name;
}
string Customer::Get_address() const
{
	return this->Address;
}
string Customer::Get_PhoneNumber() const
{
	return this->PhoneNumber;
}
vector<Bill>& Customer::Get_vector()
{
	return this->Lb;
}
void Customer::Update_bill(Bill b)
{
	for (int i = 0; i < this->Lb.size(); i++)
	{
		if (this->Lb[i].ID.compare(b.ID) == 0)
		{
			this->Lb[i] = b;
			break;
		}
	}
	throw string("Khach hang nay khong mua hoa don nay!");
}
void Customer::Input_from_file(fstream& in)
{
	getline(in, this->ID, ',');
	getline(in, this->Name, ',');
	getline(in, this->Address, ',');
	getline(in, this->PhoneNumber, '\n');
}
Customer& Customer::operator=(Customer& _other)
{
	if (this != &_other)
	{
		this->ID = _other.ID;
		this->Name = _other.Name;
		this->Address = _other.Address;
		this->PhoneNumber = _other.PhoneNumber;
		this->Lb = _other.Lb;
	}
	return (*this);
}
istream& operator>>(istream& in, Customer& c)
{
	cout << distance() << "------------ THONG TIN KHACH HANG ----------" << endl;
	cout << distance() << "ID: "; getline(in, c.ID);
	cout << distance() << "Ho va ten: "; getline(in, c.Name); Standardized(c.Name);
	cout << distance() << "Dia chi: "; getline(in, c.Address);
	cout << distance() << "So dien thoai: "; getline(in, c.PhoneNumber);
	cout << distance() << "----------------- KET THUC -----------------" << endl;
	return in;
}
ostream& operator<<(ostream& out, const Customer& c)
{
	out << " " << setw(12) << c.ID << " |" << " " << setw(24) << c.Name << " |"
	    << " " << setw(25) << c.Address << " |" << "  " << setw(10) << c.PhoneNumber << "  |"
		<< " " << setw(21) << const_cast<Customer&>(c).Lb.at(const_cast<Customer&>(c).Lb.size() - 1).Get_ID() << " |";
	return out;
}


// =================================== Class ListCustomer ==========================================
ListCustomer::ListCustomer() {}
ListCustomer::~ListCustomer() {}
int ListCustomer::Get_length() const
{
	return this->List.size();
}
bool ListCustomer::Check_valid_ID(string id)
{
	for (int i = 0; i < this->List.size(); i++)
	{
		if ((*this)[i].Get_ID().compare(id) == 0)
			return false;
	}
	return true;
}
Customer& ListCustomer::operator[](int index)
{
	if (index > this->List.size() || index < 0)
	{
		static Customer c;
		return c;
	}
	return this->List[index];
}
int ListCustomer::Find_id(string id)
{
	for (int i = 0; i < this->List.size(); i++)
	{
		if ((*this)[i].Get_ID().compare(id) == 0)
		{
			return i;
		}
	}
	return -1;
}
void ListCustomer::Input_from_file(string filename)
{
    fstream file_in;
    file_in.open(filename, ios::in);
    if(!file_in.good())
    {
        throw string("Khong tim thay File nay!");
    }
    while (!file_in.eof())
    {
		Customer s;
        s.Input_from_file(file_in);
        this->List.push_back(s);
    }
    file_in.close();
}
void ListCustomer::Add(const Customer &_new_customer)
{
	if (this->Check_valid_ID(const_cast<Customer&>(_new_customer).Get_ID())) this->List.push_back(_new_customer);
	else
		throw string("ID khach hang khong hop le ...");
}
void ListCustomer::Update(int index, int option)
{
	switch (option)
	{
	case 1:
	{
		string _name;
		cout << distance() << "Ten: "; getline(cin, _name); Standardized(_name);
		(*this)[index].Set_Name(_name);
		cout << distance() << "Cap nhat ten khach hang thanh cong..." << endl;
		break;
	}
	case 2:
	{
		string _address;
		cout << distance() << "Dia chi: "; getline(cin, _address); Standardized(_address);
		(*this)[index].Set_Address(_address);
		cout << distance() << "Cap nhat dia chi khach hang thanh cong..." << endl;
		break;
	}
	case 3:
	{
		string _phoneNumber;
		cout << distance() << "So dien thoai: "; getline(cin, _phoneNumber); Standardized(_phoneNumber);
		(*this)[index].Set_PhoneNumber(_phoneNumber);
		cout << distance() << "Cap nhat so dien thoai khach hang thanh cong..." << endl;
		break;
	}
	}

}
void ListCustomer::Delete(string id, ListBill& lb)
{
	int index = this->Find_id(id);
    if (index == -1) throw string("Khong tim thay ID nay...");
	else
	{
		for (int i = 0; i < (*this)[index].Get_vector().size(); i++)
		{
			lb.Delete((*this)[index].Get_vector()[i].Get_ID());
		}
		this->List.erase(index);
	}	
}
void ListCustomer::Show_information(string id)
{
	string dis = distance();
	if (this->List.empty()) cout << dis << "Danh sach khach hang trong..." << endl;
	else if (id.compare("") != 0 && this->Find_id(id) == -1)
    {
        cout << dis << "Khong co khach hang nay!" << endl;
    }
	else if (id.compare("") == 0)
	{
		dis = distance(20);
		cout <<    dis << " ___________________________________________________________________________________________________________________________________________ " << endl
				<< dis << "                                                            THONG TIN KHACH HANG                                                             " << endl
				<< dis << " ------------------------------------------------------------------------------------------------------------------------------------------- " << endl
				<< dis << "| STT |      ID      |      Ten khach hang      |          Dia chi          |      SDT     |  Ma hoa don gan nhat  | Trinh trang thanh toan |" << endl
				<< dis << " ___________________________________________________________________________________________________________________________________________ " << endl;
		for (int i = 0; i < this->List.size(); i++) 
		{
			cout << dis << "|" << setw(4) << i + 1 << " |";
			cout << (*this)[i];
			cout << "    " << setw(16);
			((*this)[i].Get_vector().at((*this)[i].Get_vector().size() - 1).Get_PayStatus()) ? cout << "Da thanh toan" : cout << "Chua thanh toan";
			cout << "    |" << endl;
			cout << dis << " ___________________________________________________________________________________________________________________________________________ " << endl;
		}
		cout << dis << " ----------------------------------------------------------------- KET THUC ---------------------------------------------------------------- " << endl;
	}
	else
	{
		dis = distance(20);
		cout <<    dis << " ___________________________________________________________________________________________________________________________________________ " << endl
				<< dis << "                                                             THONG TIN KHACH HANG                                                            " << endl
				<< dis << " ------------------------------------------------------------------------------------------------------------------------------------------- " << endl
				<< dis << "| STT |      ID      |      Ten khach hang      |          Dia chi          |      SDT     |  Ma hoa don gan nhat  | Trinh trang thanh toan |" << endl
				<< dis << " ___________________________________________________________________________________________________________________________________________ " << endl;
		int i = this->Find_id(id);
		cout << dis << "|" << setw(4) << 1 << " |";
		cout << (*this)[i];
		cout << "    " << setw(16);
		((*this)[i].Get_vector().at((*this)[i].Get_vector().size() - 1).Get_PayStatus()) ? cout << "Da thanh toan" : cout << "Chua thanh toan";
		cout << "    |" << endl;
		cout << dis << " ___________________________________________________________________________________________________________________________________________ " << endl;
		cout << dis << " ----------------------------------------------------------------- KET THUC ---------------------------------------------------------------- " << endl;
	}
	
}
// void ListCustomer::List_out()
// {
// 	ListCustomer a;
// 	Workbook workbook("");
// 	Worksheet* pWorksheet = workbook.GetWorksheetByIndex(0);

// 	for (uint16_t i = 0; i < this->Get_AmountCustomer(); i++)
// 	{
// 		Cell* pCell = pWorksheet->GetCell(0, i);
// 		pCell->SetFloat(i + 1);
// 		//pCell->SetFloat(i * 2.34f);
// 	}
// 	int j = 0;
// 	for (Customer i : this->list)
// 	{
// 		string s;
// 		s = i.Get_name();

// 		char* g = const_cast<char*>(s.c_str());
// 		pWorksheet->GetCell(1, j)->SetString(g);
// 		s = i.Get_address();
// 		g = const_cast<char*>(s.c_str());
// 		pWorksheet->GetCell(2, j)->SetString(g);
// 		s = i.Get_PhoneNumber();
// 		g = const_cast<char*>(s.c_str());
// 		pWorksheet->GetCell(3, j)->SetString(g);
// 		s = i.Get_Condition();
// 		g = const_cast<char*>(s.c_str());
// 		pWorksheet->GetCell(4, j)->SetString(g);
		
// 	}
// 	workbook.Save("ListCustomer.xls");

// 	Workbook* pWorkbookIn = new Workbook("");
// 	if (pWorkbookIn->Load("ListCustomer.xls"))
// 	{
// 		Worksheet* pWorksheetIn = pWorkbookIn->GetWorksheetByIndex(0);
// 		Cell* pCellIn = pWorksheetIn->GetCell(2, 1);
// 		printf("Formula: %s\n", pCellIn->GetFormula());
// 	}
// }