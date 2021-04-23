#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <exception>
#include <iostream>
#include <algorithm>

using namespace std;


class Date {
private:
    int year;
    int month;
    int day;

public:
    int GetYear() const     { return year; }
    int GetMonth() const    { return month; }
    int GetDay() const      { return day; }
    friend istream& operator>>(istream& in, Date& l) {
        in >> l.year;
        in.ignore(1);
        in >> l.month;
        if (l.month > 12 || l.month < 1) {
            runtime_error e("Invalid day : " + to_string(l.month));
            throw (e);
        }
        in.ignore(1);
        in >> l.day;
        if (l.day > 31 || l.day < 1) {
            runtime_error e("Invalid day : " + to_string(l.day));
            throw e;
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, const Date& l) {
        out << l.GetYear() << '-' << l.GetMonth() << '-' << l.GetDay();
        return out;
    }
    bool operator<(const Date& r) const {
        if (this->year < r.year)
            return true;
        else if (this->month < r.month)
            return true;
        else if (this->day < r.day)
            return true;
        else return false;
    }
};



class Database {
private:
    map< Date, set<string>> data;

public:

    void AddEvent(const Date& date, const string& event) {
        if (data.count(date) == 0)
            data.insert({ date,{event} });
        else {
            data.find(date)->second.insert(event);
        }
    }

    bool DeleteEvent(const Date& date, const string& event) {
        if (data.count(date) != 0) {
            if (data.find(date)->second.count(event) != 0) {
                data.find(date)->second.erase(event);
                return true;
            }
            else
                return false;
        }
    }

    int  DeleteDate(const Date& date) {
        int tmp = data.at(date).size();
        data.erase(date);
        return tmp;
    }

    set<string> Find(const Date& date) const {
        if (data.count(date) != 0)
            return data.find(date)->second;
    }

    void Print() const {
        for (auto i : data) {
            for (auto j : i.second)
                cout << i.first << ' ' << j << endl;
        }
    }
};

int main() {
    Database db;

    string line,command,event;
    Date date;
    try {
        while (getline(cin, line)) {
            stringstream ss(line);
            line = "\0";
            if (ss.good()) {
                ss >> command;
                
                    if (command == "Print")
                        db.Print();
                    else {
                        ss >> date;
                        if (ss.good())
                            ss >> event;
                        if (command == "Find")
                            for (auto i : db.Find(date))
                                cout << i << endl;
                        else if (command == "Del" && event != "\0")          //if there was event
                            if (db.DeleteEvent(date, event)) {
                                cout << "Deleted successfully " << endl;
                            }
                            else {
                                cout << "Event not found" << endl;
                            }
                        else if (command == "Del" && event == "\0")     //if there was only date
                            cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
                        else if (command == "Add")
                            db.AddEvent(date, event);
                        else
                            cout << "Unnown command: " << command << endl;
                    }
                }
            }
        
    }
    catch (exception& e) {
        cout << e.what() << endl;
    }





    return 0;
}