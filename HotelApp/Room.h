#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class Room {
public:
    int number;
    std::string type;
    double price;
    bool busy;

    Room();
    Room(int n, std::string t, double p);
    void print();
};