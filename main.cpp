#include "data.h"
#include "report.h"
#include "ui.h"

#include <clocale>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
    setlocale(LC_ALL, "");

#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    fillDemoData();

    int choice;

    do {
        showMenu();
        choice = readInt("Оберіть пункт меню: ");

        switch (choice) {
        case 1:
            addTeacher();
            break;
        case 2:
            addSubject();
            break;
        case 3:
            addGroup();
            break;
        case 4:
            addWorkload();
            break;
        case 5:
            printTeachers();
            break;
        case 6:
            printSubjects();
            break;
        case 7:
            printGroups();
            break;
        case 8:
            printAllWorkloads();
            break;
        case 9:
            searchWorkloads();
            break;
        case 10:
            printTeacherSummary();
            break;
        case EXIT_CODE:
            cout << "Роботу завершено." << endl;
            break;
        default:
            cout << "Невірний пункт меню." << endl;
            break;
        }
    } while (choice != EXIT_CODE);

    return 0;
}
