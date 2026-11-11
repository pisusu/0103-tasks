#ifndef PARTIYA_H
#define PARTIYA_H

#include <iostream>
#include <string>
using namespace std;

// Base class: Product Batch (Task 1)
class Partiya {
private:
    int    quantity;       // quantity of goods in the batch (pieces)
    string name;           // product name
    int    day;            // delivery day
    int    month;          // delivery month
    int    year;           // delivery year
    int    sold;           // sold (pieces)
    int    writtenOff;     // written off (pieces)

public:
    Partiya() : quantity(0), name(""), day(1), month(1), year(2024),
        sold(0), writtenOff(0) {}

    void init(int q, const string& n, int d, int m, int y);

    virtual void sell(int amount = 1);
    virtual void writeOff(int amount = 1);

    int getRemaining() const;

    virtual void printRemaining() const;

    virtual void printReport() const;

    // Getters
    int    getQuantity()   const { return quantity; }
    string getName()       const { return name; }
    int    getSold()       const { return sold; }
    int    getWrittenOff() const { return writtenOff; }
    int    getDay()        const { return day; }
    int    getMonth()      const { return month; }
    int    getYear()       const { return year; }

    virtual ~Partiya() {}
};

#endif