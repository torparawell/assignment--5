#include "Assignment-5.h"

Student::Student() {
    id = -1;
    level = "null";
    major = "null";
    gpa = -1;
    advisorId = -1;
}

Student::Student(int id, string level, string major, double gpa, int advisorId) {
    this->id = id;
    this->level = level;
    this->major = major;
    this->gpa = gpa;
    this->advisorId = advisorId;
}

// Getters
int Student::GetId() {
    return id;
}

string Student::GetLevel() {
    return level;
}

string Student::GetMajor() {
    return major;
}

double Student::GetGpa() {
    return gpa;
}

int Student::GetAdvisorId() {
    return advisorId;
}

// Setters
void Student::SetId(int studentId) {
    id = studentId;
}

void Student::SetLevel(string l) {
    level = l;
}

void Student::SetMajor(string m) {
    major = m;
}

void Student::SetGpa(double g) {
    gpa = g;
}

void Student::SetAdvisorId(int ai) {
    advisorId = ai;
}

void Student::PrintStats() {
    cout << "\nStudent ID: " << GetId() << endl;
    cout << "Level: " << GetLevel() << endl;
    cout << "Major: " << GetMajor() << endl;
    cout << "GPA: " << GetGpa() << endl;
    cout << "Advisor Id: " << GetAdvisorId() << endl;
}

void Student::PrintStatsToFile(ofstream& outfile) {
    outfile << GetId() << endl;
    outfile << GetLevel() << endl;
    outfile << GetMajor() << endl;
    outfile << GetGpa() << endl;
    outfile << GetAdvisorId() << endl;
    outfile << endl;
}