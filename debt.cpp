#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdarg.h>
#include <algorithm>

using namespace std;

#define f1c(val) cout << val << "\n";

fstream file;

class price
{
private:
    int index;
    string name, getDate, detail;
    float money;
    bool tick;

public:
    price(){};
    price(const price &p1);
    void get(int index, string name, string getDate, float money, bool tick, string detail);
    int getID();
    string getName();
    string Date();
    float getMoney();
    bool getTick();
    string getDetail();
    void setID(int);
    void setName(string);
    void setDate(string);
    void setMoney(float);
    void setTick(bool);
    void setDetail(string);
    void print();
    bool operator<(const price &p) const
    {
        return (money < p.money);
    }
};

void price::get(int index, string name, string getDate, float money, bool tick, string detail)
{
    this->index = index;
    this->name = name;
    this->getDate = getDate;
    this->money = money;
    this->tick = tick;
    this->detail = detail;
}

void price::print()
{
    cout << index << " : " << name << " | " << money << " | " << getDate << " | ";
    if (tick)
        cout << "✅";
    else
        cout << "❌";
    cout << " | " << detail;
    cout << endl;
    cout << "-----------------------------------------------------------------";
    cout << endl;
}

int price::getID()
{
    return index;
}
string price::getName()
{
    return name;
}

string price::Date()
{
    return getDate;
}

float price::getMoney()
{
    return money;
}

bool price::getTick()
{
    return tick;
}

string price::getDetail()
{
    return detail;
}

void price::setID(int x)
{
    index = x;
}

void price::setName(string x)
{
    name = x;
}

void price::setDate(string x)
{
    getDate = x;
}

void price::setMoney(float x)
{
    money = x;
}

void price::setTick(bool x)
{
    tick = x;
}

void price::setDetail(string x)
{
    detail = x;
}

price::price(const price &p1)
{
    this->index = p1.index;
    this->name = p1.name;
    this->getDate = p1.getDate;
    this->money = p1.money;
    this->tick = p1.tick;
    this->detail = p1.detail;
}

vector<string> menuStr;

void menuFunc(int count, ...)
{
    va_list args;
    va_start(args, count);
    string temp;
    for (int i = 0; i < count; i++)
    {
        temp = va_arg(args, char *);
        menuStr.push_back(temp);
    }
    va_end(args);
}

void showMenu()
{
    f1c("Menu : ");
    for (int i = 0; i < menuStr.size(); i++)
        cout << '\t' << menuStr[i] << " = " << i << endl;
}

void fileUpdate(string fileName, vector<price> vec)
{
    file.open(fileName.c_str(), ios::out);
    if (file.fail())
    {
        cout << "db.txt file was not created." << endl;
        return;
    }
    for (int i = 0; i < vec.size(); i++)
        file << vec[i].getID() << " " << vec[i].getName() << " "
             << vec[i].getMoney() << " " << vec[i].Date() << " " << vec[i].getTick() << " " << vec[i].getDetail() << endl;
    file.close();
}

