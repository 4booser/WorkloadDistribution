#include "report.h"
#include "data.h"
#include "ui.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void printTeachers() {
    printLine();
    cout << left << setw(5) << "ID"
         << setw(32) << "ПІБ"
         << setw(25) << "Підрозділ"
         << setw(10) << "Норма"
         << setw(10) << "Факт" << endl;
    printLine();

    for (const Teacher& teacher : teachers) {
        cout << left << setw(5) << teacher.id
             << setw(32) << teacher.fullName
             << setw(25) << teacher.department
             << setw(10) << teacher.maxHours
             << setw(10) << calculateTeacherHours(teacher.id) << endl;
    }
}

void printSubjects() {
    printLine();
    cout << left << setw(5) << "ID"
         << setw(35) << "Дисципліна"
         << setw(12) << "Семестр"
         << setw(10) << "Години" << endl;
    printLine();

    for (const Subject& subject : subjects) {
        cout << left << setw(5) << subject.id
             << setw(35) << subject.name
             << setw(12) << subject.semester
             << setw(10) << subject.planHours << endl;
    }
}

void printGroups() {
    printLine();
    cout << left << setw(5) << "ID"
         << setw(15) << "Група"
         << setw(10) << "Курс"
         << setw(30) << "Спеціальність" << endl;
    printLine();

    for (const Group& group : groups) {
        cout << left << setw(5) << group.id
             << setw(15) << group.name
             << setw(10) << group.course
             << setw(30) << group.speciality << endl;
    }
}

void printWorkloadRow(const Workload& item) {
    Teacher* teacher = findTeacherById(item.teacherId);
    Subject* subject = findSubjectById(item.subjectId);
    Group* group = findGroupById(item.groupId);

    cout << left << setw(5) << item.id
         << setw(28) << (teacher != nullptr ? teacher->fullName : "-")
         << setw(28) << (subject != nullptr ? subject->name : "-")
         << setw(12) << (group != nullptr ? group->name : "-")
         << setw(18) << item.lessonType
         << setw(8) << item.hours << endl;
}

void printAllWorkloads() {
    printLine();
    cout << left << setw(5) << "ID"
         << setw(28) << "Викладач"
         << setw(28) << "Дисципліна"
         << setw(12) << "Група"
         << setw(18) << "Вид"
         << setw(8) << "Год." << endl;
    printLine();

    for (const Workload& item : workloads) {
        printWorkloadRow(item);
    }
}

void printTeacherSummary() {
    printLine();
    cout << left << setw(5) << "ID"
         << setw(35) << "Викладач"
         << setw(12) << "Норма"
         << setw(12) << "Факт"
         << setw(20) << "Стан" << endl;
    printLine();

    for (const Teacher& teacher : teachers) {
        int total = calculateTeacherHours(teacher.id);
        string state = total > teacher.maxHours ? "перевищення" : "норма";

        cout << left << setw(5) << teacher.id
             << setw(35) << teacher.fullName
             << setw(12) << teacher.maxHours
             << setw(12) << total
             << setw(20) << state << endl;
    }
}
