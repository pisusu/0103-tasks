#ifndef PARTIYA_CHECKED_H
#define PARTIYA_CHECKED_H

#include "tovar_srok.h"

// Derived class with checks (Task 3)
class PartiyaChecked : public TovarSrok {
public:
    void initChecked(int q, const string& n, int d, int m, int y, int shelfLife) {
        cout << "[Call PartiyaChecked::initChecked]\n";
        if (q < 0) { cout << "  ! Error: negative quantity\n"; return; }
        if (shelfLife < 0) { cout << "  ! Error: negative shelf life\n"; return; }
        initExpiring(q, n, d, m, y, shelfLife);
    }

    void sell(int amount = 1) override {
        cout << "[Call PartiyaChecked::sell] Parameter: " << amount << endl;
        if (amount <= 0) {
            cout << "  ! Error: amount must be > 0\n";
            return;
        }
        if (amount > getRemaining()) {
            cout << "  ! Error: selling more than remaining ("
                << getRemaining() << ")\n";
            return;
        }
        if (getDaysLeft() <= 0) {
            cout << "  ! Error: shelf life expired\n";
            return;
        }
        Partiya::sell(amount);
    }

    void writeOff(int amount = 1) override {
        cout << "[Call PartiyaChecked::writeOff] Parameter: " << amount << endl;
        if (amount <= 0) {
            cout << "  ! Error: amount must be > 0\n";
            return;
        }
        if (amount > getRemaining()) {
            cout << "  ! Error: writing off more than remaining ("
                << getRemaining() << ")\n";
            return;
        }
        Partiya::writeOff(amount);
    }
};

#endif