#include "Booking.h"
#include <iostream>
using namespace std;

Booking::Booking() {
    id = 0;
    roomNumber = 0;
    status = "active";
}

Booking::Booking(int i, int rn, string g, string in, string out) {
    id = i;
    roomNumber = rn;
    guest = g;
    checkIn = in;
    checkOut = out;
    status = "active";
}

bool Booking::overlapsWith(string in, string out) {
    if (status == "cancelled") return false;
    if (status == "checkedout") return false;
    if (status == "expired") return false;
    return checkIn < out && in < checkOut;
}

void Booking::print() {
    cout << "#" << id
        << "  номер " << roomNumber
        << "  " << guest
        << "  " << checkIn << " -> " << checkOut
        << "  (" << status << ")\n";
}