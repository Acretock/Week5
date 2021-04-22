#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <exception>
#include <iostream>
#include <algorithm>

using namespace std;

// –еализуйте функции и методы классов и при необходимости добавьте свои
class Date {
private:
    int year;
    int month;
    int day;

public:
    int GetYear() const {}
    int GetMonth() const {}
    int GetDay() const {}
};

bool operator<(const Date& lhs, const Date& rhs);

class Database {
private:
    map< Date, set<string>> data;

public:
    void AddEvent(const Date& date, const string& event) {

    }

    bool DeleteEvent(const Date& date, const string& event) {

    }

    int  DeleteDate(const Date& date) {

    }

    set<string> Find(const Date& date) const {

    }

    void Print() const {

    }
};

int main() {
    Database db;

    string command;
    while (getline(cin, command)) {
        // —читайте команды с потока ввода и обработайте каждую
    }

    return 0;
}