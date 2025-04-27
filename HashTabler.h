#pragma once
#include<fstream>
#include <regex>
#include"Stack.h"
using namespace std;

#define MAX 13

struct HashTable {
	Stack drinkList[MAX];
	int tienThua = 0;
	bool isAdmin = false;

	// Hàm b?m ??n gi?n t? tên n??c u?ng
	int HashFunction(string tenNuoc) {
		int hashKey = 0;
		int i = 0;
		for (char ch : tenNuoc) {
			hashKey += (i + 1) * int(ch);
		}
		return hashKey % MAX;
	}

	void Show() {

		cout << "\x1b[34m";
		cout << "ID\tTen nuoc\tHan su dung\t\tGia ban\t\tSo luong\n";
		cout << "\x1b[0m";

		for (int i = 0; i < MAX; i++) {
			cout << "\x1b[38;2;0;0;0m";
			cout << i + 1 << "\t";
			cout << drinkList[i].getTenNuoc();
			if (drinkList[i].getTenNuoc().length() < 8)
				cout << "\t\t";
			else
				cout << "\t";

			cout << drinkList[i].getHSD() << "\t\t";
			cout << drinkList[i].GetGiaBan() << "\t\t";
			cout << drinkList[i].soLuongNuoc() << "\n";
		}
	}

	// Thêm ph?n t? vào hash table v?i ph??ng pháp gi?i quy?t xung ??t
	bool IsCollision(Drink newDrink) {
		int index = HashFunction(newDrink.tenNuoc);

		// Gi?i quy?t xung ??t b?ng cách tìm ch? tr?ng ti?p theo
		int originalIndex = index;

		do {
			string nameDrink = drinkList[index].getTenNuoc();
			int quantity = drinkList[index].soLuongNuoc();
			if (nameDrink == "Empty") {
				drinkList[index].push(newDrink);
				return true;
			}

			if (nameDrink == newDrink.tenNuoc and quantity >= MAXSTACK) {
				index = (index + 1) % MAX;
				continue;
			}
			if (nameDrink == newDrink.tenNuoc and quantity < MAXSTACK) {
				drinkList[index].push(newDrink);
				return true;
			}
			index = (index + 1) % MAX;
		} while (index != originalIndex);
		return false;

	}

	void SearchDrinkByName(string pattern) {
		// T?o regex pattern cho tên n??c
		regex drinkRegex(pattern, regex_constants::icase); // regex không phân bi?t ch? hoa/th??ng
		cout << "\x1b[1J";
		cout << "\x1b[9999999999999A";

		bool found = false;
		for (int i = 0; i < MAX; i++) {
			string drinkName = drinkList[i].getTenNuoc();

			// Ki?m tra n?u tên n??c kh?p v?i pattern
			if (regex_search(drinkName, drinkRegex) and drinkName != "Empty") {
				cout << "Tim thay: " << drinkName
					<< " - ID: " << i + 1
					<< " - Gia: " << drinkList[i].GetGiaBan()
					<< " - So luong: " << drinkList[i].soLuongNuoc()
					<< "\n";
				found = true;
			}
		}

		if (!found) {
			cout << "Khong tim thay ten nuoc phu hop voi tu khoa.\n";
		}
	}

	void BuyDrink(int ID, int soLuong, int& balance, string code) {
		if (ID - 1 >= MAX || ID - 1 < 0) {
			cout << "khong co mat hang nay!\n"; Sleep(1000);
			return;
		}
		if (soLuong > drinkList[ID - 1].soLuongNuoc()) {
			cout << "khong du san pham!\n"; Sleep(1000);
			return;
		}

		if (code == "") {
			if (soLuong * drinkList[ID - 1].GetGiaBan() > balance) {
				cout << "khong du tien\n"; Sleep(1000);
				return;
			}
		}

		double tmp = Profit();
		while (soLuong > 0) {
			drinkList[ID - 1].pop();
			soLuong--;
			if (code == "")
			{
				balance -= drinkList[ID - 1].GetGiaBan();
				tmp += drinkList[ID - 1].GetGiaBan();
			}
		}
		if (drinkList[ID - 1].soLuongNuoc() == 0)
		{
			drinkList[ID - 1].push(Drink());
			drinkList[ID - 1].pop();
		}

		if (code == "") {
			cout << "da mua hang thanh cong !\n";
		}
		else {
			cout << "lay nuoc thanh cong!\n";
		}

		SaveDataToFile(*this, "beverage.csv");
		ofstream file("ProfitMoney.txt", ios::trunc);
		file << tmp;
		Sleep(1000);
	}

