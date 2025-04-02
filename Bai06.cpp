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

class SV
{
private:
    string id, name, address;
    int tc;
    double average;
    bool hasGrad;
public:
    int getTC() const {return tc;}
    double getAverage() const {return average;}
    void setGrad(const bool& b) {hasGrad = b;}
    bool getGrad() const {return hasGrad;}
    void Input()
    {
        cout << "Nhap id: "; cin >> id;
        cout << "Nhap ten: "; cin >> name;
        cout << "Nhap dia chi: "; cin >> address;
        cout << "Nhap so tin chi: "; RangeInput(tc,1);
        cout << "Nhap diem TB: "; RangeInput(average,0,10);
    }

    void Output() const
    {
        cout << "ID: " << id << endl;
        cout << "Ten: " << name << endl;
        cout << "Dia chi: " << address << endl;
        cout << "So tin chi: " << tc << endl;
        cout << "Diem TB: " << average << endl;
    }

    string GradStatus() const
    {
        if (hasGrad) return "du dieu kien tot nghiep. ";
        return "chua du dieu kien tot nghiep.";
    }
};

class College : public SV
{
private:
    double TTN;

public:
    void Input()
    {
        SV::Input();
        cout << "Nhap diem thi tot nghiep: "; RangeInput(TTN,0,10);
        setGrad(getTC() >= 110 && getAverage() >= 5 && TTN >= 5);
    }

    void Output() const
    {
        SV::Output();
        cout << "Diem thi tot nghiep: " << TTN << endl;
        cout << "Tinh trang: " << GradStatus() << endl;
    }
};

class Uni : public SV
{
private:
    string LVname;
    double LVgrade;

public:
    void Input()
    {
        SV::Input();
        cout << "Nhap ten luan van: "; cin >> LVname;
        cout << "Nhap diem luan van: "; RangeInput(LVgrade,0,10);
        setGrad(getTC() >= 145 && getAverage() >= 5 && LVgrade >= 5);
    }

    void Output() const
    {
        SV::Output();
        cout << "Ten luan van: " << LVname << endl;
        cout << "Diem luan van: " << LVgrade << endl;
        cout << "Tinh trang: " << GradStatus() << endl;
    }
};

class Manager
{
private:
    vector<College> c;
    vector<Uni> u;
public:
    void Menu()
    {
        int n;
        while (true)
        {
            cout << "--------------------------------MENU----------------------------" << endl;
            cout << "1. Nhap sinh vien. " << endl;
            cout << "2. Xuat sinh vien. " << endl;
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
        // INPUT
        if (n == 1)
        {
            cout << "1. Sinh vien cao dang. " << endl;
            cout << "2. Sinh vien dai hoc. " << endl;
            cout << "Lua chon: "; RangeInput(n,1,2);

            //Clear previous information
            if (n == 1) c.clear();
            else u.clear();

            int sl;
            cout << "So sinh vien: "; RangeInput(sl,1,10);
            for (int i = 0; i < sl; i++)
            {
                cout << "Sinh vien thu " << i+1 << "." << endl;
                // COLLEGE
                if (n == 1){
                    College temp;
                    temp.Input();
                    c.push_back(temp);
                }
                else {
                    Uni temp;
                    temp.Input();
                    u.push_back(temp);
                }
            }
            return;
        }

        //OUTPUT
        if (n == 2)
        {
            cout << "1. Sinh vien cao dang. " << endl;
            cout << "2. Sinh vien dai hoc. " << endl;
            cout << "3. Sinh vien du dieu kien tot nghiep. " << endl;
            cout << "4. Sinh vien khong du dieu kien tot nghiep. " << endl;
            cout << "5. Sinh vien dai hoc co diem trung binh cao nhat. " << endl;
            cout << "Lua chon: "; RangeInput(n,1,5);

            if (n == 1){
                cout << "Danh sach sinh vien cao dang: " << endl;
                for (const auto& i : c) {
                    i.Output();
                    cout << endl;
                }
            }
            else if (n == 2){
                cout << "Danh sach sinh vien dai hoc: " << endl;
                for (const auto& i : u) {
                    i.Output();
                    cout << endl;
                }
            }
            else if (n == 3){
                cout << "Danh sach sinh vien du dieu kien tot nghiep: " << endl;
                for (const auto& i : c) {
                    if (i.getGrad()){
                        i.Output();
                        cout << endl;
                    }
                }
                for (const auto& i : u) {
                    if (i.getGrad()){
                        i.Output();
                        cout << endl;
                    }
                }
            }
            else if (n == 4){
                cout << "Danh sach sinh vien chua du dieu kien tot nghiep: " << endl;
                for (const auto& i : c) {
                    if (!i.getGrad()){
                        i.Output();
                        cout << endl;
                    }
                }
                for (const auto& i : u) {
                    if (!i.getGrad()){
                        i.Output();
                        cout << endl;
                    }
                }
            }
            else {
                cout << "Sinh vien dai hoc co DTB cao nhat: " << endl;
                if (u.size() == 0) {
                    cout << "Khong co sinh vien nao. " << endl;
                    return;
                }
                Uni temp = u[0];
                for (int i = 1; i < u.size(); i++){
                    if (temp.getAverage() < u[i].getAverage()){
                        temp = u[i];
                    }
                }
                temp.Output();
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
