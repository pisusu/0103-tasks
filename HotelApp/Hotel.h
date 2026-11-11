#pragma once
#include <vector>
#include <string>
#include "Room.h"
#include "Booking.h"

class Hotel {
private:
    std::vector<Room> rooms;
    std::vector<Booking> bookings;
    int nextId;

public:
    Hotel();

    int findRoomIndex(int number);
    bool validDate(std::string d);
    int nights(std::string a, std::string b);
    bool roomFreeForDates(int roomNumber, std::string in, std::string out);

    void showRooms();
    void bookRoom();
    void cancelBooking();
    void deleteBooking();
    void checkInOut();
    void showForDates();
    void showCost();
    void showBookings();

    std::string today();
    void markExpiredBookings();

    bool tryAddGenerated(int roomNum, std::string guest,
        std::string d1, std::string d2);

    void saveToFile(std::string filename);
    void loadFromFile(std::string filename);
};

