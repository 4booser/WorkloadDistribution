#pragma once

#include "models.h"

#include <vector>

extern std::vector<Teacher> teachers;
extern std::vector<Subject> subjects;
extern std::vector<Group> groups;
extern std::vector<Workload> workloads;

Teacher* findTeacherById(int id);
Subject* findSubjectById(int id);
Group* findGroupById(int id);

void addTeacher();
void addSubject();
void addGroup();
void addWorkload();

int calculateTeacherHours(int teacherId);
void searchWorkloads();
void fillDemoData();
