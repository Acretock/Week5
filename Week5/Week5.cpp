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
    int GetYear() const     { return year; }
    int GetMonth() const    { return month; }
    int GetDay() const      { return day; }
};

bool operator<(const Date& l, const Date& r) {
    if (l.GetYear() < r.GetDay())
        return l.GetYear() < r.GetDay();
    if (l.GetMonth() < r.GetMonth())
        return l.GetMonth() < r.GetMonth();
    if (l.GetDay() < r.GetDay())
        return l.GetDay() < r.GetDay();
}

class Database {
private:
    map< set<Date>, set<string>> data;

public:
    void AddEvent(const Date& date, const string& event) {
        if (data.find({date}) == end(data))
            data.insert({ {date},{event} });
        else {
            data.find({ date })->second.insert(event);
        }
    }

    bool DeleteEvent(const Date& date, const string& event) {
        data.find({ date })->second.erase(event);
    }

    int  DeleteDate(const Date& date) {
        data.erase({ date });
    }

    set<string> Find(const Date& date) const {
        if (data.find({ date }) != end(data))
            return data.find({ date })->second;
    }

    void Print() const {
        for (auto i : data)
            ;
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