#include "BookingGenerator.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

BookingGenerator::BookingGenerator(Hotel* h) {
    hotel = h;
    names[0] = "Иванов И.И.";
    names[1] = "Петров П.П.";
    names[2] = "Сидоров С.С.";
    names[3] = "Кузнецов А.А.";
    names[4] = "Смирнова Е.В.";
    names[5] = "Волкова М.А.";
    names[6] = "Морозов Д.С.";
    names[7] = "Новиков К.Л.";
}

void BookingGenerator::generate() {
    int n;
    cout << "Сколько броней сгенерировать? ";
    cin >> n;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Неверное число.\n";
        return;
    }

    time_t now = time(0);
    tm ltBuf;
    localtime_s(&ltBuf, &now);
    tm* lt = &ltBuf;

    int made = 0;
    for (int k = 0; k < n; k++) {
        int roomNum = rand() % 100 + 1;

        int offsetIn = rand() % 21;
        int length = rand() % 7 + 1;
        int offsetOut = offsetIn + length;

        tm t1 = *lt;
        t1.tm_mday += offsetIn;
        mktime(&t1);
        tm t2 = *lt;
        t2.tm_mday += offsetOut;
        mktime(&t2);

        char buf1[11], buf2[11];
        strftime(buf1, 11, "%Y-%m-%d", &t1);
        strftime(buf2, 11, "%Y-%m-%d", &t2);

        string d1 = buf1, d2 = buf2;
        string guest = names[rand() % 8];

        if (hotel->tryAddGenerated(roomNum, guest, d1, d2))
            made++;
    }
    cout << "Создано броней: " << made << " из " << n << "\n";
}