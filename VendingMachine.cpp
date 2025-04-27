#include <iostream>
#include <Windows.h>
#include <sstream>
#include <fstream>
#include "HashTabler.h"
using namespace std;

bool isNumber(const string str) {
    for (char const& c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int main() {
    cout << "\x1b]4;0;rgb:ff/ff/ed\x1B\x5C";
    cout << "\x1b[38;2;0;0;0m";

    ifstream file;
    HashTable maybanNuoc;

    file.open("beverage.csv");
    int precent = 20;
    for (int i = 0; i < 5; i++) {
        cout << "\x1b[3D" << "-----" << precent << "%";
        precent += 20;
        Sleep(200);
    }
    cout << "\n";
    if (!file.is_open()) {
        cout << "Khong mo duoc tep beverage.csv" << endl;
        return 0;
    }
    else {
        string line = "";
        while (getline(file, line)) {
            stringstream ss(line);
            string check;
            int count = 0;
            string luu[3] = {};
            while (getline(ss, check, ',')) {
                if (count == 0) luu[0] = check;
                if (count == 1) {
                    luu[1] = check;
                    if (luu[1][2] != '/') luu[1] = '0' + luu[1];
                    if (luu[1][5] != '/') luu[1].insert(3, "0");
                }
                if (count == 2) luu[2] = check;
                count++;
            }
            if (count >= 3) {
                Drink newDrink(luu[0], luu[1], stoi(luu[2]));
                maybanNuoc.IsCollision(newDrink);
            }
        }
    }

    while (true) {
        cout << "\x1b[1J";
        cout << "\x1b[9999999999999A";
        cout << "--------------- MAY BAN NUOC ------------------\n";
        cout << "1. Admin\n2. Khach Hang\nx . Thoat\n";
        string chon;
        cout << "Hay chon lua chon : "; cin >> chon;
        if (chon == "1") {
            cout << "\nhay nhap tai khoan : ";
            string tk;
            cin >> tk; cin.ignore();
            cout << "hay nhap mat khau : ";
            string mk;
            cin >> mk; cin.ignore();
            if (tk == "admin142" && mk == "123") {
                maybanNuoc.isAdmin = true;
                cout << "Vao quyen admin thanh cong!\n"; Sleep(1000);
                break;
            }
            else {
                cout << "tai khoan hoac mat khau khong dung !\n";
                cout << "Nhan ENTER de nhap lai!";
                cin.get();
                continue;
            }
        }
        else if (chon == "2") {
            break;
        }
        if (chon == "x") return 0;
        else {
            cout << "lua chon khong hop le !\n";
            Sleep(500);
            cout << "Nhan ENTER de nhap lai\n";
            cin.get();
        }
    }

    while (true) {
        cout << "\x1b[1J";
        cout << "\x1b[9999999999999A";
        cout << "--------------- MAY BAN NUOC------------------\n";
        maybanNuoc.Show();
        cout << "Tien trong may : " << maybanNuoc.tienThua << "\n";

        if (maybanNuoc.isAdmin) {
            ifstream file("ProfitMoney.txt");
            double tien;
            file >> tien;
            cout << "Tien loi trong may : " << tien << endl;
        }

        cout << "--------------- LUA CHON ------------------\n";
        cout << "1. Nap tien\n2. Tim nuoc \n3. Mua nuoc\n4. Sap xep theo gia tien nuoc\n";
        if (maybanNuoc.isAdmin) {
            cout << "5. Them nuoc\n6. Lay nuoc \n7. Lay tien trong may\n";
        }
        cout << "nhap x de exit !\n";
        cout << "nhap lua chon : ";
        string a;
        cin >> a;
        if (a == "1") {
            cout << "\x1b[1J";
            cout << "\x1b[9999999999999A";
            cout << "--------------- MAY BAN NUOC------------------\n";
            maybanNuoc.Show();
            cout << "Tien trong may : " << maybanNuoc.tienThua << "\n";
            if (maybanNuoc.isAdmin) {
                ifstream file("ProfitMoney.txt");
                double tien;
                file >> tien;
                cout << "Tien loi trong may : " << tien << endl;
            }
            cout << "---------------------------------\n";
            string money;
            cout << "Nhap so tien nap vao may (toi da nap duoc 999999) : "; cin >> money; cin.ignore();
            if (money[0] == '-') {
                cout << "Khong nhap tien am duoc!\nNhan ENTER de thoat";
                cin.get(); continue;
            }
            if (money.length() <= 6 and maybanNuoc.tienThua + stoi(money) <= 999999) {
                maybanNuoc.tienThua += stoi(money);
                cout << "Nap tien thanh cong!\nNhan ENTER de thoat!";
                cin.get();
            }
            else {
                cout << "Vuot qua so luong co the nap duoc hoac khong dung dinh dang!\nNhan ENTER de thoat";
                cin.get();
            }
        }
        else if (a == "2") {
            cout << "\x1b[1J";
            cout << "\x1b[9999999999999A";
            cout << "--------------- MAY BAN NUOC------------------\n";
            maybanNuoc.Show();
            cout << "Tien trong may : " << maybanNuoc.tienThua << "\n";
            if (maybanNuoc.isAdmin) {
                ifstream file("ProfitMoney.txt");
                double tien;
                file >> tien;
                cout << "Tien loi trong may : " << tien << endl;
            }
            cout << "---------------------------------\n";
            string name;
            cout << "nhap ten nuoc muon tim : "; cin >> name; cin.ignore();
            string bars = "|/-\\";
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < bars.length(); j++) {
                    cout << "\x1b[31m";
                    cout << bars[j];
                    cout << "\x1b[1D";
                    Sleep(200);
                }
            }
            cout << "\x1b[0m\n";
            cout << "\x1b[38;2;0;0;0m";
            maybanNuoc.SearchDrinkByName(name);
            cout << "Nhan ENTER de thoat!\n";
            cin.get();
        }
        else if (a == "3")
        {
            cout << "\x1b[1J";
            cout << "\x1b[9999999999999A";
            cout << "--------------- MAY BAN NUOC------------------\n";
            maybanNuoc.Show();
            cout << "Tien trong may : " << maybanNuoc.tienThua << "\n";

            if (maybanNuoc.isAdmin)
            {
                ifstream file("ProfitMoney.txt");
                double tien;
                file >> tien;
                cout << "Tien loi trong may : " << tien << endl;
            }

            cout << "---------------------------------\n";
            string ID, soLuong;
            cout << "nhap ID : "; cin >> ID; cin.ignore();
            if (isNumber(ID)) {
                cout << "nhap so luong mua : "; cin >> soLuong; cin.ignore();
                if (isNumber(soLuong)) {
                    maybanNuoc.BuyDrink(stoi(ID), stoi(soLuong), maybanNuoc.tienThua, "");
                    cout << "Nhan ENTER de thoat!"; cin.get();
                }
                else {
                    cout << "Sai dinh dang!\nNhan ENTER de tiep tuc\n";
                    cin.get();
                }
            }
            else {
                cout << "Sai dinh dang!\nNhan ENTER de tiep tuc\n"; cin.get();
                cin.get();
            }


        }
        else if (a == "4") {
            cout << "Dang tien hanh sap xep ";
            string bars = "|/-\\";
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < bars.length(); j++)
                {
                    cout << "\x1b[31m";
                    cout << bars[j];
                    cout << "\x1b[1D";
                    Sleep(200);
                }
            }
            cout << "\n";
            cout << "\x1b[38;2;0;0;0m";
            maybanNuoc.HeapSort();
            cout << "\x1b[1J";
            cout << "\x1b[9999999999999A";
            cout << "Sap xep thanh cong!\n";
            Sleep(1000);

        }
        else if (a == "5" && maybanNuoc.isAdmin) {
            cout << "\x1b[1J";  // Xóa màn hình
            cout << "\x1b[9999999999999A";  // Di chuy?n con tr? lên trên

            cout << "--------------- MAY BAN NUOC------------------\n";
            maybanNuoc.Show();

            cout << "Tien trong may : " << maybanNuoc.tienThua << "\n";

            if (maybanNuoc.isAdmin) {
                ifstream file("ProfitMoney.txt");
                if (!file) {
                    cout << "Khong the mo file Tien.txt.\n";
                }
                else {
                    double tien;
                    file >> tien;
                    cout << "Tien loi trong may : " << tien << endl;
                }
            }

            cout << "---------------------------------\n";

            string name, han;
            int gia, soLuong;
            cout << "Nhap ten nuoc muon them: ";
            cin >> name;
            cin.ignore();  // ??m b?o lo?i b? ký t? m?i dòng

            cout << "Han su dung (dd/MM/yyyy): ";
            cin >> han;
            cin.ignore();
            if (han[2] != '/') han = '0' + han;
            if (han[5] != '/') han.insert(3, "0");
            string checkNgay = han.substr(0, 2);
            string checkThang = han.substr(3, 2);

            // Ki?m tra ??nh d?ng ngày tháng
            if (stoi(checkNgay) < 1 || stoi(checkNgay) > 31 || stoi(checkThang) < 1 || stoi(checkThang) > 12) {
                cout << "Dinh dang khong hop le! \nNhan Enter de thoat!";
                cin.get();
                continue;
            }
            cout << "Gia cua san pham: ";
            cin >> gia;
            cout << "So luong: ";
            cin >> soLuong;
            maybanNuoc.AddDrink(name, han, gia, soLuong);
            cout << "Nhan ENTER de thoat!\n";
            cin.get();
            cin.ignore();
        }
        else if (a == "6" and maybanNuoc.isAdmin) {
            cout << "\x1b[1J";
            cout << "\x1b[9999999999999A";
            cout << "--------------- MAY BAN NUOC------------------\n";
            maybanNuoc.Show();
            cout << "Tien trong may : " << maybanNuoc.tienThua << "\n";

            if (maybanNuoc.isAdmin)
            {
                ifstream file("ProfitMoney.txt");
                double tien;
                file >> tien;
                cout << "Tien loi trong may : " << tien << endl;
            }

            cout << "---------------------------------\n";
            int ID, soLuong;
            cout << "nhap ID : "; cin >> ID;
            cout << "nhap so luong can lay: "; cin >> soLuong;
            maybanNuoc.BuyDrink(ID, soLuong, maybanNuoc.tienThua, "Allow");
        }
        else if (a == "7" and maybanNuoc.isAdmin)
        {
            cout << "\x1b[1J";
            cout << "\x1b[9999999999999A";
            cout << "--------------- MAY BAN NUOC------------------\n";
            maybanNuoc.Show();
            cout << "---------------------------------\n";
            maybanNuoc.EarnProfit();
        }
        else if (a == "x")
        {
            cout << "\x1b[1J";
            cout << "\x1b[9999999999999A";
            cout << "Cam on ban vi da su dung may\n";
            Sleep(1000);
            cout << "Tien thua thoi lai cho ban : " << maybanNuoc.tienThua << "\n";
            maybanNuoc.tienThua = 0;
            Sleep(1000);
            break;
        }
        else
        {
            cout << "lua chon khong hop le !\n";
            Sleep(1000);
        }

    }
    file.close();
    return 0;
}