#include "data.h"
#include "report.h"
#include "storage.h"
#include "ui.h"

#include <clocale>
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
    setlocale(LC_ALL, "");

#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    system("chcp 65001 > nul");
#endif

    loadData();

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
            saveData();
            cout << "Роботу завершено." << endl;
            break;
        default:
            cout << "Невірний пункт меню." << endl;
            break;
        }
    } while (choice != EXIT_CODE);

    return 0;
}
