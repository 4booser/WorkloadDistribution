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
         << setw(32) << "Full name"
         << setw(25) << "Department"
         << setw(10) << "Max"
         << setw(10) << "Fact" << endl;
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
         << setw(35) << "Subject"
         << setw(12) << "Semester"
         << setw(10) << "Hours" << endl;
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
         << setw(15) << "Group"
         << setw(10) << "Course"
         << setw(30) << "Speciality" << endl;
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
         << setw(28) << "Teacher"
         << setw(28) << "Subject"
         << setw(12) << "Group"
         << setw(18) << "Type"
         << setw(8) << "Hours" << endl;
    printLine();

    for (const Workload& item : workloads) {
        printWorkloadRow(item);
    }
}

void printTeacherSummary() {
    printLine();
    cout << left << setw(5) << "ID"
         << setw(35) << "Teacher"
         << setw(12) << "Max"
         << setw(12) << "Fact"
         << setw(20) << "State" << endl;
    printLine();

    for (const Teacher& teacher : teachers) {
        int total = calculateTeacherHours(teacher.id);
        string state = total > teacher.maxHours ? "exceeded" : "normal";

        cout << left << setw(5) << teacher.id
             << setw(35) << teacher.fullName
             << setw(12) << teacher.maxHours
             << setw(12) << total
             << setw(20) << state << endl;
    }
}
