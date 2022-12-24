#include "../Header_files/Manage.h"
using namespace std;
string dis = distance();
void Check_valid_option(string checkValidOption, int &select, int maxValue)
{
    bool valid = true;
    do
    {
        if (valid == false) cout << dis << "Lua chon cua ban khong hop le... Hay chon lai: ";
        valid = true;
        getline(cin, checkValidOption);
        if (checkValidOption.empty() == false)
        {
            for (int i = 0; i < checkValidOption.length(); i++)
            {
                if (checkValidOption[i] < 48 || checkValidOption[i] > 57)
                {
                    valid = false;
                    break;
                }
            }
        }
        else valid = false;
        if (valid)
        {
            if (checkValidOption.length() >= 9)
            {
                valid = false;
            }
            else
            {
                select = stoi(checkValidOption);
                if (select < 1 || select > maxValue)
                {
                    valid = false;
                }
            }
        }
    }while (!valid);
}
void checkValidFileName(string &fileName)
{
    bool checkValid = true;
    do
    {
        if (checkValid == false) cout << dis << "Ten cua tep khong hop lai... Hay nhap lai: ";
        checkValid = true;
        getline(cin, fileName);
        for (int i = 0; i < fileName.length(); i++)
        {
            if (fileName[i] == ' ')
            {
                checkValid = false;
                break;
            }
        }
    }while(!checkValid);
}
void Update_file_database(GoodsManagement& g, ListCustomer& lc, ListBill& lb ,string File_goods_database = "../Database/Goods_database/Goods_database.txt", string File_cus_database = "../Database/Customer_database/Customer_database.txt", string File_bill_database = "../Database/Bill_database/Bill_database.txt")
{
    fstream goods_out, cus_out, bill_out;
    goods_out.open(File_goods_database, ios::out | ios::trunc);
    for (int i = 0; i < g.Get_length(); i++)
    {
        goods_out << g[i].Get_batch() << "," << g[i].Get_good_name() << ","
            << g[i].Get_origin() << "," << g[i].Get_type() << ","
            << g[i].Get_EXP().to_String() << "," << g[i].Get_amount() << ","
            << setprecision(18) << g[i].Get_cost() * g[i].Get_amount() << "," << g[i].Get_import_date().to_String();
        if (i < g.Get_length() - 1) goods_out << endl;
    }
    goods_out.ignore();
    goods_out.close();

    cus_out.open(File_cus_database, ios::out | ios::trunc);
    for (int i = 0; i < lc.Get_length(); i++) 
    {
        cus_out << lc[i].Get_ID() << "," << lc[i].Get_name() << ","
                << lc[i].Get_address() << "," << lc[i].Get_PhoneNumber();
        if (i < lc.Get_length() - 1) cus_out << endl;
    }
    cus_out.ignore();
    cus_out.close();

    bill_out.open(File_bill_database, ios::out | ios::trunc);
    for (int i = 0; i < lb.Get_vector().size(); i++)
    {
        bill_out << lb[i].Get_ID() << "," << lb[i].Get_PayStatus() << "," << lb[i].Get_date_of_bill().to_String_has_hour() << "," << lb[i].Get_vector().size() << ",";
        for (int j = 0 ; j < lb[i].Get_vector().size(); j++)
        {
            bill_out << lb[i].Get_vector().at(j)->Get_id() << "-" << lb[i].Get_vector_expAmount().at(j);
            (j < lb[i].Get_vector().size() - 1) ? bill_out << " " : bill_out << ",";
        }
        bill_out << lb[i].Get_customer()->Get_ID();
        if (i < lb.Get_vector().size() - 1) bill_out << endl;
    }
    bill_out.ignore();
    bill_out.close();
}
void Update_file_backupData(GoodsManagement& g, ListCustomer& lc, ListBill& lb)
{
    Date _local_time;
    _local_time.Set_day_real_time();
    string _file_name = "";
    _file_name += to_string(_local_time.Get_day()) + to_string(_local_time.Get_month()) + to_string(_local_time.Get_year()) + ".rec";

    fstream goods_out, cus_out, bill_out;
    goods_out.open("../Database/Backup/Goods/" + _file_name, ios::out | ios::app);
    for (int i = 0; i < g.Get_length(); i++)
    {
        goods_out << g[i].Get_batch() << "," << g[i].Get_good_name() << ","
            << g[i].Get_origin() << "," << g[i].Get_type() << ","
            << g[i].Get_EXP().to_String() << "," << g[i].Get_amount() << ","
            << setprecision(18) << g[i].Get_cost() * g[i].Get_amount() << "," << g[i].Get_import_date().to_String();
        if (i < g.Get_length() - 1) goods_out << endl;
    }
    goods_out << endl << endl;
    goods_out.close();

    cus_out.open("../Database/Backup/Customer/" + _file_name, ios::out | ios::app);
    for (int i = 0; i < lc.Get_length(); i++) 
    {
        cus_out << lc[i].Get_ID() << "," << lc[i].Get_name() << ","
                << lc[i].Get_address() << "," << lc[i].Get_PhoneNumber();
        if (i < lc.Get_length() - 1) cus_out << endl;
    }
    cus_out << endl << endl;
    cus_out.close();

    bill_out.open("../Database/Backup/Bill/" + _file_name, ios::out | ios::app);
    for (int i = 0; i < lb.Get_vector().size(); i++)
    {
        bill_out << lb[i].Get_ID() << "," << lb[i].Get_PayStatus() << "," << lb[i].Get_date_of_bill().to_String_has_hour() << "," << lb[i].Get_vector().size() << ",";
        for (int j = 0 ; j < lb[i].Get_vector().size(); j++)
        {
            bill_out << lb[i].Get_vector().at(j)->Get_id() << "-" << lb[i].Get_vector_expAmount().at(j);
            (j < lb[i].Get_vector().size() - 1) ? bill_out << " " : bill_out << ",";
        }
        bill_out << lb[i].Get_customer()->Get_ID();
        if (i < lb.Get_vector().size() - 1) bill_out << endl;
    }
    bill_out << endl << endl;
    bill_out.close();
}
void Import(GoodsManagement &g)
{
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        cout << dis << " ------ TINH NANG NHAP HANG ------ " << endl
             << dis << "|       1. Tu file                |" << endl
             << dis << "|       2. Tu nguoi su dung       |" << endl
             << dis << "|       3. Quay lai               |" << endl
             << dis << " --------------------------------- " << endl
             << dis << " Lua chon: ";
        Check_valid_option(checkValidOption, select, 3);
        switch (select)
        {
        case 1:
        {
            string file_name;
            cout << dis << "Ten file: "; checkValidFileName(file_name);
            try 
            {
                g.Input_from_file(file_name);
                cout << dis << "Nhap hang tu file " << file_name << " thanh cong..." << endl;
            }
            catch (string e)
            {
                cout << dis << e << endl;
            }
            cout << dis; system("pause");  
            break;
        }
        case 2:
        {
            g.Input();
            cout << dis << "Nhap hang thanh cong..." << endl;
            cout << dis; system("pause");
            break;
        }
        }
    }while ( select < 3);
}
void Export(GoodsManagement &g, ListCustomer &lc, ListBill &lb)
{
    int select;
    bool check_export =  false, check_print_bill = true;
    do
    {
        string checkValidOption;
        system("cls");
        cout << dis << " ------ TINH NANG XUAT HANG ------ " << endl
             << dis << "|       1. Theo goi               |" << endl
             << dis << "|       2. Theo nguoi su dung     |" << endl
             << dis << "|       3. In hoa don             |" << endl
             << dis << "|       4. Quay lai               |" << endl
             << dis << "---------------------------------- " << endl
             << dis << " Lua chon: ";
        Check_valid_option(checkValidOption, select, 4);        
        switch (select)
        {
        case 1:
            try
            {
                if (!check_print_bill) cout << dis << "Ban phai in hoa don moi nhat truoc khi thuc hien cho lan tiep theo!" << endl;
                else
                {
                    string filename;
                    cout << dis << "File name: "; checkValidFileName(filename);
                    g.Export_from_file(filename, lc, lb);
                    cout << dis << "Xuat hang thanh cong ..." << endl;
                    check_export = true;
                    check_print_bill = false;
                }
                cout << dis; system("pause");
                break;
            }
            catch(string e)
            {
                check_export = false;
                cout << dis << e << endl;
                cout << dis; system("pause");
                break;
            }
        case 2:
        {
            try
            {
                if (!check_print_bill) cout << dis << "Ban phai in hoa don moi nhat truoc khi thuc hien cho lan tiep theo!" << endl;
                else
                {
                    g.Export(lc, lb);
                    cout << dis << "Xuat hang thanh cong!..." << endl;
                    check_export = true;
                    check_print_bill = false;
                }
                cout << dis; system("pause");
                break;
            }
            catch (string e)
            {
                check_export = false;
                cout << dis << e << endl;
                cout << dis; system("pause");
                break;
            }
        }
        case 3:
        {
            if (check_export)
            {
                string file_name = "../Bill.txt";
                lb[lb.Get_vector().size()-1].Print(file_name);
                cout << dis << "In hoa don thanh cong!..." << endl;
                check_export = false;
                check_print_bill = true;
            }
            else cout << dis << "Ban khong co hoa don nao de in..." << endl;
            cout << dis; system("pause");
            break;
        }
        default:
        {
            if (!check_print_bill) 
            {
                cout << dis << "Ban phai in hoa don moi nhat truoc khi thoat tinh nang nay!" << endl;
                cout << dis; system("pause");
                select = 0;
            }
        }
        }
    }while(select < 4);
}
void Update(GoodsManagement &g)
{
    string Goods_name, checkValidOption;
    cout << dis << "Nhap ten hang hoa ma ban muon cap nhat: "; getline(cin, Goods_name);
    if (g.Find_name_goods(Goods_name) == false) cout<< dis << "Khong co hang hoa nay trong kho!" << endl;
    else
    {
        map<int, string> mapping;
        Standardized(Goods_name);
        g.Search(mapping, Goods_name, 1);
        int select, index_of_id;
        cout << dis << "Lua chon hang hoa de cap nhat: "; Check_valid_option(checkValidOption, index_of_id, mapping.size());
        int index = g.Find_id(mapping[index_of_id]);
        if (index == -1)
        {
            cout << dis << "Khong tim thay hang hoa nay." << endl;
            return;
        }
        try
        {
            do
            {
                string checkValidOption;
                system("cls");
                g.Search(mapping, Goods_name, 1);
                cout << dis << " ------ TINH NANG CAP NHAT ------ " << endl
                    << dis << "|         1. Lo                   |" << endl
                    << dis << "|         2. Ten                  |" << endl
                    << dis << "|         3. Nguon goc            |" << endl
                    << dis << "|         4. Loai                 |" << endl
                    << dis << "|         5. Han su dung          |" << endl
                    << dis << "|         6. So luong             |" << endl
                    << dis << "|         7. Gia nhap             |" << endl
                    << dis << "|         8. Ngay nhap            |" << endl
                    << dis << "|         9. Quay lai             |" << endl
                    << dis << " --------------------------------- " << endl
                    << dis << " Lua chon: ";
                Check_valid_option(checkValidOption, select, 9);                    
                switch (select)
                {
                    case 1:
                        cout << dis << "Lo: ";
                        g.Update(index, select);
                        cout << dis << "Cap nhat lo thanh cong..." << endl;
                        cout << dis; system("pause");
                        break;
                    case 2:
                        cout << dis << "Ten: ";
                        g.Update(index, select);
                        Goods_name = g[index].Get_good_name();
                        cout << dis << "Cap nhat ten thanh cong..." << endl;
                        cout << dis; system("pause");
                        break;
                    case 3:
                        cout << dis << "Nguon goc: ";
                        g.Update(index, select);
                        cout << dis << "Cap nhat nguon goc thanh cong..." << endl;
                        cout << dis; system("pause");
                        break;
                    case 4:
                        cout << dis << "Loai: ";
                        g.Update(index, select);
                        cout << dis << "Cap nhat loai thanh cong..." << endl;
                        cout << dis; system("pause");
                        break;
                    case 5:
                        try
                        {
                            cout << dis << "Han su dung";
                            g.Update(index, select);
                            cout << dis << "Cap nhat han su dung thanh cong..." << endl;
                            cout << dis; system("pause");
                            break;
                        }
                        catch(string e)
                        {
                            cout << dis << e << endl;
                            cout << dis; system("pause");
                            break;
                        }
                    case 6:
                        cout << dis << "So luong: ";
                        g.Update(index, select);
                        cout << dis << "Cap nhat so luong thanh cong..." << endl;
                        cout << dis; system("pause");
                        cin.ignore();
                        break;
                    case 7:
                        cout << dis << "Gia nhap: ";
                        g.Update(index, select);
                        cout << dis << "Cap nhat gia nhap thanh cong..." << endl;
                        cout << dis; system("pause");
                        cin.ignore();
                        break;
                    case 8:
                        try
                        {
                            cout << dis << "Ngay nhap";
                            g.Update(index, select);
                            cout << dis << "Cap nhat ngay nhap thanh cong..." << endl;
                            cout << dis; system("pause");
                            break;
                        }
                        catch(string e)
                        {
                            cout << dis << e << endl;
                            cout << dis; system("pause");
                            break;
                        }
                    default:
                        cout << dis << "Cap nhat hang hoa thanh cong..." << endl;     
                }
            } while (select < 9);
        }
        catch(string e)
        {
            cout << dis << e << endl;
        }
    }
}
void Delete(GoodsManagement &g)
{
    string Goods_name, checkValidOption;
    cout << dis << "Nhap ten hang hoa ma ban muon xoa: "; getline(cin, Goods_name); Standardized(Goods_name);
    if (g.Find_name_goods(Goods_name) == false) cout << dis << "Khong co hang hoa nay trong kho." << endl;
    else
    {
        map<int, string> mapping;
        g.Search(mapping, Goods_name, 1);
        int select;
        cout << dis << "Lua chon hang hoa de xoa: "; Check_valid_option(checkValidOption, select, mapping.size());
        try
        {
            g.Delete(mapping.at(select));
            cout << dis << "Xoa hang hoa thanh cong..." << endl;         
        }
        catch(string e)
        {
            cout << dis << e << endl;
        } 
    }
}
void Sort(GoodsManagement &g)
{
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        g.Show_information();
        cout << dis << " ------- TINH NANG SAP XEP ------ " << endl
             << dis << "|       1. Theo ten              |" << endl
             << dis << "|       2. Theo han su dung      |" << endl
             << dis << "|       3. Theo ngay nhap        |" << endl
             << dis << "|       4. Theo loai             |" << endl
             << dis << "|       5. Quay lai              |" << endl
             << dis << " -------------------------------- " << endl;
        cout << dis << " Lua chon: ";
        Check_valid_option(checkValidOption, select, 5);
        if (select < 5)
        {
            bool ascORdesc; int checkAsc;
            cout << dis << "Tang dan[1] hay Giam dan[2]: "; Check_valid_option(checkValidOption, checkAsc, 2);
            ascORdesc = (checkAsc == 1) ? true : false;
            switch (select)
            {
            case 1:
                g.Sort(Sort_by_name, ascORdesc, 0, g.Get_length() - 1);
                break;
            case 2:
                g.Sort(Sort_by_EXP, ascORdesc, 0, g.Get_length() - 1);
                break;
            case 3:
                g.Sort(Sort_by_impDate, ascORdesc, 0, g.Get_length() - 1);
                break;
            case 4:
                g.Sort(Sort_by_type, ascORdesc, 0, g.Get_length() - 1);
                break;
            }
            g.Show_information();
            cout << dis; system("pause");
        }
    }while(select < 5);
}
void Search(GoodsManagement &g)
{
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        cout << dis << " ------- TINH NANG TIM KIEM ------- " << endl
             << dis << "|       1. Theo ten san pham       |" << endl
             << dis << "|       2. Theo loai san pham      |" << endl
             << dis << "|       3. Theo lo hang            |" << endl
             << dis << "|       4. Quay lai                |" << endl
             << dis << " ---------------------------------- " << endl;
        cout << dis << " Lua chon: ";
        Check_valid_option(checkValidOption, select, 4);
        map<int, string> mapping;
        switch (select)
        {
        case 1:
        {
            string goods_name;
            cout << dis << "Nhap ten hang hoa ma ban muon tim kiem: "; getline(cin, goods_name);
            Standardized(goods_name);
            g.Search(mapping, goods_name, 1);
            break;
        }
        case 2:
        {
            string goods_type;
            cout << dis << "Nhap loai hang hoa ma ban muon tim kiem: "; getline(cin, goods_type);
            Standardized(goods_type);
            g.Search(mapping, goods_type, 2);
            break;
        }
        case 3:
        {
            string goods_batch;
            cout << dis << "Nhap Lo hang ma ban muon tim kiem: "; getline(cin, goods_batch);
            Standardized(goods_batch);
            g.Search(mapping, goods_batch, 3);
            break;
        }
        }
        if (select < 4) { cout << dis; system("pause"); }
    }while (select < 4);
    
}
void Goods_Object(GoodsManagement &g, ListCustomer &lc, ListBill &lb)
{
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        cout << dis << " ------ DANH SACH LUA CHON CHO HANG HOA ------ " << endl
             << dis << "|         1. Nhap hang                        |" << endl
             << dis << "|         2. Xuat hang                        |" << endl
             << dis << "|         3. Cap nhat                         |" << endl
             << dis << "|         4. Xoa                              |" << endl
             << dis << "|         5. Sap xep                          |" << endl
             << dis << "|         6. Tim kiem                         |" << endl
             << dis << "|         7. Hien thi thong tin               |" << endl
             << dis << "|         8. Quay lai                         |" << endl
             << dis << " --------------------------------------------- " << endl;
        cout << dis << " Lua chon: ";
        Check_valid_option(checkValidOption, select, 8);
        switch (select)
        {
        case 1:
            Import(g);
            break;
        case 2:
            Export(g, lc, lb);
            break;
        case 3:
            Update(g);
            cout << dis; system("pause");
            break;
        case 4:
            Delete(g);
            cout << dis; system("pause");
            break;
        case 5:
        {
            Sort(g);
            cout << dis; system("pause");
            break;
        }    
        case 6:
        {
            Search(g);
            break;
        }
        case 7:
        {
            g.Show_information();
            cout << dis; system("pause");
            break;
        }
    }
    }while (select < 8);
}
void Customer_Object(GoodsManagement &g, ListCustomer &lc, ListBill &lb)
{
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        cout << dis << " -------- DANH SACH LUA CHON CHO KHACH HANG ------- " << endl
             << dis << "|          1. Them khach hang moi                  |" << endl
             << dis << "|          2. Cap nhat                             |" << endl
             << dis << "|          3. Xoa                                  |" << endl
             << dis << "|          4. Tim kiem                             |" << endl
             << dis << "|          5. Hien thi thong tin                   |" << endl
             << dis << "|          6. Thanh toan hoa don                   |" << endl 
             << dis << "|          7. Lich su thanh toan                   |" << endl            
             << dis << "|          8. Quay lai                             |" << endl
             << dis << " ---------------------------------------------------" << endl;
        cout << dis << " Lua chon: ";
        Check_valid_option(checkValidOption, select, 8);
        switch (select)
        {
            case 1:
            {
                try
                {
                    Customer c;
                    cin >> c;
                    lc.Add(c);
                    cout << dis << "Them khach hang moi thanh cong..." << endl;  
                    cout << dis; system("pause");
                    break;
                }
                catch(string e)
                {
                    cout << dis << e << endl;
                    cout << dis; system("pause");
                }
            }            
            case 2:
            {
                string id;
                cout << dis << "Nhap ID cua khach hang ma ban muon cap nhat: "; getline(cin, id);
                int index = lc.Find_id(id);
                if (index == -1) 
                {
                    cout << dis << "Khong tim thay ID nay..." << endl;
                    cout << dis; system("pause");
                }
                else
                {
                    int select;
                    do
                    {
                        system("cls");
                        lc.Show_information(id);
                        string checkValidOption;
                        cout << dis << " ------ TINH NANG CAP NHAT ------ " << endl
                            << dis << "|       1. Ten                    |" << endl
                            << dis << "|       2. Dia chi                |" << endl
                            << dis << "|       3. So dien thoai          |" << endl
                            << dis << "|       4. Quay lai               |" << endl
                            << dis << " --------------------------------- " << endl
                            << dis << " Lua chon: ";
                        Check_valid_option(checkValidOption, select, 4);
                        lc.Update(index, select);
                        if (select < 4) { cout << dis; system("pause"); }
                    } while(select < 4);
                }
                break;
            }
            case 3:
            {
                try
                {
                    string id;
                    cout << dis << "Nhap ID cua khach hang ma ban muon xoa: "; getline(cin, id);
                    lc.Delete(id, lb);
                    cout << dis << "Xoa khach hang co ID: " << id << " thanh cong..." << endl;
                    cout << dis; system("pause");
                    break;
                }
                catch(string e)
                {
                    cout << dis << e << endl;
                    cout << dis; system("pause");
                    break;
                }
            }
            case 4:
            {
                try
                {
                    string id;
                    cout << dis << "Nhap ID cua khach hang ma ban muon tim kiem: "; getline(cin, id);
                    lc.Show_information(id);   
                    cout << dis; system("pause");
                    break;
                }
                catch(string e)
                {
                    cout << dis << e << endl;
                    cout << dis; system("pause");
                }
            }
            case 5:
                lc.Show_information();   
                cout << dis; system("pause");
                break;
            case 6:
            {
                try
                {
                    string id;
                    int indexOfListBill;
                    cout << dis << "Nhap ID khach hang muon thanh toan hoa don tra sau: "; getline(cin, id);
                    int indexOfListCustomer = lc.Find_id(id);
                    if (indexOfListCustomer != -1)
                    {
                        lc.Show_information(id);
                        if (lc[indexOfListCustomer].Get_vector().size() == 0)
                        {
                            cout << dis << "Khach hang nay chua mua hang hoa nao!" << endl;
                        }
                        else indexOfListBill = lb.Find_id(lc[indexOfListCustomer].Get_vector().at(lc[indexOfListCustomer].Get_vector().size() - 1).Get_ID());


                        if (lb[indexOfListBill].Get_PayStatus())
                        {
                            cout << dis << "Khach hang nay da thanh toan hoa don!" << endl;
                        }
                        else
                        {
                            cout << dis << "Xac nhan thanh toan: Co[1] | Khong [2]: "; 
                            char ch;
                            do
                            {
                                ch = getchar(); cin.ignore();
                                if (ch == '1') lb[indexOfListBill].Set_PayStatus(true);
                                else if (ch != '2') 
                                {
                                    ch = '0';
                                    cout << dis << "Xac nhan khong chinh xac ... Lua chon lai: ";
                                }
                            }while(ch == '0');
                            cout << dis << "Xac nhan thanh toan hoa don thanh cong" << endl;
                            lc[indexOfListCustomer].Update_bill(lb[indexOfListBill]);
                        }
                    }
                    else cout << dis << "Khong tim thay khach hang nay!" << endl;
                    cout << dis; system("pause");
                    break;  
                }
                catch(string e)
                {
                    cout << dis << e << endl;
                    cout << dis; system("pause");
                    break;
                }
            }
            case 7:
            {
                string id;
                cout << dis << "Nhap ID khach hang ma ban muon xem lich su thanh toan: "; getline(cin, id);
                int index = lc.Find_id(id);
                if(index != -1)
                {
                    string dis_temp = dis;
                    dis_temp.erase(0, 4);
                    cout << dis_temp << "-------------------------------------- LICH SU THANH TOAN --------------------------------------" << endl << endl;
                    for (int i = 0; i < lc[index].Get_vector().size(); i++)
                    {
                        lc[index].Get_vector()[i].Show();
                        cout << dis_temp << "________________________________________________________________________________________________" << endl << endl;
                    }
                    cout << dis_temp << "------------------------------------------- KET THUC -------------------------------------------" << endl;
                }
                else
                {
                    cout << dis << "Khong tim thay khach hang nay!" << endl;
                }
                cout << dis; system("pause");
            }
        }
    }while (select < 8);
}
void Menu(GoodsManagement &g, ListCustomer &lc, ListBill &lb)
{
    try
    {
        g.Input_from_file("../Database/Goods_database/Goods_database.txt");
        lc.Input_from_file("../Database/Customer_database/Customer_database.txt");
        lb.Input_from_file("../Database/Bill_database/Bill_database.txt", g, lc);
    }
    catch(string e)
    {
        cout << dis << e << endl;
        cout << dis; system("pause");
        return;
    }
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        cout << dis << " ------- LUA CHON DOI TUONG ------- " << endl
             << dis << "|       1. Khach hang              |" << endl
             << dis << "|       2. Hang hoa                |" << endl
             << dis << "|       3. Thoat                   |" << endl
             << dis << " ---------------------------------- " << endl;
        cout << dis << " Lua chon: ";
        Check_valid_option(checkValidOption, select, 4);
        switch (select)
        {
        case 1:
            Customer_Object(g, lc, lb);
            break;
        case 2:
            Goods_Object(g, lc, lb);
            break;
        default:
            Update_file_database(g, lc, lb);
            Update_file_backupData(g,lc,lb);
            cout << endl << dis << "Cam on ban da su dung dich vu cua chung toi ^_^...  Chuc ban mot ngay tot lanh!" << endl << endl;
        }   
    } while (select < 3);
}
int main()
{
    GoodsManagement g;
    ListCustomer lc;
    ListBill lb;
    Menu(g, lc, lb);
    return 0;
}
