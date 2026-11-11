#include <iostream>
#include <ctime>
#include <clocale>
#include "Menu.h"
#include <Windows.h>


using namespace std;

int main() {
    SetConsoleCP(65001);            // ? ввод UTF-8
    SetConsoleOutputCP(65001);      // ? вывод UTF-8

    setlocale(LC_ALL, "Russian");;
    srand((unsigned)time(0));

    Menu menu;
    menu.run();

    return 0;
}