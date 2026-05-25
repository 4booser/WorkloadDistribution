#include "data.h"
#include "report.h"
#include "ui.h"

#include <cctype>
#include <iostream>
#include <string>

using namespace std;

vector<Teacher> teachers;
vector<Subject> subjects;
vector<Group> groups;
vector<Workload> workloads;

string toLowerText(string value) {
    for (char& symbol : value) {
        symbol = (char)tolower((unsigned char)symbol);
    }
    return value;
}

Teacher* findTeacherById(int id) {
    for (Teacher& teacher : teachers) {
        if (teacher.id == id) {
            return &teacher;
        }
    }
    return nullptr;
}

Subject* findSubjectById(int id) {
    for (Subject& subject : subjects) {
        if (subject.id == id) {
            return &subject;
        }
    }
    return nullptr;
}

Group* findGroupById(int id) {
    for (Group& group : groups) {
        if (group.id == id) {
            return &group;
        }
    }
    return nullptr;
}

void addTeacher() {
    Teacher teacher;

    teacher.id = (int)teachers.size() + 1;
    teacher.fullName = readLine("Enter teacher full name: ");
    teacher.department = readLine("Enter department: ");
    teacher.maxHours = readInt("Enter max hours: ");

    if (teacher.maxHours <= 0) {
        teacher.maxHours = DEFAULT_MAX_HOURS;
    }

    teachers.push_back(teacher);
    cout << "Teacher added. ID = " << teacher.id << endl;
}

void addSubject() {
    Subject subject;

    subject.id = (int)subjects.size() + 1;
    subject.name = readLine("Enter subject name: ");
    subject.semester = readInt("Enter semester: ");
    subject.planHours = readInt("Enter planned hours: ");

    if (subject.planHours < MIN_HOURS) {
        cout << "Hours must be positive." << endl;
        return;
    }

    subjects.push_back(subject);
    cout << "Subject added. ID = " << subject.id << endl;
}

void addGroup() {
    Group group;

    group.id = (int)groups.size() + 1;
    group.name = readLine("Enter group name: ");
    group.course = readInt("Enter course: ");
    group.speciality = readLine("Enter speciality: ");

    groups.push_back(group);
    cout << "Group added. ID = " << group.id << endl;
}

int calculateTeacherHours(int teacherId) {
    int total = 0;

    for (const Workload& item : workloads) {
        if (item.teacherId == teacherId) {
            total += item.hours;
        }
    }

    return total;
}

void addWorkload() {
    if (teachers.empty() || subjects.empty() || groups.empty()) {
        cout << "First add teacher, subject and group." << endl;
        return;
    }

    int teacherId = readInt("Enter teacher ID: ");
    int subjectId = readInt("Enter subject ID: ");
    int groupId = readInt("Enter group ID: ");

    Teacher* teacher = findTeacherById(teacherId);
    Subject* subject = findSubjectById(subjectId);
    Group* group = findGroupById(groupId);

    if (teacher == nullptr || subject == nullptr || group == nullptr) {
        cout << "Error. One of the IDs was not found." << endl;
        return;
    }

    Workload item;

    item.id = (int)workloads.size() + 1;
    item.teacherId = teacherId;
    item.subjectId = subjectId;
    item.groupId = groupId;
    item.lessonType = readLine("Enter lesson type: ");
    item.hours = readInt("Enter hours: ");

    if (item.hours < MIN_HOURS) {
        cout << "Hours must be positive." << endl;
        return;
    }

    if (calculateTeacherHours(teacherId) + item.hours > teacher->maxHours) {
        cout << "Warning: teacher max hours will be exceeded." << endl;
    }

    workloads.push_back(item);
    cout << "Workload record added." << endl;
}

void searchWorkloads() {
    string query = readLine("Enter search keyword: ");
    string normalizedQuery = toLowerText(query);
    bool found = false;

    printLine();
    cout << "Search results" << endl;
    printLine();

    for (const Workload& item : workloads) {
        Teacher* teacher = findTeacherById(item.teacherId);
        Subject* subject = findSubjectById(item.subjectId);
        Group* group = findGroupById(item.groupId);

        string text;
        if (teacher != nullptr) text += teacher->fullName + " ";
        if (subject != nullptr) text += subject->name + " ";
        if (group != nullptr) text += group->name + " ";
        text += item.lessonType;

        if (toLowerText(text).find(normalizedQuery) != string::npos) {
            printWorkloadRow(item);
            found = true;
        }
    }

    if (!found) {
        cout << "Records not found." << endl;
    }
}

void fillDemoData() {
    teachers.push_back({ 1, "Petrenko Ivan", "Programming department", 720 });
    teachers.push_back({ 2, "Ivanenko Olena", "Math department", 680 });
    teachers.push_back({ 3, "Shevchenko Andrii", "Computer science department", 700 });

    subjects.push_back({ 1, "Programming", 2, 120 });
    subjects.push_back({ 2, "Databases", 3, 90 });
    subjects.push_back({ 3, "Higher Mathematics", 2, 100 });
    subjects.push_back({ 4, "Computer Networks", 4, 80 });

    groups.push_back({ 1, "P-21", 2, "121 Software Engineering" });
    groups.push_back({ 2, "P-22", 2, "121 Software Engineering" });
    groups.push_back({ 3, "KB-11", 1, "125 Cybersecurity" });

    workloads.push_back({ 1, 1, 1, 1, "lectures", 30 });
    workloads.push_back({ 2, 1, 1, 2, "practice", 40 });
    workloads.push_back({ 3, 2, 3, 1, "lectures", 35 });
    workloads.push_back({ 4, 3, 2, 3, "labs", 45 });
}
