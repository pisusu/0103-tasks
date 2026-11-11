#pragma once
#include "Hotel.h"
#include "BookingGenerator.h"

class Menu {
private:
    Hotel hotel;
    BookingGenerator generator;

public:
    Menu();
    void show();
    void run();
};