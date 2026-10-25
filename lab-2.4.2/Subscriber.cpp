#include "Subscriber.h"
#pragma execution_character_set("utf-8")


Debt::Debt() : count(0) {
    books = new BorrowedBook[MAX_SIZE];
}

Debt::Debt(const Debt& other) : count(other.count) {
    books = new BorrowedBook[MAX_SIZE];
    for (int i = 0; i < count; i++) books[i] = other.books[i];
}

Debt::~Debt() {
    delete[] books;
}

void Debt::addBook(const BorrowedBook& b) {
    if (count < MAX_SIZE) books[count++] = b;
}

Debt& Debt::operator=(const Debt& other) {
    if (this == &other) return *this;
    count = other.count;
    for (int i = 0; i < count; i++) books[i] = other.books[i];
    return *this;
}

Debt::operator string() const {
    stringstream ss;
    ss << "=== DEBT RECORD ===\nTotal unreturned books: " << count << "\n";
    for (int i = 0; i < count; i++) {
        ss << "- " << books[i].book.author << " \"" << books[i].book.title << "\"\n";
    }
    return ss.str();
}

ostream& operator<<(ostream& out, const Debt& d) {
    out << string(d);
    return out;
}


// --- Реалізація Subscriber ---
Subscriber::Subscriber() : lastName(""), libraryId(0), size(MAX_SIZE), count(0) {
    books = new BorrowedBook[size];
}

Subscriber::Subscriber(string name, int id) : lastName(name), libraryId(id), size(MAX_SIZE), count(0) {
    books = new BorrowedBook[size];
}

Subscriber::Subscriber(const Subscriber& other) {
    lastName = other.lastName;
    libraryId = other.libraryId;
    size = other.size;
    count = other.count;
    books = new BorrowedBook[size];
    for (int i = 0; i < count; i++) books[i] = other.books[i];
}

Subscriber::~Subscriber() {
    delete[] books;
}

string Subscriber::getLastName() const { return lastName; }
void Subscriber::setLastName(string name) { lastName = name; }
int Subscriber::getLibraryId() const { return libraryId; }
void Subscriber::setLibraryId(int id) { libraryId = id; }
int Subscriber::getSize() const { return size; }
int Subscriber::getCount() const { return count; }

void Subscriber::addBook(const BorrowedBook& b) {
    // Перевірка на унікальність
    for (int i = 0; i < count; i++) {
        if (books[i] == b) return; // Дублікати не допускаються
    }
    if (count < size) books[count++] = b;
}

bool Subscriber::removeBook(int index) {
    if (index < 0 || index >= count) return false;
    for (int i = index; i < count - 1; i++) {
        books[i] = books[i + 1];
    }
    count--;
    return true;
}

double Subscriber::calculateDebtPrice() const {
    double total = 0;
    for (int i = 0; i < count; i++) {
        if (!books[i].isReturned) total += books[i].book.price;
    }
    return total;
}

Subscriber& Subscriber::operator=(const Subscriber& other) {
    if (this == &other) return *this;
    lastName = other.lastName;
    libraryId = other.libraryId;
    count = other.count;
    for (int i = 0; i < count; i++) books[i] = other.books[i];
    return *this;
}

BorrowedBook& Subscriber::operator[](int index) {
    return books[index];
}

Subscriber::operator string() const {
    stringstream ss;
    ss << "Subscriber: " << lastName << " (ID: " << libraryId << ")\nBooks count: " << count << "\n";
    for (int i = 0; i < count; i++) {
        ss << i + 1 << ". " << books[i].book.title << " - "
            << (books[i].isReturned ? "Returned" : "Not Returned") << "\n";
    }
    return ss.str();
}

ostream& operator<<(ostream& out, const Subscriber& s) {
    out << string(s);
    return out;
}

istream& operator>>(istream& in, Subscriber& s) {
    cout << "Enter Last Name: "; in >> s.lastName;
    cout << "Enter Library ID: "; in >> s.libraryId;
    return in;
}

// Об'єднання (без дублікатів)
Subscriber operator+(const Subscriber& s1, const Subscriber& s2) {
    Subscriber result(s1.lastName + "_" + s2.lastName, 0);
    for (int i = 0; i < s1.count; i++) result.addBook(s1.books[i]);
    for (int i = 0; i < s2.count; i++) result.addBook(s2.books[i]);
    return result;
}

// Перетин (спільні елементи)
Subscriber operator*(const Subscriber& s1, const Subscriber& s2) {
    Subscriber result("Intersection", 0);
    for (int i = 0; i < s1.count; i++) {
        for (int j = 0; j < s2.count; j++) {
            if (s1.books[i] == s2.books[j]) {
                result.addBook(s1.books[i]);
                break;
            }
        }
    }
    return result;
}

// Різниця (елементи першого, яких немає в другому)
Subscriber operator-(const Subscriber& s1, const Subscriber& s2) {
    Subscriber result("Difference", 0);
    for (int i = 0; i < s1.count; i++) {
        bool found = false;
        for (int j = 0; j < s2.count; j++) {
            if (s1.books[i] == s2.books[j]) {
                found = true;
                break;
            }
        }
        if (!found) result.addBook(s1.books[i]);
    }
    return result;
}

// Генерація боргу
Debt Subscriber::generateDebt() const {
    Debt debtObj;
    for (int i = 0; i < count; i++) {
        if (!books[i].isReturned) {
            debtObj.addBook(books[i]);
        }
    }
    return debtObj;
}