#pragma once
#include<string>
using namespace std;

struct Drink {
	string tenNuoc;
	string hanSuDung;
	int giaBan;


	Drink() {
		tenNuoc = "Empty";
		hanSuDung = "00/00/0000";
		giaBan = 00000;
	}

	Drink(string tenNuoc, string hanSudung, int giaBan) {
		this->tenNuoc = tenNuoc;
		this->hanSuDung = hanSudung;
		this->giaBan = giaBan;
	}

};
