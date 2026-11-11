// ConsoleCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <locale.h>

 // перечисляемый тип
enum TrafficLight
{
    Red,
    Yellow,
    Green
};

int main()
{
    setlocale(LC_ALL, "Russian");
    // определение синтаксиса числа
    int n;
    std::cout << "Enter a number: ";
    std::cin >> n; // считываем целое число из стандарт потока

    bool isEven = false;
    if (n % 2 == 0)
        isEven = true;

    if (isEven)
        std::cout << n << "четное число \n";
    else
        std::cout << n << "нечетное число \n";

    return 0;

    //  константа
    const double SPEED_OF_LIGHT = 299792458.0;

    // автоопределение типа переменной
    auto PI = 3.14; // double 
    auto sqrtPI = sqrt(PI); // long double

    TrafficLight currentColor = Green;
    std::cout << currentColor << std::endl;



   
}


/*int main() {
    std::print("Hello world");
}
/*
* C++ компилируемый статически типизорованный язык
* Хорошая совместимость с С
* Поддержка разных парадигм:
*  - процедуроне программирование 
*  - ООП
*  - функциональное 
*  - обобщенное
* 
* типы данных:
*  - целые числа различных размеров со знаком и без 
*  - int short char long
*  - unsigned (int short char long)
*  - signed (int short char long)
*  - числа с плавающей запятой
*  - float double long double 
*  - bool (true, false)
* 
* числовые литералы 
*  999999L, 24234234UL (long, unsigned long)
*  - шестандцатиричные 
*  0x3274aab (ноль икс)
*  - двоичные (префикс 0b)
* 0b11100044
*  - восьмиричные (начинается с 0)
* 003
* 
* 
*/




