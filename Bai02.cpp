#include <bits/stdc++.h>
using namespace std;

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

class Book
{
private:
    string id, date, publisher;
    double price, tt = -1;
    int sl;

public:
    void setTT(const string& str){
        if (str == "moi") tt = price * sl;
        else tt = price * sl / 2;
    }
    void setTT(const double& tax){ tt = price * sl + tax;}
    double getTT()const{return tt;}
    string getPublisher() const {return publisher;}
    void Input()
    {
        cout << "Nhap ma: "; cin >> id;
        cout << "Nhap ngay nhap: "; cin >> date;
        cin.ignore(1000, '\n');
        cout << "Nhap nha xuat ban: "; getline(cin,publisher);
        cout << "Nhap don gia: "; RangeInput(price, 0);
        cout << "Nhap so luong: "; RangeInput(sl, 0);
    }

    void Output()
    {
        cout << "Ma: " << id << endl;
        cout << "Ngay nhap: " << date << endl;
        cout << "Nha xuat ban: " << publisher << endl;
        cout << "Don gia: " << price << endl;
        cout << "So luong: " << sl << endl;
    }
};

class GK : public Book
{
private:
    string state;

public:
    void Input()
    {
        Book::Input();
        cout << "Nhap tinh trang: ";
        while (!(cin >> state) || (state != "moi" && state != "cu"))
        {
            cout << "Thu lai: ";
            cin.clear();
            cin.ignore(1000,'\n');
        }
        setTT(state);
    }

    void Output()
    {
        Book::Output();
        cout << "Tinh trang: " << state << endl;
        cout << "Thanh tien: " << getTT() << endl;
    }
};

class TK : public Book
{
private:
    double tax;

public:
    void Input()
    {
        Book::Input();
        cout << "Nhap thue: "; RangeInput(tax, 0);
        setTT(tax);
    }

    void Output()
    {
        Book::Output();
        cout << "Thue: " << tax << endl;
        cout << "Thanh tien: " << getTT() << endl;
    }
};

class Manager
{
private:
    GK gk[3];
    TK tk[3];
    int nGk = 0, nTk = 0;
    int sl;
public:
    void Menu()
    {
        int n;
        while (true)
        {
            cout << "--------------------------------MENU----------------------------" << endl;
            cout << "1. Nhap sach." << endl;
            cout << "2. Xuat sach." << endl;
            cout << "3. Tinh. " << endl;
            cout << "4. Thoat. " << endl;
            cout << "Lua chon: ";

            while (!(cin >> n) || n < 1 || n > 4)
            {
                cout << "Thu lai: ";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            system("cls");
            if (n == 4) return;
            Switch(n);
        }
    }

    void Switch(int& n){
        switch(n)
        {
        case 1:
        {
            cout << "1. Sach giao khoa. " << endl;
            cout << "2. Sach tham khao. " << endl;
            cout << "Lua chon: "; RangeInput(n,1,2);
            cout << "So luong sach nhap: ";
            if (n == 1){RangeInput(nGk,1,3); sl = nGk;}
            else {RangeInput(nTk,1,3); sl = nTk;}
            for (int i = 0; i < sl; i++)
            {
                cout << "Sach thu " << i+1 << endl;
                if (n == 1) gk[i].Input();
                else tk[i].Input();
            }
            break;
        }
        case 2:
        {
            cout << "1. Sach giao khoa. " << endl;
            cout << "2. Sach tham khao. " << endl;
            cout << "3. SGK theo nha xuat ban. " << endl;
            cout << "Lua chon: "; RangeInput(n,1,3);
            if (n == 3)
            {
                cout << "Nhap nha xuat ban: ";
                string temp; cin >> temp;
                cout << "Danh sach SGK cua nha xuat ban " << temp << ":" << endl;
                bool found = false;
                for (int i = 0; i < nGk; i++){
                    if (gk[i].getPublisher() == temp){
                        gk[i].Output();
                        found = true;
                    }
                }
                if (!found) cout << "Khong co SGK nao." << endl;
                break;
            }
            if ((n == 1 && nGk == 0) || (n == 2 && nTk == 0))
            {
                cout << "Khong co sach nao." << endl;
                break;
            }

            sl = (n == 1)? nGk : nTk;
            for (int i = 0; i < sl; i++)
            {
                cout << endl << "Sach thu " << i+1 << endl;
                if (n == 1) gk[i].Output();
                else tk[i].Output();
            }
            break;
        }
        case 3:
        {
            cout << "1. Thanh tien sach giao khoa. " << endl;
            cout << "2. Thanh tien sach tham khao. " << endl;
            cout << "3. Trung binh cong don gia sach tham khao. " << endl;
            cout << "Lua chon: "; RangeInput(n,1,3);
            double cal = 0;
            if (n == 1) {
                for (int i = 0; i < nGk; i++){
                    cal += gk[i].getTT();
                }
                cout << "Thanh tien SGK: " << fixed << setprecision(0) << cal << " VND. " << endl;
                break;
            }
            if (n == 2) {
                for (int i = 0; i < nTk; i++){
                    cal += tk[i].getTT();
                }
                cout << "Thanh tien STK: " << fixed << setprecision(0) << cal << " VND. " << endl;
                break;
            }
            if (n == 3) {
                for (int i = 0; i < nTk; i++){
                    cal += tk[i].getTT();
                }
                cal /= 3;
                cout << "TBC don gia STK: " << fixed << setprecision(0) << cal << " VND. " << endl;
                break;
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }
};

int main()
{
    Manager m;
    m.Menu();
}
