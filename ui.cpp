#include "ui.h"

#include <iostream>
#include <limits>

using namespace std;

int readInt(const string& message) {
    int value;

    cout << message;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input error. Try again: ";
    }

    return value;
}

string readLine(const string& message) {
    string value;

    cout << message;
    getline(cin >> ws, value);

    return value;
}

void printLine() {
    cout << string(90, '-') << endl;
}

void showMenu() {
    cout << endl;
    cout << "========== WORKLOAD DISTRIBUTION ==========" << endl;
    cout << "1. Add teacher" << endl;
    cout << "2. Add subject" << endl;
    cout << "3. Add group" << endl;
    cout << "4. Add workload record" << endl;
    cout << "5. Show teachers" << endl;
    cout << "6. Show subjects" << endl;
    cout << "7. Show groups" << endl;
    cout << "8. Show all workload records" << endl;
    cout << "9. Search" << endl;
    cout << "10. Summary report" << endl;
    cout << "0. Exit" << endl;
}