	double Profit()
	{
		ifstream file("ProfitMoney.txt");
		double tmp = 0;

		if (file.fail())
		{
			cout << "Khong mo duoc tep!" << endl;
			return 0;
		}

		if (!(file >> tmp))
		{
			cout << "Khong the doc so tu tep!" << endl;
			return 0;
		}

		file.close();
		return tmp;
	}

	void SaveDataToFile(const HashTable& maybanNuoc, const string& filename) {
		ofstream file(filename, ios::trunc);

		if (file.is_open()) {
			for (int i = 0; i < MAX; i++) {
				Stack currentStack = maybanNuoc.drinkList[i];
				while (currentStack.soLuongNuoc() > 0) {
					Drink drink = currentStack.pop();
					if (drink.tenNuoc != "Empty") {
						file << drink.tenNuoc << "," << drink.hanSuDung << "," << drink.giaBan << "\n";
					}
				}
			}

		}
		else {
			cout << "Khong mo duoc tep de cap nhat sau khi mua." << endl;
		}
		file.close();
	}

	void HeapSort() {
		int n = MAX;
		int start = n - 1;
		while (start > 0) {
			start--;
			Repair(start, n);
		}
		while (n != 1) {
			n = n - 1;
			Swap(drinkList[0], drinkList[n]);
			Repair(0, n);
		}
		MoveEmptyToEnd();
	}

	void Repair(int parent, int n) {
		while (LeftChild(parent) < n) {
			int l = LeftChild(parent);
			if (l + 1 < n and drinkList[l].GetGiaBan() < drinkList[l + 1].GetGiaBan()) {
				l = l + 1;
			}
			if (drinkList[l].GetGiaBan() > drinkList[parent].GetGiaBan()) {
				Swap(drinkList[l], drinkList[parent]);
				parent = l;
			}
			else return;
		}
	}

	void Swap(Stack& doUong1, Stack& doUong2) {
		Stack temp;
		temp = doUong1;
		doUong1 = doUong2;
		doUong2 = temp;
	}

	int LeftChild(int parent) {
		return 2 * parent + 1;
	}

	void MoveEmptyToEnd() {
		int nonEmptyIndex = 0;
		for (int i = 0; i < MAX; i++) {
			if (drinkList[i].getTenNuoc() != "Empty") {
				Swap(drinkList[i], drinkList[nonEmptyIndex]);
				nonEmptyIndex++;
			}
		}
	}

	void AddDrink(string name, string Han, int gia, int soLuong)
	{
		int choConLai = 0;
		for (int i = 0; i < MAX; i++) {
			if (drinkList[i].getTenNuoc() == name or drinkList[i].getTenNuoc() == "Empty") {
				choConLai += (MAXSTACK - drinkList[i].soLuongNuoc());

			}
		}
		if (soLuong > choConLai) {
			cout << "May khong the chua het so luong them vao!\n"; Sleep(1500);
			return;
		}
		cout << "Dang them nuoc!\n"; Sleep(500);
		bool fail = false;
		ofstream file("beverage.csv", ios::app);
		if (file.is_open()) {
			Drink newDrink(name, Han, gia);
			while (soLuong > 0) {
				if (IsCollision(newDrink)) {
					file << name << "," << Han << "," << gia << "\n";
					soLuong--;
				}
				else {
					fail = true; break;
				}

			}

			if (fail) {
				cout << "Them nuoc that bai do may khong con cho trong\n"; Sleep(1000);
			}
			else cout << "\x1b[32m" << "Da them thanh cong nuoc !\n" << "\x1b[0m"; Sleep(1000);
		}

		cout << "\x1b[38;2;0;0;0m";
		file.close();
	}

	void EarnProfit()
	{
		cout << "Da lay tien ra khoi may !" << endl;
		ofstream file("ProfitMoney.txt", ios::trunc);
		file << 0;

		Sleep(1000);
		file.close();
	}
};