int main()
{
    cout.precision(20);
    system("copy db.txt backUp.txt");
    string fileName = "db.txt";
    file.open(fileName.c_str(), ios::in);
    if (file.fail())
    {
        cout << "db.txt file was not created." << endl;
        return 0;
    }
    vector<price> vec;
    int index;
    string name, getDate, detail;
    float money;
    bool tick;
    price temp;
    string strTemp;
    while (file >> strTemp)
    {
        index = stoi(strTemp);
        file >> strTemp;
        name = strTemp;
        file >> strTemp;
        money = stof(strTemp);
        file >> strTemp;
        getDate = strTemp;
        file >> strTemp;
        tick = stoi(strTemp);
        file >> strTemp;
        detail = strTemp;
        temp.get(index, name, getDate, money, tick, detail);
        vec.push_back(temp);
    }
    file.close();
    menuFunc(10, "Add", "Edit", "ShowAll", "showTicked", "showNotTicked", "Exit", "Total", "Delete", "Search", "Profit");
    while (1)
    {
        showMenu();
        cout << endl;
        int choice;
        cin >> choice;
        if (choice == 5)
        {
            fileUpdate(fileName, vec);
            break;
        }
        else if (choice == 0)
        {
            index = vec.size();
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter money: ";
            cin >> money;
            cout << "Enter get date: ";
            cin >> getDate;
            tick = false;
            cout << "Enter get detail: ";
            cin >> detail;
            temp.get(index, name, getDate, money, tick, detail);
            vec.push_back(temp);
            sort(vec.begin(), vec.end());
            fileUpdate(fileName, vec);
        }
        else if (choice == 1)
        {
            cout << "Enter ID: ";
            cin >> index;
            int B = 0;
            for (int i = 0; i < vec.size(); i++)
                if (index == vec[i].getID())
                {
                    vec[i].print();
                    B = 1;
                    index = vec[i].getID();
                    int editOption;
                    cout << "Enter number to edit: " << endl
                         << "0 -> cancel" << endl
                         << "1 -> name" << endl
                         << "2 -> money" << endl
                         << "3 -> date" << endl
                         << "4 -> tick" << endl
                         << "5 -> detail" << endl;
                    cin >> editOption;
                    if (editOption == 0)
                        break;
                    else if (editOption == 1)
                    {
                        cout << "Enter new name: ";
                        cin >> name;
                        vec[i].setName(name);
                    }
                    else if (editOption == 2)
                    {
                        cout << "Enter new money: ";
                        cin >> money;
                        vec[i].setMoney(money);
                    }
                    else if (editOption == 3)
                    {
                        cout << "Enter new get date: ";
                        cin >> getDate;
                        vec[i].setDate(getDate);
                    }
                    else if (editOption == 4)
                    {
                        cout << "Enter new tick (0/1): ";
                        cin >> tick;
                        vec[i].setTick(tick);
                    }
                    else if (editOption == 5)
                    {
                        cout << "Enter new detail: ";
                        cin >> detail;
                        vec[i].setDetail(detail);
                    }
                    else
                    {
                        cout << "Invalid cmd." << endl
                             << endl;
                        break;
                    }
                    sort(vec.begin(), vec.end());
                    cout << "Done." << endl
                         << endl;
                    fileUpdate(fileName, vec);
                    break;
                }
            if (!B)
                cout << "Not found!" << endl;
        }
        else if (choice == 2)
            for (int i = 0; i < vec.size(); i++)
                vec[i].print();
        else if (choice == 3)
            for (int i = 0; i < vec.size(); i++)
            {
                if (vec[i].getTick())
                    vec[i].print();
            }
        else if (choice == 4)
            for (int i = 0; i < vec.size(); i++)
            {
                if (!vec[i].getTick())
                    vec[i].print();
            }
        else if (choice == 6)
        {
            int totalIdx, total = 0;
            cout << "\tTotalAll = 0" << endl
                 << "\tTotalTicked = 1" << endl
                 << "\tTotalNotTicked = 2" << endl;
            cin >> totalIdx;
            if (totalIdx == 0)
            {
                for (int i = 0; i < vec.size(); i++)
                    if (vec[i].getMoney() > 0)
                        total += vec[i].getMoney();
            }
            else if (totalIdx == 1)
            {
                for (int i = 0; i < vec.size(); i++)
                    if (vec[i].getTick())
                        if (vec[i].getMoney() > 0)
                            total += vec[i].getMoney();
            }
            else if (totalIdx == 2)
            {
                for (int i = 0; i < vec.size(); i++)
                    if (!vec[i].getTick())
                        if (vec[i].getMoney() > 0)
                            total += vec[i].getMoney();
            }
            else
            {
                cout << "Invalid num" << endl;
                continue;
            }
            cout << "\tTotal: " << total << endl;
        }
        else if (choice == 7)
        {
            cout << "Enter ID: ";
            cin >> index;
            int B = 0;
            for (int i = 0; i < vec.size(); i++)
                if (index == vec[i].getID())
                {
                    B = 1;
                    vec[i].print();
                    int deleteOption; // for cancel
                    cout << "0 -> cancel" << endl
                         << "1 -> continue" << endl;
                    cin >> deleteOption;
                    if (deleteOption == 0)
                        break;
                    vec.erase(vec.begin() + i); // delete object
                    fileUpdate(fileName, vec);
                    cout << "Done." << endl;
                    break;
                }
            if (!B)
                cout << "Not found!" << endl;
        }
        else if (choice == 8)
        {
            cout << "Enter name for search: ";
            cin >> name;
            int B = 0;
            for (int i = 0; i < vec.size(); i++)
                if (name == vec[i].getName())
                {
                    B = 1;
                    vec[i].print();
                }
            if (!B)
                cout << "Not found!" << endl;
        }
        else if (choice == 9)
        {
            cout << "Enter ID: ";
            cin >> index;
            int B = 0;
            for (int i = 0; i < vec.size(); i++)
                if (index == vec[i].getID())
                {
                    B = 1;
                    vec[i].print();
                    float tavarom = 40.2 / (365 * 100); // Tavarom Roozane
                    float payment = vec[i].getMoney();
                    cout << "Enter days: ";
                    float days;
                    cin >> days;
                    payment += payment * tavarom * days; // result
                    cout << "result: " << payment << endl
                         << endl;
                    break;
                }
            if (!B)
                cout << "Not found!" << endl;
        }
        else
            cout << "Invalid cmd. try again..." << endl;
    }
    return 0;
}