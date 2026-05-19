#pragma once

#include <string>

const int DEFAULT_MAX_HOURS = 720;
const int MIN_HOURS = 1;
const int EXIT_CODE = 0;

struct Teacher {
    int id;
    std::string fullName;
    std::string department;
    int maxHours;
};

struct Subject {
    int id;
    std::string name;
    int semester;
    int planHours;
};

struct Group {
    int id;
    std::string name;
    int course;
    std::string speciality;
};

struct Workload {
    int id;
    int teacherId;
    int subjectId;
    int groupId;
    std::string lessonType;
    int hours;
};
