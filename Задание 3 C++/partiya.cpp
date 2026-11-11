#include "partiya.h"

void Partiya::init(int q, const string& n, int d, int m, int y) {
    cout << "[Call Partiya::init] Parameters: quantity=" << q
        << ", name=" << n
        << ", date=" << d << "." << m << "." << y << endl;

    quantity = q;
    name = n;
    day = d;
    month = m;
    year = y;
    sold = 0;
    writtenOff = 0;
}

void Partiya::sell(int amount) {
    cout << "[Call Partiya::sell] Parameter: " << amount << endl;
    if (amount <= 0) {
        cout << "  ! Error: amount must be positive\n";
        return;
    }
    if (amount > getRemaining()) {
        cout << "  ! Error: not enough goods (remaining "
            << getRemaining() << ")\n";
        return;
    }
    sold += amount;
}

void Partiya::writeOff(int amount) {
    cout << "[Call Partiya::writeOff] Parameter: " << amount << endl;
    if (amount <= 0) {
        cout << "  ! Error: amount must be positive\n";
        return;
    }
    if (amount > getRemaining()) {
        cout << "  ! Error: not enough goods (remaining "
            << getRemaining() << ")\n";
        return;
    }
    writtenOff += amount;
}

int Partiya::getRemaining() const {
    return quantity - sold - writtenOff;
}

void Partiya::printRemaining() const {
    cout << "[Call Partiya::printRemaining]\n";
    cout << "  Product: " << name
        << " | Remaining: " << getRemaining() << " pcs.\n";
}

void Partiya::printReport() const {
    cout << "[Call Partiya::printReport]\n";
    cout << "  ===== FULL REPORT =====\n";
    cout << "  Name         : " << name << "\n";
    cout << "  Delivery date: " << day << "." << month << "." << year << "\n";
    cout << "  Total in batch: " << quantity << " pcs.\n";
    cout << "  Sold         : " << sold << " pcs.\n";
    cout << "  Written off  : " << writtenOff << " pcs.\n";
    cout << "  Remaining    : " << getRemaining() << " pcs.\n";
}