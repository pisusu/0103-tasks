#include "Menu.h"
#include <iostream>
using namespace std;

Menu::Menu() : generator(&hotel) {
    hotel.loadFromFile("hotel_data.txt");
    hotel.markExpiredBookings();
}

void Menu::show() {
    cout << "\n===== ОТЕЛЬ =====\n"
        << "1. Показать все номера\n"
        << "2. Забронировать номер\n"
        << "3. Отменить бронь\n"
        << "4. Заезд / выезд\n"
        << "5. Свободные номера и брони на даты\n"
        << "6. Стоимость проживания\n"
        << "7. Сгенерировать тестовые брони\n"
        << "8. Показать все брони\n"
        << "9. Удалить бронь навсегда\n"
        << "0. Выход\n"
        << "Выбор: ";
}

void Menu::run() {
    int choice;
    while (true) {
        show();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Неверный ввод. Введите число.\n";
            continue;
        }

        if (choice == 0) {
            hotel.saveToFile("hotel_data.txt");
            break;
        }
        else if (choice == 1) hotel.showRooms();
        else if (choice == 2) hotel.bookRoom();
        else if (choice == 3) hotel.cancelBooking();
        else if (choice == 4) hotel.checkInOut();
        else if (choice == 5) hotel.showForDates();
        else if (choice == 6) hotel.showCost();
        else if (choice == 7) generator.generate();
        else if (choice == 8) hotel.showBookings();
        else if (choice == 9) hotel.deleteBooking();     
        else cout << "Нет такого пункта.\n";
    }
}