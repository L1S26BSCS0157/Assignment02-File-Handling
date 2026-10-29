/*
 * Name       : YOUR FULL NAME
 * Reg No     : YOUR REGISTRATION NUMBER
 * Assignment : 02 - File Handling
 * Question   : Q2 - Parking Report
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    ifstream inFile("parking.txt");
    if (!inFile) {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int d, m, y;
    char slash;
    inFile >> d >> slash >> m >> slash >> y;
    inFile.ignore(100, '\n');
    inFile.ignore(100, '\n');

    ofstream outFile("receipts.txt");
    outFile << "Receipts for " << d << "/" << m << "/" << y << endl;

    cout << "Parking report for " << d << "/" << m << "/" << y << endl;

    char plate[15], longestPlate[15] = "";
    char type;
    char inTime[6], outTime[6];
    int vehicles = 0, cars = 0, bikes = 0, totalCollected = 0;
    int longestMinutes = -1, longestHours = 0, longestRemainder = 0;

    while (vehicles < 30 && inFile >> plate >> type >> inTime >> outTime) {
        int inH = (inTime[0] - '0') * 10 + (inTime[1] - '0');
        int inM = (inTime[3] - '0') * 10 + (inTime[4] - '0');
        int outH = (outTime[0] - '0') * 10 + (outTime[1] - '0');
        int outM = (outTime[3] - '0') * 10 + (outTime[4] - '0');

        int start = inH * 60 + inM;
        int finish = outH * 60 + outM;
        int minutes = finish - start;
        int hoursCharged = (minutes + 59) / 60;
        if (hoursCharged == 0) hoursCharged = 1;

        int fee;
        if (type == 'C') {
            fee = hoursCharged * 100;
            cars++;
            cout << plate << " Car ";
        } else {
            fee = hoursCharged * 40;
            bikes++;
            cout << plate << " Bike ";
        }

        cout << minutes / 60 << " h " << minutes % 60
             << " min Fee: " << fee << endl;

        outFile << plate << " " << fee << endl;
        totalCollected += fee;
        if (minutes > longestMinutes) {
            longestMinutes = minutes;
            strcpy(longestPlate, plate);
            longestHours = minutes / 60;
            longestRemainder = minutes % 60;
        }
        vehicles++;
    }

    inFile.close();
    outFile.close();

    if (vehicles == 0) {
        cout << "No vehicles found!" << endl;
        return 0;
    }

    cout << "Vehicles: " << vehicles << endl;
    cout << "Cars: " << cars << " Bikes: " << bikes << endl;
    cout << "Total collected: " << totalCollected << endl;
    cout << "Longest stay: " << longestPlate << " (" << longestHours
         << " h " << longestRemainder << " min)" << endl;
    return 0;
}
