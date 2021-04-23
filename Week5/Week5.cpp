#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <exception>
#include <iostream>
#include <algorithm>
#include <iomanip>
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
            runtime_error e("Invalid mounth : " + to_string(l.month));
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
    friend ostream& operator<<(ostream& out, const Date& l) {       // outbut type yyyy-mm-dd
        out << setw(4) << setfill('0') << l.GetYear() << '-' << setw(2) << setfill('0') << l.GetMonth() << '-' << setw(2) << setfill('0') << l.GetDay();
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
    map< Date, set<string>> data;                                   // map for sorting reason, so is set

public:

    void AddEvent(const Date& date, const string& event) {          // Add date(yyyy-mm-dd) event
        if (data.count(date) == 0)                                  // adds date and event to database
            data.insert({ date,{event} });
        else {
            data.find(date)->second.insert(event);
        }
    }

    bool DeleteEvent(const Date& date, const string& event) {       // Del date(yyyy-mm-dd) event
        if (data.count(date) != 0) {                                // Event deleted if true, Event not found if false
            if (data.find(date)->second.count(event) != 0) {
                data.find(date)->second.erase(event);
                return true;
            }
            else
                return false;
        }
    }

    int  DeleteDate(const Date& date) {                             // Del date(yyyy-mm-dd)
        if (data.count(date) != 0) {                                // get number of deleted events
            int tmp = data.at(date).size();
            data.erase(date);
            return tmp;
        }
        else return 0;
    }

    set<string> Find(const Date& date) const {                      // Find date(yyyy-mm-dd)
        if (data.count(date) != 0)                                  // get all events 
            return data.find(date)->second;                         
    }

    void Print() const {                                            //Print all dates and event 
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
        while (getline(cin, line)) {            // get a line
            if (!line.empty()) {                // if its not empty
                stringstream ss(line);          // create a stringstream
                if (ss.good()) {
                    ss >> command;              // read a command
                    if (command == "Print")
                        db.Print();
                    else {
                        ss >> date;             // read a date
                        if (ss.good())          // if stream is not empty
                            ss >> event;        // read event
                        if (command == "Find")
                            for (auto i : db.Find(date))                    // print all event on a given date
                                cout << i << endl;
                        else if (command == "Del" && event != "\0")         // if there was event delete it
                            if (db.DeleteEvent(date, event)) {
                                cout << "Deleted successfully " << endl;
                            }
                            else {
                                cout << "Event not found" << endl;
                            }
                        else if (command == "Del" && event == "\0")         // if there was only date, delete all events
                            cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
                        else if (command == "Add")                          // add a day to database
                            db.AddEvent(date, event);
                        else
                            cout << "Unnown command: " << command << endl;  // display if command was faulty
                        event = "\0";

                    }
                }
            }
        }
    }
    catch (exception& e) {          // if there was any problems, the program stops
        cout << e.what() << endl;
    }





    return 0;
}