#include "storage.h"
#include "data.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const string TEACHERS_FILE = "teachers.txt";
const string SUBJECTS_FILE = "subjects.txt";
const string GROUPS_FILE = "groups.txt";
const string WORKLOADS_FILE = "workloads.txt";

bool fileExists(const string& fileName) {
    ifstream file(fileName);
    return file.good();
}

bool splitLine(const string& line, string parts[], int count) {
    stringstream stream(line);
    string part;
    int index = 0;

    while (getline(stream, part, ';') && index < count) {
        parts[index] = part;
        index++;
    }

    return index == count;
}

void loadTeachers() {
    ifstream file(TEACHERS_FILE);
    string line;

    while (getline(file, line)) {
        string parts[4];

        if (splitLine(line, parts, 4)) {
            Teacher teacher;
            teacher.id = stoi(parts[0]);
            teacher.fullName = parts[1];
            teacher.department = parts[2];
            teacher.maxHours = stoi(parts[3]);

            teachers.push_back(teacher);
        }
    }
}

void loadSubjects() {
    ifstream file(SUBJECTS_FILE);
    string line;

    while (getline(file, line)) {
        string parts[4];

        if (splitLine(line, parts, 4)) {
            Subject subject;
            subject.id = stoi(parts[0]);
            subject.name = parts[1];
            subject.semester = stoi(parts[2]);
            subject.planHours = stoi(parts[3]);

            subjects.push_back(subject);
        }
    }
}

void loadGroups() {
    ifstream file(GROUPS_FILE);
    string line;

    while (getline(file, line)) {
        string parts[4];

        if (splitLine(line, parts, 4)) {
            Group group;
            group.id = stoi(parts[0]);
            group.name = parts[1];
            group.course = stoi(parts[2]);
            group.speciality = parts[3];

            groups.push_back(group);
        }
    }
}

void loadWorkloads() {
    ifstream file(WORKLOADS_FILE);
    string line;

    while (getline(file, line)) {
        string parts[6];

        if (splitLine(line, parts, 6)) {
            Workload workload;
            workload.id = stoi(parts[0]);
            workload.teacherId = stoi(parts[1]);
            workload.subjectId = stoi(parts[2]);
            workload.groupId = stoi(parts[3]);
            workload.lessonType = parts[4];
            workload.hours = stoi(parts[5]);

            workloads.push_back(workload);
        }
    }
}

bool loadData() {
    teachers.clear();
    subjects.clear();
    groups.clear();
    workloads.clear();

    if (!fileExists(TEACHERS_FILE) ||
        !fileExists(SUBJECTS_FILE) ||
        !fileExists(GROUPS_FILE) ||
        !fileExists(WORKLOADS_FILE)) {
        fillDemoData();
        return false;
    }

    loadTeachers();
    loadSubjects();
    loadGroups();
    loadWorkloads();

    return true;
}

bool saveTeachers() {
    ofstream file(TEACHERS_FILE);

    if (!file.is_open()) {
        return false;
    }

    for (const Teacher& teacher : teachers) {
        file << teacher.id << ';'
             << teacher.fullName << ';'
             << teacher.department << ';'
             << teacher.maxHours << endl;
    }

    return true;
}

bool saveSubjects() {
    ofstream file(SUBJECTS_FILE);

    if (!file.is_open()) {
        return false;
    }

    for (const Subject& subject : subjects) {
        file << subject.id << ';'
             << subject.name << ';'
             << subject.semester << ';'
             << subject.planHours << endl;
    }

    return true;
}

bool saveGroups() {
    ofstream file(GROUPS_FILE);

    if (!file.is_open()) {
        return false;
    }

    for (const Group& group : groups) {
        file << group.id << ';'
             << group.name << ';'
             << group.course << ';'
             << group.speciality << endl;
    }

    return true;
}

bool saveWorkloads() {
    ofstream file(WORKLOADS_FILE);

    if (!file.is_open()) {
        return false;
    }

    for (const Workload& workload : workloads) {
        file << workload.id << ';'
             << workload.teacherId << ';'
             << workload.subjectId << ';'
             << workload.groupId << ';'
             << workload.lessonType << ';'
             << workload.hours << endl;
    }

    return true;
}

bool saveData() {
    bool result = saveTeachers() &&
                  saveSubjects() &&
                  saveGroups() &&
                  saveWorkloads();

    if (result) {
        cout << "Дані збережено." << endl;
    } else {
        cout << "Помилка збереження даних." << endl;
    }

    return result;
}
