#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    int year;
    bool isAvailable;

public:
    Book(string t, string a, string i, int y) 
        : title(t), author(a), isbn(i), year(y), isAvailable(true) {}
    
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getIsbn() const { return isbn; }
    int getYear() const { return year; }
    bool getIsAvailable() const { return isAvailable; }
    
    void setTitle(string t) { title = t; }
    void setAuthor(string a) { author = a; }
    void setYear(int y) { year = y; }
    
    bool borrow() {
        if (isAvailable) {
            isAvailable = false;
            cout << "Книга \"" << title << "\" выдана." << endl;
            return true;
        }
        cout << "Книга \"" << title << "\" недоступна." << endl;
        return false;
    }
    
    void returnBook() {
        isAvailable = true;
        cout << "Книга \"" << title << "\" возвращена." << endl;
    }
    
    void displayInfo() const {
        cout << "\"" << title << "\" - " << author << " (" << year << ")" << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Статус: " << (isAvailable ? "Доступна" : "Выдана") << endl;
    }
};

class Library {
private:
    string name;
    string address;
    vector<Book> books;

public:
    Library(string n, string addr) : name(n), address(addr) {}
    
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Книга \"" << book.getTitle() << "\" добавлена в библиотеку." << endl;
    }
    
    bool removeBook(const string& isbn) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getIsbn() == isbn) {
                cout << "Книга \"" << it->getTitle() << "\" удалена из библиотеки." << endl;
                books.erase(it);
                return true;
            }
        }
        cout << "Книга с ISBN " << isbn << " не найдена." << endl;
        return false;
    }
    
    void findBook(const string& title) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.getTitle().find(title) != string::npos) {
                book.displayInfo();
                cout << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Книги с названием \"" << title << "\" не найдены." << endl;
        }
    }
    
    bool borrowBook(const string& isbn) {
        for (auto& book : books) {
            if (book.getIsbn() == isbn) {
                return book.borrow();
            }
        }
        cout << "Книга с ISBN " << isbn << " не найдена." << endl;
        return false;
    }
    
    bool returnBook(const string& isbn) {
        for (auto& book : books) {
            if (book.getIsbn() == isbn) {
                book.returnBook();
                return true;
            }
        }
        cout << "Книга с ISBN " << isbn << " не найдена." << endl;
        return false;
    }
    
    void displayAllBooks() const {
        cout << "=== Библиотека: " << name << " ===" << endl;
        cout << "Адрес: " << address << endl;
        cout << "Всего книг: " << books.size() << endl << endl;
        
        for (const auto& book : books) {
            book.displayInfo();
            cout << endl;
        }
    }
    
    void displayAvailableBooks() const {
        cout << "=== Доступные книги ===" << endl;
        int count = 0;
        for (const auto& book : books) {
            if (book.getIsAvailable()) {
                book.displayInfo();
                cout << endl;
                count++;
            }
        }
        cout << "Всего доступно: " << count << " книг(и)" << endl;
    }
};

int main() {
    
    Library library("Центральная библиотека", "ул. Пушкина, д. 10");
    
    cout << "=== Добавление книг ===" << endl;
    library.addBook(Book("Война и мир", "Л.Н. Толстой", "978-5-17-098342-5", 1869));
    library.addBook(Book("Преступление и наказание", "Ф.М. Достоевский", "978-5-17-098343-2", 1866));
    library.addBook(Book("Мастер и Маргарита", "М.А. Булгаков", "978-5-17-098344-9", 1967));
    library.addBook(Book("Анна Каренина", "Л.Н. Толстой", "978-5-17-098345-6", 1877));
    cout << endl;
    
    library.displayAllBooks();
    
    cout << "=== Поиск книги ===" << endl;
    library.findBook("Толстой");
    cout << endl;
    
    cout << "=== Выдача книг ===" << endl;
    library.borrowBook("978-5-17-098342-5");
    library.borrowBook("978-5-17-098344-9");
    cout << endl;
    
    library.displayAvailableBooks();
    cout << endl;
    
    cout << "=== Возврат книги ===" << endl;
    library.returnBook("978-5-17-098342-5");
    cout << endl;
    
    library.displayAvailableBooks();
    
    return 0;
}
