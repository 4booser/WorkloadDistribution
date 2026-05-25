#include "data.h"
#include "report.h"
#include "storage.h"
#include "ui.h"

#include <iostream>

using namespace std;

int main() {
    loadData();

    int choice;

    do {
        showMenu();
        choice = readInt("Choose menu item: ");

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
            cout << "Program finished." << endl;
            break;
        default:
            cout << "Wrong menu item." << endl;
            break;
        }
    } while (choice != EXIT_CODE);

    return 0;
}
