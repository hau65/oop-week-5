#include <bits/stdc++.h>
using namespace std;
const int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
void RangeInput(int& n, const int& low = numeric_limits<int>::min(), const int& high = numeric_limits<int>::max()){
    while (!(cin >> n) || n < low || n > high){
        cout << "Thu lai: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }
}
void RangeInput(double& n, const double& low = numeric_limits<double>::min(), const double& high = numeric_limits<double    >::max()){
    while (!(cin >> n) || n < low || n > high){
        cout << "Thu lai: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }
}
bool IsLeapYear(const int& year){
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}
int GetDaysInMonth(const int& month, const int& year){
    return (month == 2 && IsLeapYear(year))? 29 : daysInMonth[month - 1];
}
bool isNum(const string& str){
    return all_of(str.begin(), str.end(), [](unsigned char c){return isdigit(c); });
}
class Date
{
private:
    int day, month, year;

public:
    int getMonth() const {return month;}
    int getYear() const {return year;}
    string info() const
    {
        ostringstream oss;
        oss << day << "/" << month << "/" << year;
        return oss.str();
    }

    static bool isRealDate(const Date& d)
    {
        if (d.month < 1 || d.month > 12) throw runtime_error("Thang khong hop le.");
        if (d.day < 1 || d.day > GetDaysInMonth(d.month, d.year)) throw runtime_error("Ngay khong hop le.");
        if (d.year < 1900) throw runtime_error("Nam khong hop le.");
        return true;
    }

    // Check if a date is valid
    friend istream& operator >> (istream& is, Date& date)
    {
        string str;
        cin >> str;
        stringstream ss(str);
        string temp[3];
        try
        {
            if (getline(ss, temp[0], '/') && isNum(temp[0])
                && getline(ss, temp[1], '/')&& isNum(temp[1])
                && getline(ss, temp[2], '/')&& isNum(temp[2]))
            {
                date.day = stoi(temp[0]);
                date.month = stoi(temp[1]);
                date.year = stoi(temp[2]);
            }
            else throw runtime_error("Dinh dang sai.");
            if (!isRealDate(date)) throw runtime_error("Ngay khong co that.");
        }
        catch (const runtime_error& e)
        {
            cout << "Loi: " << e.what() << endl << "Thu lai: ";
            is >> date;
        }
        return is;
    }

    friend ostream& operator << (ostream& os, Date& date){
        return os << date.info();
    }
};

class Transaction
{
private:
    string id;
    Date date;
    double price, area, tt;

public:
    double getTT() const {return tt;}
    void setTT(const string& str){
        if (str == "A"){
            tt *= 1.5;
        }
        if (str == "thuong"){
            tt *= 0.9;
        }
    }
    void setTT(const int& n){
        if (n == 1) tt *= 2;
        else if (n > 15) tt *= 1.2;
    }
    void setTT(const double& d) {tt = d;}
    Date getDate() const {return date;}
    void Input()
    {
        cout << "Nhap id: "; cin >> id;
        cout << "Nhap ngay(D/M/YYYY): "; cin >> date;
        cout << "Nhap gia: "; RangeInput(price,0);
        cout << "Nhap dien tich: "; RangeInput(area,0);
        tt = area * price;
    }

    void Output() const
    {
        cout << "ID: " << id << endl;
        cout << "Ngay: " << date.info() << endl;
        cout << "Gia: " << price << endl;
        cout << "Dien tich: " << area << endl;
    }
};

class Land : public Transaction
{
private:
    string type;

public:
    void Input()
    {
        Transaction::Input();
        cout << "Nhap loai (A/B/C): ";
        while (!(cin >> type) || (type != "A" && type != "B" && type != "C"))
        {
            cout << "Thu lai: ";
            cin.clear();
            cin.ignore(1000,'\n');
        }
        setTT(type);
    }

    void Output() const
    {
        Transaction::Output();
        cout << "Loai: " << type << endl;
        cout << "Thanh tien: " << getTT() << endl;
    }
};

class House : public Transaction
{
private:
    string type, address;

public:
    void Input()
    {
        Transaction::Input();
        cout << "Nhap dia chi: "; cin >> address;
        cout << "Nhap loai (cao cap/thuong): ";
        cin.ignore(1000,'\n');
        getline(cin, type);
        while (type != "cao cap" && type != "thuong")
        {
            cout << "Thu lai: ";
            cin.ignore(1000,'\n');
            getline(cin,type);
        }
        setTT(type);
    }

    void Output() const
    {
        Transaction::Output();
        cout << "Loai: " << type << endl;
        cout << "Dia chi: " << address << endl;
        cout << "Thanh tien: " << getTT() << endl;
    }
};

class Apartment : public Transaction
{
private:
    string roomID;
    int floor;

public:
    void Input()
    {
        Transaction::Input();
        cout << "Nhap ma can: "; cin >> roomID;
        cout << "Nhap tang: "; RangeInput(floor, 1, 150);
        setTT(floor);
    }

    void Output() const
    {
        Transaction::Output();
        cout << "Ma can: " << roomID << endl;
        cout << "Tang: " << floor << endl;
        cout << "Thanh tien: " << getTT() << endl;
    }
};

class Manager
{
private:
    vector<Land> l;
    vector<House> h;
    vector<Apartment> a;

public:
    void Menu()
    {
        int n;
        while (true)
        {
            cout << "--------------------------------MENU----------------------------" << endl;
            cout << "1. Nhap giao dich." << endl;
            cout << "2. Xuat giao dich." << endl;
            cout << "3. Tinh. " << endl;
            cout << "4. Thoat. " << endl;
            cout << "Lua chon: ";

            RangeInput(n,1,4);
            system("cls");
            if (n == 4) return;
            Switch(n);
        }
    }

    void Switch(int& n)
    {
        // INPUT
        if (n == 1)
        {
            cout << "1. Giao dich dat. " << endl;
            cout << "2. Giao dich nha pho. " << endl;
            cout << "3. Giao dich can ho chung cu. " << endl;
            cout << "Lua chon: "; RangeInput(n,1,3);

            //Clear previous information
            if (n == 1) l.clear();
            else if (n == 2) h.clear();
            else a.clear();

            int sl;
            cout << "So giao dich: "; RangeInput(sl,1,10);
            for (int i = 0; i < sl; i++)
            {
                cout << "Giao dich thu " << i+1 << "." << endl;
                // LAND
                if (n == 1)
                {
                    Land temp;
                    temp.Input();
                    l.push_back(temp);
                }
                //HOUSE
                else if (n == 2)
                {
                    House temp;
                    temp.Input();
                    h.push_back(temp);
                }
                //APARTMENT
                else {
                    Apartment temp;
                    temp.Input();
                    a.push_back(temp);
                }
            }
            return;
        }

        //OUTPUT
        if (n == 2)
        {
            cout << "1. Giao dich dat. " << endl;
            cout << "2. Giao dich nha pho. " << endl;
            cout << "3. Giao dich can ho chung cu. " << endl;
            cout << "4. Giao dich nha pho co gia tri cao nhat. " << endl;
            cout << "5. Danh sach cac giao dich thang 12/2024. " << endl;
            cout << "Lua chon: "; RangeInput(n,1,5);
            //LAND
            if (n == 1){
                for (const auto& i : l)
                    i.Output();
            }
            //HOUSE
            else if (n == 2){
                for (const auto& i : h)
                    i.Output();
            }
            //APARTMENT
            else if (n == 3){
                for (const auto& i : a)
                    i.Output();
            }
            else if (n == 4){
                if (h.size() == 0) {
                    cout << "Khong co giao dich nha pho. " << endl;
                    return;
                }
                House temp = h[0];
                for (int i = 1; i < h.size(); i++){
                    if (h[i].getTT() > temp.getTT())
                        temp = h[i];
                }
                cout << "Giao dich: " << endl;
                temp.Output();
            }
            else {
                cout << "Danh sach: " << endl;
                for (const auto& i : l){
                    if (i.getDate().getMonth() == 12 && i.getDate().getYear() == 2024){
                        i.Output();
                        cout << endl;
                    }
                }
                for (const auto& i : h){
                    if (i.getDate().getMonth() == 12 && i.getDate().getYear() == 2024){
                        i.Output();
                        cout << endl;
                    }
                }
                for (const auto& i : a){
                    if (i.getDate().getMonth() == 12 && i.getDate().getYear() == 2024){
                        i.Output();
                        cout << endl;
                    }
                }
            }
            return;
        }

        // CALCULATE
        if (n == 3)
        {
            cout << "1. Tong so luong tung loai. " << endl;
            cout << "2. Trung binh thanh tien cua can ho chung cu. " << endl;
            cout << "Lua chon: "; RangeInput(n,1,2);
            if (n == 1)
            {
                cout << "Tong so giao dich dat: " << l.size()  << endl;
                cout << "Tong so giao dich nha pho: " << h.size() << endl;
                cout << "Tong so giao dich can ho chung cu: " << a.size() << endl;
            }
            else {
                double av = 0;
                for (const auto& i : a) av += i.getTT();
                cout << "Trung binh: " << av << " VND. " << endl;
            }
            return;
        }
    }
};

int main()
{
    Manager m;
    m.Menu();
}
