#pragma once
#include <string>

class Booking {
public:
    int id;
    int roomNumber;
    std::string guest;
    std::string checkIn;
    std::string checkOut;
    std::string status;

    Booking();
    Booking(int i, int rn, std::string g, std::string in, std::string out);
    bool overlapsWith(std::string in, std::string out);
    void print();
};