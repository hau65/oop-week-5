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
class Employee
{
private:
    string name, dob;
    int salary;

public:
    void CalSalary(const int& daysWorked){salary = daysWorked * 100000;}
    void CalSalary(const int& basicS, const int& productNum) {salary = basicS + productNum * 5000;}
    double getSalary() const {return salary;}
    void Input()
    {
        cout << "Nhap ten: "; cin >> name;
        cout << "Nhap ngay sinh: "; cin >> dob;
    }

    void Output() const
    {
        cout << "Ten: " << name << endl;
        cout << "Ngay sinh: " << dob << endl;
    }
};

class Office : public Employee
{
private:
    int basicSalary, productNum;

public:
    void Input()
    {
        Employee::Input();
        cout << "Nhap luong co ban: "; RangeInput(basicSalary,0);
        cout << "Nhap so luong san pham: "; RangeInput(productNum,0);
        CalSalary(basicSalary,productNum);
    }

    void Output() const
    {
        Employee::Output();
        cout << "Luong co ban: " << basicSalary << endl;
        cout << "So luong san pham: " << productNum << endl;
        cout << "Luong: " << getSalary() << " VND" << endl;
    }
};

class Factory : public Employee
{
private:
    int workDays;

public:
    void Input()
    {
        Employee::Input();
        cout << "Nhap so ngay lam viec: "; RangeInput(workDays,0);
        CalSalary(workDays);
    }

    void Output() const
    {
        Employee::Output();
        cout << "So ngay lam viec: " << workDays << endl;
        cout << "Luong: " << getSalary() << " VND" << endl;
    }
};

class Manager
{
private:
    vector<Office> o;
    vector<Factory> f;

public:
    void Menu()
    {
        int n;
        while (true)
        {
            cout << "--------------------------------MENU----------------------------" << endl;
            cout << "1. Nhap nhan vien. " << endl;
            cout << "2. Xuat nhan vien. " << endl;
            cout << "3. Tinh tong luong. " << endl;
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
            cout << "1. Nhan vien van phong. " << endl;
            cout << "2. Nhan vien san xuat. " << endl;
            cout << "Lua chon: "; RangeInput(n,1,2);

            //Clear previous information
            if (n == 1) o.clear();
            else f.clear();

            int sl;
            cout << "So nhan vien: "; RangeInput(sl,1,10);
            for (int i = 0; i < sl; i++)
            {
                cout << "Nhan vien thu " << i+1 << "." << endl;
                // OFFICE
                if (n == 1){
                    Office temp;
                    temp.Input();
                    o.push_back(temp);
                }
                //FACTORY
                else {
                    Factory temp;
                    temp.Input();
                    f.push_back(temp);
                }
            }
            return;
        }

        //OUTPUT
        if (n == 2)
        {
            cout << "1. Nhan vien van phong. " << endl;
            cout << "2. Nhan vien san xuat. " << endl;
            cout << "Lua chon: "; RangeInput(n,1,2);
            //LAND
            if (n == 1){
                for (const auto& i : o)
                    i.Output();
            }
            else {
                for (const auto& i : f)
                    i.Output();
            }
            return;
        }

        // CALCULATE
        if (n == 3)
        {
            int sum = 0;
            for (const auto& i : o)
                sum += i.getSalary();
            for (const auto& i : f)
                sum += i.getSalary();

            cout << "Tong luong ma cong ty phai tra nhan vien: " << sum << " VND." << endl;
            return;
        }
    }
};

int main()
{
    Manager m;
    m.Menu();
}
