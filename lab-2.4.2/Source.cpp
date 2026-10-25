#include <iostream>
#include "Subscriber.h"
#pragma execution_character_set("utf-8")
#include <windows.h>

using namespace std;

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    {
        setlocale(LC_ALL, "uk_UA.UTF-8");
    }

    cout << "Size of Subscriber class: " << sizeof(Subscriber) << " bytes\n\n";

    Subscriber sub1("Shevchenko", 101);
    Subscriber sub2("Franko", 102);

    Book b1 = { "Author1", "C++ Basics", 2020, "Pub1", 450.50 };
    Book b2 = { "Author2", "OOP Patterns", 2021, "Pub2", 600.00 };
    Book b3 = { "Author3", "Data Structures", 2019, "Pub3", 550.00 };

    BorrowedBook bb1 = { b1, "2023-10-01", "2023-11-01", false };
    BorrowedBook bb2 = { b2, "2023-10-15", "2023-11-15", true };
    BorrowedBook bb3 = { b3, "2023-10-20", "2023-11-20", false };

    // Додавання книг
    sub1.addBook(bb1);
    sub1.addBook(bb2);

    sub2.addBook(bb2);
    sub2.addBook(bb3);

    cout << sub1 << "\n" << sub2 << "\n";

    // Тестування операцій над множинами
    Subscriber unionSub = sub1 + sub2;
    cout << "--- Union ---\n" << unionSub << "\n";

    Subscriber interSub = sub1 * sub2;
    cout << "--- Intersection ---\n" << interSub << "\n";

    Subscriber diffSub = sub1 - sub2;
    cout << "--- Difference (sub1 - sub2) ---\n" << diffSub << "\n";

    // Тестування генерації боргу
    cout << "Total Debt Price for Sub1: " << sub1.calculateDebtPrice() << " UAH\n";
    Debt sub1Debt = sub1.generateDebt();
    cout << sub1Debt;

    return 0;
}