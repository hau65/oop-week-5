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
class Transaction
{
private:
    string id, date;
    double price, tt = 0;
    int sl;
public:
    double getTT() const {return tt;}
    void setTT(const double& n){tt = n;}
    void Input()
    {
        cout << "Nhap id: "; cin >> id;
        cout << "Nhap ngay: "; cin >> date;
        cout << "Nhap don gia: "; RangeInput(price,0);
        cout << "Nhap so luong: "; RangeInput(sl,0);
        tt = price * sl;
    }

    void Output() const
    {
        cout << "ID: " << id << endl;
        cout << "Ngay: " << date << endl;
        cout << "Don gia: " << price << endl;
        cout << "So luong: " << sl << endl;
    }
};

class GoldT : public Transaction
{
private:
    string type;

public:
    void Input()
    {
        Transaction::Input();
        cout << "Nhap loai: "; cin >> type;
    }

    void Output() const
    {
        Transaction::Output();
        cout << "Loai: " << type << endl;
        cout << "Thanh tien: " << getTT() << endl;
    }
};

class MoneyT : public Transaction
{
private:
    string type;
    double rate;
public:
    string getType() const {return type;}
    void Input()
    {
        Transaction::Input();
        cout << "Nhap loai(VND/USD/Euro): ";
        while (!(cin >> type) || (type != "VND" && type != "USD" && type != "Euro"))
        {
            cout << "Thu lai: ";
            cin.clear();
            cin.ignore(1000,'\n');
        }
        if (type == "VND") rate = 1;
        else {cout << "Ti gia: "; RangeInput(rate,0);}
        setTT(getTT()*rate);
    }

    void Output() const
    {
        Transaction::Output();
        cout << "Loai: " << type << endl;
        cout << "Ti gia: " << rate << endl;
        cout << "Thanh tien: " << getTT() << endl;
    }
};

class Manager
{
private:
    vector<GoldT> g;
    vector<MoneyT> m;
public:
    void Menu()
    {
        int n;
        while (true)
        {
            cout << "--------------------------------MENU----------------------------" << endl;
            cout << "1. Nhap giao dich." << endl;
            cout << "2. Xuat giao dich." << endl;
            cout << "3. Thoat. " << endl;
            cout << "Lua chon: ";

            RangeInput(n,1,3);
            system("cls");
            if (n == 3) return;
            Switch(n);
        }
    }

    void Switch(int& n)
    {
        switch(n)
        {
        case 1:
        {
            cout << "1. Giao dich vang. " << endl;
            cout << "2. Giao dich tien te. " << endl;
            cout << "Lua chon: "; RangeInput(n,1,2);
            if (n == 1) g.clear();
            else m.clear();
            int sl;
            cout << "So luong giao dich: "; RangeInput(sl,1,10);
            for (int i = 0; i < sl; i++)
            {
                cout << "Dao dich thu " << i+1 << endl;
                if (n == 1){
                    GoldT temp;
                    temp.Input();
                    g.push_back(temp);
                }
                else{
                    MoneyT temp;
                    temp.Input();
                    m.push_back(temp);
                }
            }
            break;
        }
        case 2:
        {
            cout << "1. Giao dich vang. " << endl;
            cout << "2. Giao dich tien te. " << endl;
            cout << "3. Giao dich vang co thanh tien cao nhat. " << endl;
            cout << "4. Giao dich Euro co thanh tien thap nhat. " << endl;
            cout << "5. Giao dich thanh tien tren 1000000000. " << endl;
            cout << "Lua chon: "; RangeInput(n,1,5);
            if ((n == 1 && g.size() == 0) || (n == 2 && m.size() == 0))
                {cout << "Khong co giao dich nao. " << endl; break;}

            if (n == 1) {
                for (int i = 0; i < g.size(); i++) {
                    cout << endl << "Giao dich thu " << i+1 << endl;
                    g[i].Output();
                }
            }
            else if (n == 2) {
                for (int i = 0; i < m.size(); i++) {
                    cout << endl << "Giao dich thu " << i+1 << endl;
                    m[i].Output();
                }
            }
            else if (n == 3){
                if (g.size() == 0) {cout << "Khong co giao dich nao. " << endl; break;}
                GoldT temp = g[0];
                for (int i = 1; i < g.size(); i++){
                    if (g[i].getTT() > temp.getTT()) temp = g[i];
                }
                cout << "Giao dich vang co thanh tien cao nhat: " << endl;
                temp.Output();
            }
            else if (n == 4){
                if (m.size() == 0)
                {
                    cout << "Khong co giao dich nao. " << endl;
                    break;
                }

                MoneyT temp;
                temp.setTT(numeric_limits<double>::max());
                for (int i = 0; i < m.size(); i++){
                    if (m[i].getType() == "Euro" && m[i].getTT() < temp.getTT())
                        temp = m[i];
                }
                if (temp.getTT() == numeric_limits<double>::max()){
                    cout << "Khong tim thay giao dich nao. " << endl;
                    break;
                }
                cout << "Giao dich Euro co thanh tien thap nhat: " << endl;
                temp.Output();
            }
            else
            {
                cout << "Cac giao dich co thanh tien tren 1000000000: " << endl;
                bool found = false;
                for (const auto& i : g){
                    if (i.getTT() > 1000000000){
                        i.Output();
                        found = true;
                    }
                    cout << endl;
                }
                for (const auto& i : m){
                    if (i.getTT() > 1000000000){
                        i.Output();
                        found = true;
                    }
                    cout << endl;
                }
                if (!found) cout << "Khong tim thay. " << endl;
            }
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
