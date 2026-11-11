#ifndef TOVAR_SROK_H
#define TOVAR_SROK_H

#include "partiya.h"

// Derived class: Product with expiration date (Task 2, variant 2)
class TovarSrok : public Partiya {
private:
    int daysLeft;   // remaining shelf life in days

public:
    TovarSrok() : Partiya(), daysLeft(0) {}

    void initExpiring(int q, const string& n, int d, int m, int y, int shelfLife) {
        cout << "[Call TovarSrok::initExpiring] shelfLife=" << shelfLife << endl;
        init(q, n, d, m, y);
        daysLeft = shelfLife;
    }

    void sell(int amount = 1) override {
        cout << "[Call TovarSrok::sell] Parameter: " << amount << endl;
        if (daysLeft <= 0) {
            cout << "  ! Error: shelf life expired, selling prohibited\n";
            return;
        }
        Partiya::sell(amount);
    }

    void newDay() {
        cout << "[Call TovarSrok::newDay]\n";
        if (daysLeft > 0) daysLeft--;
        cout << "  Days left: " << daysLeft << endl;
    }

    void printRemaining() const override {
        cout << "[Call TovarSrok::printRemaining]\n";
        cout << "  Product: " << getName()
            << " | Remaining: " << getRemaining() << " pcs."
            << " | Shelf life: " << daysLeft << " days.\n";
    }

    void printReport() const override {
        Partiya::printReport();
        cout << "  Shelf life: " << daysLeft << " days.\n";
        cout << "  ========================\n";
    }

    int getDaysLeft() const { return daysLeft; }
};

#endif