/*
 * Name       : YOUR FULL NAME
 * Reg No     : YOUR REGISTRATION NUMBER
 * Assignment : 02 - File Handling
 * Question   : Q3 - Scholarship List
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    char path[100];
    cout << "Enter the file name: ";
    cin.getline(path, 100);

    ifstream inFile(path);
    if (!inFile.is_open()) {
        cout << "Could not open " << path << "!" << endl;
        return 1;
    }

    int n;
    if (!(inFile >> n)) {
        inFile.close();
        cout << "No students found!" << endl;
        return 0;
    }
    if (n > 30) {
        cout << "Too many students!" << endl;
        inFile.close();
        return 0;
    }
    inFile.ignore(100, '\n');

    ofstream outFile("scholarship.txt");
    char name[30], topName[30] = "";
    int found = 0, eligible = 0;
    double cgpa, total = 0, topCgpa = -1;

    for (int i = 0; i < n; i++) {
        if (!inFile.getline(name, 30, ',')) break;
        if (!(inFile >> cgpa)) break;
        inFile.ignore(100, '\n');

        cout << "[" << name << "] CGPA: " << cgpa << endl;
        found++;
        total += cgpa;

        if (cgpa >= 3.50) {
            outFile << name << "," << cgpa << endl;
            eligible++;
        }
        if (cgpa > topCgpa) {
            topCgpa = cgpa;
            strcpy(topName, name);
        }
    }

    inFile.close();
    outFile.close();

    if (found < n) {
        cout << "Warning: only " << found << " of " << n << " records found." << endl;
    }
    if (found == 0) {
        cout << "No students found!" << endl;
        return 0;
    }

    cout << "Students: " << found << endl;
    cout << "Average CGPA: " << total / found << endl;
    cout << "Eligible for scholarship: " << eligible << endl;
    cout << "Top student: " << topName << " (" << topCgpa << ")" << endl;
    return 0;
}
