#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h> 
using namespace std;

class Airline {
private:
    string Flight, Des, Dep;
    int Seats;

public:
    Airline(string flight, string des, string dep, int seats) {
        Flight = flight;
        Des = des;
        Dep = dep;
        Seats = seats;
    }

    string getFlight() {
        return Flight;
    }

    string getDes() {
        return Des;
    }

    string getDep() {
        return Dep;
    }

    int getSeat() {
        return Seats;
    }

    void update() {
        Seats--;
        ifstream in("D:\\flight.txt");
        ofstream out("D:\\flightTemp.txt");

        string line;
        while (getline(in, line)) {
            size_t pos = line.find(Flight);
            if (pos != string::npos) {
                int seatPos = line.find_last_of(':');
                stringstream ss;
                ss << Seats;
                string strSeats = ss.str();
                line.replace(seatPos + 2, string::npos, strSeats);
            }
            out << line << endl;
        }

        in.close();
        out.close();
        remove("D:\\flight.txt");
        rename("D:\\flightTemp.txt", "D:\\flight.txt");
        cout << "Seat reserved successfully!" << endl;
    }
};

void display() {
    ifstream in("D:\\flight.txt");
    if (!in) {
        cout << "Error: File can't be opened" << endl;
    } else {
        string line;
        while (getline(in, line)) {
            cout << line << endl;
        }
        in.close();
    }
}

int main() {
    Airline flight1("F101", "UAE", "ENGLAND", 50);
    Airline flight2("F202", "UAE", "USA", 40);
    Airline flight3("F303", "UAE", "CANADA", 20);

    ofstream out("D:\\flight.txt");
    if (!out) {
        cout << "Error: File can't open" << endl;
    } else {
        out << flight1.getFlight() << " : " << flight1.getDes() << " : " << flight1.getDep() << " : " << flight1.getSeat() << endl << endl;
        out << flight2.getFlight() << " : " << flight2.getDes() << " : " << flight2.getDep() << " : " << flight2.getSeat() << endl << endl;
        out << flight3.getFlight() << " : " << flight3.getDes() << " : " << flight3.getDep() << " : " << flight3.getSeat() << endl << endl;
        out.close();
        cout << "Data saved successfully." << endl;
    }

    bool exit = false;
    while (!exit) {
        system("cls");
        cout << "\tWelcome to Airline Management System" << endl;
        cout << "\t************************************" << endl;
        cout << "\t1. Reserve a Seat" << endl;
        cout << "\t2. Exit" << endl;
        cout << "\tEnter your choice: ";
        int val;
        cin >> val;

        if (val == 1) {
            system("cls");
            display();
            string flight;
            cout << "Enter Flight Number: ";
            cin >> flight;

            if (flight == flight1.getFlight()) {
                if (flight1.getSeat() > 0) {
                    flight1.update();
                } else {
                    cout << "Sorry, seats not available." << endl;
                }
            } else if (flight == flight2.getFlight()) {
                if (flight2.getSeat() > 0) {
                    flight2.update();
                } else {
                    cout << "Sorry, seats not available." << endl;
                }
            } else if (flight == flight3.getFlight()) {
                if (flight3.getSeat() > 0) {
                    flight3.update();
                } else {
                    cout << "Sorry, seats not available." << endl;
                }
            } else {
                cout << "Flight not found." << endl;
            }

            Sleep(3000);
        } else if (val == 2) {
            system("cls");
            cout << "Goodbye!" << endl;
            Sleep(2000);
            exit = true;
        } else {
            cout << "Invalid option!" << endl;
            Sleep(2000);
        }
    }

    return 0;
}

