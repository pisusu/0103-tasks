#include "Hotel.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
using namespace std;

Hotel::Hotel() {
    nextId = 1;
    for (int i = 1; i <= 100; i++) {
        string t;
        double p;
        if (i <= 40) { t = "Standard"; p = 2500; }
        else if (i <= 70) { t = "Comfort";  p = 4000; }
        else if (i <= 90) { t = "Business"; p = 6500; }
        else { t = "Lux";      p = 12000; }
        rooms.push_back(Room(i, t, p));
    }
}

int Hotel::findRoomIndex(int number) {
    for (int i = 0; i < (int)rooms.size(); i++) {
        if (rooms[i].number == number) return i;
    }
    return -1;
}

bool Hotel::validDate(string d) {
    if (d.size() != 10) return false;
    if (d[4] != '-' || d[7] != '-') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (d[i] < '0' || d[i] > '9') return false;
    }

    int year = stoi(d.substr(0, 4));
    int month = stoi(d.substr(5, 2));
    int day = stoi(d.substr(8, 2));

    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        daysInMonth[1] = 29;
    }
    if (day > daysInMonth[month - 1]) return false;

    return true;
}

int Hotel::nights(string a, string b) {
    struct tm t1 = {}, t2 = {};
    t1.tm_year = stoi(a.substr(0, 4)) - 1900;
    t1.tm_mon = stoi(a.substr(5, 2)) - 1;
    t1.tm_mday = stoi(a.substr(8, 2));
    t2.tm_year = stoi(b.substr(0, 4)) - 1900;
    t2.tm_mon = stoi(b.substr(5, 2)) - 1;
    t2.tm_mday = stoi(b.substr(8, 2));
    time_t s1 = mktime(&t1);
    time_t s2 = mktime(&t2);
    return (int)((s2 - s1) / (60 * 60 * 24));
}

bool Hotel::roomFreeForDates(int roomNumber, string in, string out) {
    for (int i = 0; i < (int)bookings.size(); i++) {
        if (bookings[i].roomNumber != roomNumber) continue;
        if (bookings[i].overlapsWith(in, out)) return false;
    }
    return true;
}

void Hotel::showRooms() {
    cout << "\n--- Все номера ---\n";
    for (int i = 0; i < (int)rooms.size(); i++) rooms[i].print();
}

void Hotel::bookRoom() {
    int num;
    string guest, d1, d2;
    cout << "Номер комнаты: ";
    cin >> num;
    if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "Неверный номер.\n"; return; }
    cin.ignore(10000, '\n');
    cout << "ФИО гостя: ";
    getline(cin, guest);
    cout << "Дата заезда (YYYY-MM-DD): ";
    cin >> d1;
    cout << "Дата выезда (YYYY-MM-DD): ";
    cin >> d2;

    int idx = findRoomIndex(num);
    if (idx == -1) { cout << "Такого номера нет!\n"; return; }
    if (!validDate(d1) || !validDate(d2)) { cout << "Неверный формат даты!\n"; return; }
    if (d1 >= d2) { cout << "Выезд должен быть позже заезда!\n"; return; }
    if (d1 < today()) { cout << "Дата заезда раньше " << today() << " — бронь невозможна!\n"; return; }
    if (!roomFreeForDates(num, d1, d2)) { cout << "Номер занят на эти даты!\n"; return; }

    bookings.push_back(Booking(nextId, num, guest, d1, d2));
    nextId++;
    rooms[idx].busy = true;
    cout << "Бронь #" << bookings.back().id << " создана!\n";
}

void Hotel::cancelBooking() {
    int id;
    cout << "ID брони для отмены: ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Неверный ID.\n";
        return;
    }

    for (int i = 0; i < (int)bookings.size(); i++) {
        if (bookings[i].id == id && bookings[i].status == "active") {
            bookings[i].status = "cancelled";
            int idx = findRoomIndex(bookings[i].roomNumber);
            if (idx != -1) rooms[idx].busy = false;
            cout << "Бронь отменена.\n";
            return;
        }
    }
    cout << "Бронь не найдена или уже неактивна.\n";
}

void Hotel::checkInOut() {
    int id, act;
    cout << "ID брони: ";
    cin >> id;
    if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "Неверный ID.\n"; return; }

    cout << "1 - заезд, 2 - выезд: ";
    cin >> act;
    if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "Неверное действие.\n"; return; }

    for (int i = 0; i < (int)bookings.size(); i++) {
        if (bookings[i].id != id) continue;
        int idx = findRoomIndex(bookings[i].roomNumber);

        if (act == 1 && bookings[i].status == "active") {
            bookings[i].status = "checkedin";
            if (idx != -1) rooms[idx].busy = true;
            cout << "Гость заселён.\n";
            return;
        }
        if (act == 2 && bookings[i].status == "checkedin") {
            bookings[i].status = "checkedout";
            if (idx != -1) rooms[idx].busy = false;
            cout << "Гость выехал.\n";
            return;
        }
        cout << "Нельзя выполнить действие.\n";
        return;
    }
    cout << "Бронь не найдена.\n";
}

