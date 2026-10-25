#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Інформаційний запис про книгу
struct Book {
    string author;
    string title;
    int year;
    string publisher;
    double price;

    bool operator==(const Book& other) const {
        return author == other.author && title == other.title && year == other.year;
    }
};

// Запис про взяту книгу
struct BorrowedBook {
    Book book;
    string issueDate;
    string returnDate;
    bool isReturned;

    bool operator==(const BorrowedBook& other) const {
        return book == other.book && issueDate == other.issueDate;
    }
};

class Debt; // Попереднє оголошення класу Debt

class Subscriber {
private:
    string lastName;
    int libraryId;
    static const int MAX_SIZE = 100;
    int size;
    int count;
    BorrowedBook* books;

public:
    // Конструктори та деструктор
    Subscriber();
    Subscriber(string name, int id);
    Subscriber(const Subscriber& other);
    ~Subscriber();

    // Методи доступу
    string getLastName() const;
    void setLastName(string name);
    int getLibraryId() const;
    void setLibraryId(int id);
    int getSize() const;
    int getCount() const;

    // Основні методи
    void addBook(const BorrowedBook& b);
    bool removeBook(int index);

    // Методи пошуку
    Subscriber findToReturn() const;
    Subscriber searchByAuthor(const string& author) const;
    Subscriber searchByPublisher(const string& publisher) const;
    Subscriber searchByYear(int year) const;
    double calculateDebtPrice() const;

    // Перевантаження операцій
    Subscriber& operator=(const Subscriber& other);
    BorrowedBook& operator[](int index);
    operator string() const;

    // Операції над множинами (дружні функції)
    friend Subscriber operator+(const Subscriber& s1, const Subscriber& s2); // Об'єднання
    friend Subscriber operator*(const Subscriber& s1, const Subscriber& s2); // Перетин
    friend Subscriber operator-(const Subscriber& s1, const Subscriber& s2); // Різниця

    // Потокові операції
    friend ostream& operator<<(ostream& out, const Subscriber& s);
    friend istream& operator>>(istream& in, Subscriber& s);

    // Генерація боргу
    Debt generateDebt() const;
};

class Debt {
private:
    static const int MAX_SIZE = 100;
    int count;
    BorrowedBook* books;

public:
    Debt();
    Debt(const Debt& other);
    ~Debt();

    void addBook(const BorrowedBook& b);
    Debt& operator=(const Debt& other);
    operator string() const;
    friend ostream& operator<<(ostream& out, const Debt& d);
};