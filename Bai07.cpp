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
class Cattle
{
private:
    int milkLt = -1;
    int childs = -1;
    string roar;

public:
    int getMilk() const {return milkLt;}
    void setMilk(const int& n) {milkLt = n;}
    void setChild(const int& n) {childs = n;}
    int getChild() {return childs;}
    string getRoar() const {return roar;}
    void setRoar(const string& str) {roar = str;}
};

class Bovine : public Cattle
{
    public:
    Bovine(){
        Cattle::setMilk(rand() % 21);
        Cattle::setChild(rand() % 6);
        Cattle::setRoar("Aye i'm a bovine.");
    }
};

class Sheep : public Cattle
{
    public:
    Sheep(){
        Cattle::setMilk(rand() % 6);
        Cattle::setChild(rand() % 6);
        Cattle::setRoar("this vexes me (A sheep).");
    }
};

class GOAT : public Cattle
{
    public:
    GOAT(){
        Cattle::setMilk(rand() % 11);
        Cattle::setChild(rand() % 6);
        Cattle::setRoar("currently playing for Real Betis. You already khow who the goat is.");
    }
};

class Manager
{
private:
    vector<Bovine> b;
    vector<Sheep> s;
    vector<GOAT> g;

public:
    void Menu()
    {
        int n;
        while (true)
        {
            cout << "--------------------------------MENU----------------------------" << endl;
            cout << "1. Nhap gia suc. " << endl;
            cout << "2. Xuat. " << endl;
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
        if (n == 1)
        {
            int sl;
            cout << "So luong bo: "; RangeInput(sl,0);
            for (int i = 0; i < sl; i++){
                Bovine temp;
                b.push_back(temp);
            }
            cout << "So luong cuu: "; RangeInput(sl,0);
            for (int i = 0; i < sl; i++){
                Sheep temp;
                s.push_back(temp);
            }
            cout << "So luong de: "; RangeInput(sl,0);
            for (int i = 0; i < sl; i++){
                GOAT temp;
                g.push_back(temp);
            }
        }
        else if (n == 2)
        {
            cout << "1. Nhung tieng keu trong nong trai." << endl;
            cout << "2. Thong ke sau 1 lua sinh. " << endl;
            cout << "Lua chon: " << endl;
            RangeInput(n,1,2);
            if (n == 1){
                if (b.size() != 0) cout << b[0].getRoar() << endl;
                if (s.size() != 0) cout << s[0].getRoar() << endl;
                if (g.size() != 0) cout << g[0].getRoar() << endl;
            }
            if (n == 2){
                int cnt = 0;
                int lt = 0;
                for (int i = 0; i < b.size(); i++){
                    cnt += b[i].getChild() + 1;
                    lt += b[i].getMilk();
                }
                cout << "Bo: " << cnt << " con. " << endl;
                cout << "Sua bo: " << lt << " lit. " << endl << endl;

                cnt = 0;
                lt = 0;
                for (int i = 0; i < s.size(); i++){
                    cnt += s[i].getChild() + 1;
                    lt += s[i].getMilk();
                }
                cout << "Cuu: " << cnt << " con. " << endl;
                cout << "Sua cuu: " << lt << " lit. " << endl << endl;

                cnt = 0;
                lt = 0;
                for (int i = 0; i < g.size(); i++){
                    cnt += g[i].getChild() + 1;
                    lt +=g[i].getMilk();
                }
                cout << "De: " << cnt << " con. " << endl;
                cout << "Sua de: " << lt << " lit. " << endl << endl;
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
