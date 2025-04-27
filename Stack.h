#pragma once
#include <iostream>
#include "Drink.h"
using namespace std;
#define MAXSTACK 6
struct Stack
{
    Drink* value = new Drink[MAXSTACK];
    int right = -1;

    void push(Drink newDrink)
    {
        if (right < MAXSTACK - 1) {
            right++;
            value[right] = newDrink;
        }
    }

    Drink pop()
    {
        if (right > -1)
        {
            Drink drink = value[right];
            right--;
            return drink;
        }

        return Drink();
    }

    string getHSD() {
        if (right >= 0) {
            return value[right].hanSuDung;
        }
        return "00/00/0000";
    }

    string getTenNuoc() {
        if (right >= 0) {
            return value[right].tenNuoc;
        }
        return "Empty";
    }

    int GetGiaBan() {
        if (right >= 0) {
            return value[right].giaBan;
        }
        return 0;
    }

    int soLuongNuoc() {
        return right + 1;
    }
};
