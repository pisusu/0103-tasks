#pragma once
#include <string>
#include "Hotel.h"

class BookingGenerator {
private:
    std::string names[8];
    Hotel* hotel;

public:
    BookingGenerator(Hotel* h);
    void generate();
};