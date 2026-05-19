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
    teacher.fullName = readLine("Введіть ПІБ викладача: ");
    teacher.department = readLine("Введіть назву підрозділу: ");
    teacher.maxHours = readInt("Введіть максимальне навантаження: ");

    if (teacher.maxHours <= 0) {
        teacher.maxHours = DEFAULT_MAX_HOURS;
    }

    teachers.push_back(teacher);
    cout << "Викладача додано. ID = " << teacher.id << endl;
}

void addSubject() {
    Subject subject;

    subject.id = (int)subjects.size() + 1;
    subject.name = readLine("Введіть назву дисципліни: ");
    subject.semester = readInt("Введіть семестр: ");
    subject.planHours = readInt("Введіть планову кількість годин: ");

    if (subject.planHours < MIN_HOURS) {
        cout << "Кількість годин повинна бути додатною." << endl;
        return;
    }

    subjects.push_back(subject);
    cout << "Дисципліну додано. ID = " << subject.id << endl;
}

void addGroup() {
    Group group;

    group.id = (int)groups.size() + 1;
    group.name = readLine("Введіть назву групи: ");
    group.course = readInt("Введіть курс: ");
    group.speciality = readLine("Введіть спеціальність: ");

    groups.push_back(group);
    cout << "Групу додано. ID = " << group.id << endl;
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
        cout << "Спочатку потрібно додати викладача, дисципліну та групу." << endl;
        return;
    }

    int teacherId = readInt("Введіть ID викладача: ");
    int subjectId = readInt("Введіть ID дисципліни: ");
    int groupId = readInt("Введіть ID групи: ");

    Teacher* teacher = findTeacherById(teacherId);
    Subject* subject = findSubjectById(subjectId);
    Group* group = findGroupById(groupId);

    if (teacher == nullptr || subject == nullptr || group == nullptr) {
        cout << "Помилка. Один із ідентифікаторів не знайдено." << endl;
        return;
    }

    Workload item;

    item.id = (int)workloads.size() + 1;
    item.teacherId = teacherId;
    item.subjectId = subjectId;
    item.groupId = groupId;
    item.lessonType = readLine("Введіть вид заняття: ");
    item.hours = readInt("Введіть кількість годин: ");

    if (item.hours < MIN_HOURS) {
        cout << "Кількість годин повинна бути додатною." << endl;
        return;
    }

    if (calculateTeacherHours(teacherId) + item.hours > teacher->maxHours) {
        cout << "Увага: після додавання буде перевищено норму викладача." << endl;
    }

    workloads.push_back(item);
    cout << "Запис навантаження створено." << endl;
}

void searchWorkloads() {
    string query = readLine("Введіть ключове слово для пошуку: ");
    string normalizedQuery = toLowerText(query);
    bool found = false;

    printLine();
    cout << "Результати пошуку" << endl;
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
        cout << "Записи не знайдено." << endl;
    }
}

void fillDemoData() {
    teachers.push_back({ 1, "Петренко Іван Миколайович", "ЦК програмування", 720 });
    teachers.push_back({ 2, "Іваненко Олена Сергіївна", "ЦК математики", 680 });
    teachers.push_back({ 3, "Шевченко Андрій Петрович", "ЦК комп'ютерних наук", 700 });

    subjects.push_back({ 1, "Програмування", 2, 120 });
    subjects.push_back({ 2, "Бази даних", 3, 90 });
    subjects.push_back({ 3, "Вища математика", 2, 100 });
    subjects.push_back({ 4, "Комп'ютерні мережі", 4, 80 });

    groups.push_back({ 1, "П-21", 2, "121 Інженерія програмного забезпечення" });
    groups.push_back({ 2, "П-22", 2, "121 Інженерія програмного забезпечення" });
    groups.push_back({ 3, "КБ-11", 1, "125 Кібербезпека" });

    workloads.push_back({ 1, 1, 1, 1, "лекції", 30 });
    workloads.push_back({ 2, 1, 1, 2, "практичні", 40 });
    workloads.push_back({ 3, 2, 3, 1, "лекції", 35 });
    workloads.push_back({ 4, 3, 2, 3, "лабораторні", 45 });
}
