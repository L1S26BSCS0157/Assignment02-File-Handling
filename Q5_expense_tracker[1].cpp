/*
 * Name       : YOUR FULL NAME
 * Reg No     : YOUR REGISTRATION NUMBER
 * Assignment : 02 - File Handling
 * Question   : Q5 - Expense Tracker
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    int choice;
    do {
        cout << "===== Expense Tracker =====" << endl;
        cout << "1. Add an expense" << endl;
        cout << "2. Show all expenses" << endl;
        cout << "3. Show total of a category" << endl;
        cout << "4. Clear all expenses" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            char category[20];
            int amount;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid amount!" << endl;
            } else {
                ofstream outFile("expenses.txt", ios::app);
                outFile << category << " " << amount << endl;
                outFile.close();
                cout << "Expense saved." << endl;
            }
        } else if (choice == 2) {
            ifstream inFile("expenses.txt");
            char category[100][20];
            int amount[100], count = 0, total = 0;
            bool largestSet = false;
            int largest = 0, largestIndex = 0;

            while (count < 100 && inFile >> category[count] >> amount[count]) {
                total += amount[count];
                if (!largestSet || amount[count] > largest) {
                    largest = amount[count];
                    largestIndex = count;
                    largestSet = true;
                }
                count++;
            }
            inFile.close();

            if (count == 0) {
                cout << "No expenses yet." << endl;
            } else {
                for (int i = 0; i < count; i++) {
                    cout << i + 1 << ". " << category[i] << " " << amount[i] << endl;
                }
                cout << "Total spent: " << total << endl;
                cout << "Largest expense: " << category[largestIndex]
                     << " (" << largest << ")" << endl;
            }
        } else if (choice == 3) {
            char wanted[20];
            cout << "Enter category: ";
            cin >> wanted;

            ifstream inFile("expenses.txt");
            char category[20];
            int amount, count = 0, total = 0;
            while (inFile >> category >> amount) {
                if (strcmp(category, wanted) == 0) {
                    count++;
                    total += amount;
                }
            }
            inFile.close();

            if (count == 0) {
                cout << "No expenses found for " << wanted << endl;
            } else {
                cout << "Expenses in " << wanted << ": " << count << endl;
                cout << "Total for " << wanted << ": " << total << endl;
            }
        } else if (choice == 4) {
            ofstream outFile("expenses.txt");
            outFile.close();
            cout << "All expenses cleared." << endl;
        } else if (choice == 5) {
            cout << "Goodbye!" << endl;
        } else {
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);

    return 0;
}