void Hotel::showForDates() {
    string d1, d2;
    cout << "Дата с (YYYY-MM-DD): ";
    cin >> d1;
    cout << "Дата по (YYYY-MM-DD): ";
    cin >> d2;
    if (!validDate(d1) || !validDate(d2) || d1 >= d2) {
        cout << "Неверные даты.\n"; return;
    }

    cout << "\n--- Свободные номера на " << d1 << " .. " << d2 << " ---\n";
    for (int i = 0; i < (int)rooms.size(); i++) {
        if (roomFreeForDates(rooms[i].number, d1, d2))
            cout << "#" << rooms[i].number << " (" << rooms[i].type << ")\n";
    }

    cout << "\n--- Брони на этот период ---\n";
    for (int i = 0; i < (int)bookings.size(); i++) {
        if (bookings[i].overlapsWith(d1, d2))
            bookings[i].print();
    }
}

void Hotel::showCost() {
    int id;
    cout << "ID брони: ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Неверный ID.\n";
        return;
    }

    for (int i = 0; i < (int)bookings.size(); i++) {
        if (bookings[i].id == id) {
            int idx = findRoomIndex(bookings[i].roomNumber);
            if (idx == -1) { cout << "Номер не найден.\n"; return; }
            int n = nights(bookings[i].checkIn, bookings[i].checkOut);
            double total = rooms[idx].price * n;
            cout << "Ночей: " << n
                << ", цена за ночь: " << rooms[idx].price
                << ", итого: " << total << " руб.\n";
            return;
        }
    }
    cout << "Бронь не найдена.\n";
}

void Hotel::showBookings() {
    if (bookings.empty()) { cout << "Броней нет.\n"; return; }
    cout << "\n--- Все брони ---\n";
    for (int i = 0; i < (int)bookings.size(); i++) bookings[i].print();
}

bool Hotel::tryAddGenerated(int roomNum, string guest, string d1, string d2) {
    if (d1 < today()) return false;
    if (!roomFreeForDates(roomNum, d1, d2)) return false;
    bookings.push_back(Booking(nextId, roomNum, guest, d1, d2));
    nextId++;
    int idx = findRoomIndex(roomNum);
    if (idx != -1) rooms[idx].busy = true;
    return true;
}

void Hotel::saveToFile(string filename) {
    ofstream f(filename);
    if (!f.is_open()) return;

    f << rooms.size() << "\n";
    for (int i = 0; i < (int)rooms.size(); i++) {
        f << rooms[i].number << " "
            << rooms[i].type << " "
            << rooms[i].price << " "
            << rooms[i].busy << "\n";
    }

    f << bookings.size() << "\n";
    for (int i = 0; i < (int)bookings.size(); i++) {
        f << bookings[i].id << " "
            << bookings[i].roomNumber << " "
            << bookings[i].checkIn << " "
            << bookings[i].checkOut << " "
            << bookings[i].status << " "
            << bookings[i].guest << "\n";
    }

    f.close();
}

void Hotel::loadFromFile(string filename) {
    ifstream f(filename);
    if (!f.is_open()) return;

    rooms.clear();
    bookings.clear();
    nextId = 1;

    int nRooms = 0;
    f >> nRooms;
    for (int i = 0; i < nRooms; i++) {
        Room r;
        f >> r.number >> r.type >> r.price >> r.busy;
        rooms.push_back(r);
    }

    int nBookings = 0;
    f >> nBookings;
    for (int i = 0; i < nBookings; i++) {
        Booking b;
        f >> b.id >> b.roomNumber >> b.checkIn >> b.checkOut >> b.status;
        f.ignore();
        getline(f, b.guest);
        bookings.push_back(b);
        if (b.id >= nextId) nextId = b.id + 1;
    }

    f.close();
}

void Hotel::deleteBooking() {
    int id;
    cout << "ID брони для удаления: ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Неверный ID.\n";
        return;
    }

   
    int index = -1;
    for (int i = 0; i < (int)bookings.size(); i++) {
        if (bookings[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Бронь с таким ID не найдена.\n";
        return;
    }

    string st = bookings[index].status;
    if (st == "active" || st == "checkedin") {
        int roomIdx = findRoomIndex(bookings[index].roomNumber);
        if (roomIdx != -1) rooms[roomIdx].busy = false;
    }

    bookings.erase(bookings.begin() + index);

    cout << "Бронь #" << id << " удалена навсегда.\n";
}

string Hotel::today() {
    return "2026-10-15";
}

void Hotel::markExpiredBookings() {
    string cutoff = today();
    int marked = 0;

    for (int i = 0; i < (int)bookings.size(); i++) {
        if (bookings[i].checkOut < cutoff &&
            (bookings[i].status == "active" || bookings[i].status == "checkedin")) {

            bookings[i].status = "expired";

            int roomIdx = findRoomIndex(bookings[i].roomNumber);
            if (roomIdx != -1) rooms[roomIdx].busy = false;
            marked++;
        }
    }

    if (marked > 0)
        cout << "Помечено как истёкшие: " << marked << "\n";
}

