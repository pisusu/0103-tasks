#include "Room.h"
using namespace std;

Room::Room() {
    number = 0;
    type = "Standard";
    price = 0;
    busy = false;
}

Room::Room(int n, string t, double p) {
    number = n;
    type = t;
    price = p;
    busy = false;
}

void Room::print() {
    string st = busy ? "занят" : "свободен";
    cout << "#" << setw(3) << number
        << "  " << setw(9) << type
        << "  " << price << " руб/ночь"
        << "  (" << st << ")\n";
}