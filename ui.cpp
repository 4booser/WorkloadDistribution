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
        cout << "Помилка введення. Повторіть: ";
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
    cout << "========== РОЗПОДІЛ УЧБОВОГО НАВАНТАЖЕННЯ ==========" << endl;
    cout << "1. Додати викладача" << endl;
    cout << "2. Додати дисципліну" << endl;
    cout << "3. Додати групу" << endl;
    cout << "4. Додати запис навантаження" << endl;
    cout << "5. Переглянути викладачів" << endl;
    cout << "6. Переглянути дисципліни" << endl;
    cout << "7. Переглянути групи" << endl;
    cout << "8. Переглянути всі записи навантаження" << endl;
    cout << "9. Пошук" << endl;
    cout << "10. Підсумковий звіт" << endl;
    cout << "0. Вихід" << endl;
}
