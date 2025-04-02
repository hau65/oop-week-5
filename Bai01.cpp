#include <bits/stdc++.h>
using namespace std;

class Vehicle
{
private:
    string id, name, plate;
    double revenue;

public:
    double getRevenue() const {return revenue;}
    void Input()
    {
        cout << "Nhap id: "; cin >> id;
        cin.ignore(1000, '\n');
        cout << "Nhap ten tai xe: "; getline(cin, name);
        cout << "Nhap so xe: "; cin >> plate;
        cout << "Nhap doanh thu: ";
        while (!(cin >> revenue))
        {
            cout << "Thu lai: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    string info() const
    {
        ostringstream oss;
        oss << "ID: " << id << endl;
        oss << "Ten: " << name << endl;
        oss << "So xe: " << plate << endl;
        oss << "Doanh thu: " << revenue << endl;
        return oss.str();
    }
};

class InternalV : public virtual Vehicle
{
private:
    string route;
    int kmsGone;

public:
    void Input(){
        Vehicle::Input();
        cout << "Nhap tuyen: "; cin >> route;
        cout << "Nhap so km da di: ";
        while (!(cin >> kmsGone))
        {
            cout << "Thu lai: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    void BatchInput(InternalV v[], const int& n){
        for (int i = 0; i < n; i++){
            cout << "Nhap xe noi thanh thu " << i+1 << endl;
            v[i].Input();
        }
    }

    string info() const
    {
        ostringstream oss;
        oss << Vehicle::info();
        oss << "Tuyen: " << route << endl;
        oss << "So Km da di: " << kmsGone << endl;
        return oss.str();
    }
};

class ExternalV : public virtual Vehicle
{
private:
    string destination;
    int daysGone;

public:
    void Input()
    {
        Vehicle::Input();
        cin.ignore(1000, '\n');
        cout << "Nhap noi den: "; getline(cin,destination);
        cout << "Nhap so ngay da di: ";
        while (!(cin >> daysGone))
        {
            cout << "Thu lai: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
    void BatchInput(ExternalV v[], const int& n){
        for (int i = 0; i < n; i++){
            cout << "Nhap xe ngoai thanh thu " << i+1 << endl;
            v[i].Input();
        }
    }

    string info() const
    {
        ostringstream oss;
        oss << Vehicle::info();
        oss << "Noi den: " << destination << endl;
        oss << "So ngay da di: " << daysGone << endl;
        return oss.str();
    }
};

class Manager : public InternalV, public ExternalV
{
private:
    InternalV iv[10];
    ExternalV ev[10];
    int in = 0, en = 0;
public:
    void InputIV()
    {
        cout << "So luong xe: ";
        while (!(cin >> in) || in < 0 || in > 10)
        {
            cout << "Thu lai: ";
            cin.clear();
            cin.ignore(1000,'\n');
        }
        InternalV::BatchInput(iv,in);
    }

    void OutputIV(){
        for (int i = 0; i < in; i++){
            cout << "Xe noi thanh thu " << i+1 << endl;
            cout << iv[i].info() << endl << endl;
        }
    }

    void InputEV()
    {
        cout << "So luong xe: ";
        while (!(cin >> en) || en < 0)
        {
            cout << "Thu lai: ";
            cin.clear();
            cin.ignore(1000,'\n');
        }
        ExternalV::BatchInput(ev,en);
    }

    void OutputEV(){
        for (int i = 0; i < en; i++){
            cout << "Xe ngoai thanh thu " << i+1 << endl;
            cout << ev[i].info() << endl << endl;
        }
    }

    void Menu()
    {
        int n;
        while (true)
        {
            cout << "--------------------------------MENU----------------------------" << endl;
            cout << "1. Nhap thong tin." << endl;
            cout << "2. Xuat thong tin." << endl;
            cout << "3. Xuat danh thu. " << endl;
            cout << "4. Thoat. " << endl;
            cout << "Lua chon: ";

            while (!(cin >> n) || n < 1 || n > 4)
            {
                cout << "Thu lai: ";
                cin.clear();
                cin.ignore(1000,'\n');
            }
            system("cls");
            switch(n)
            {
            case 1:
                {
                    cout << "1. Xe noi thanh. " << endl;
                    cout << "2. Xe ngoai thanh. " << endl;
                    cout << "Lua chon: ";
                    while (!(cin >> n) || n < 1 || n > 2)
                    {
                        cout << "Thu lai: ";
                        cin.clear();
                        cin.ignore(1000,'\n');
                    }
                    if (n == 1) InputIV();
                    else InputEV();
                    break;
                }
            case 2:
                {
                    cout << "1. Xe noi thanh. " << endl;
                    cout << "2. Xe ngoai thanh. " << endl;
                    cout << "Lua chon: ";
                    while (!(cin >> n) || n < 1 || n > 5)
                    {
                        cout << "Thu lai: ";
                        cin.clear();
                        cin.ignore(1000,'\n');
                    }
                    if (n == 1){
                        if (in == 0){
                            cout << "Khong co thong tin xe noi thanh." << endl;
                            break;
                        }
                        OutputIV();
                    }
                    else {
                        if (en == 0){
                            cout << "Khong co thong tin xe ngoai thanh." << endl;
                            break;
                        }
                        OutputEV();
                    }
                    break;
                }
            case 3:
                {
                    cout << "1. Xe noi thanh. " << endl;
                    cout << "2. Xe ngoai thanh. " << endl;
                    cout << "3. Tat ca. " << endl;

                    while (!(cin >> n) || n < 1 || n > 3)
                    {
                        cout << "Thu lai: ";
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    double rev = 0;
                    if (n != 2){
                        for (int i = 0; i < in; i++){
                            rev += iv[i].getRevenue();
                        }
                    }
                    if (n != 1){
                        for (int i = 0; i < en; i++){
                            rev += ev[i].getRevenue();
                        }
                    }

                    cout << "Loi nhuan: " << fixed << setprecision(0) << round(rev) << " VND." << endl;
                    break;
                }
            case 4:
                {
                    return;
                }
            default:
                {
                    break;
                }
            }
        }
    }
};

int main()
{
    Manager m;
    m.Menu();
}

/*
noi thanh:
abcd
Nguyen Trung Hau
abc12
120000
3
20
asdf
Do Quang Tien
ac456
100000
4
40
bdfc
Vu Hai Thien
nck21
200000
5
100

ngoai thanh:
kjvb
Dang Huu Nghia
kck12
50000
Long An
20
fack
Jane Doe
kdf
123000
Bangkok
40
fkjd
John Deer
kdfsa
10000000
Dubai
999
