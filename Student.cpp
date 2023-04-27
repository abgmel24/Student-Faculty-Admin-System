#include "Student.h"
Student::Student() {}
Student::Student(unsigned int s, unsigned int a, string n, string l, string m, double gpa) {
    studentID = s;
    advisorID = a;
    name = n;
    level = l;
    major = m;
    this->gpa = gpa;
}
Student::~Student() {}

bool Student::operator== (Student* s) {
    return this->studentID == s->getStudentID();
}

bool Student::operator!= (Student* s) {
    return this->studentID != s->getStudentID();
}

//TODO
bool Student::operator> (Student* s) {
    return true;
}
bool Student::operator< (Student* s) {
    return true;
}

//getters
unsigned int Student::getStudentID() {
    return studentID;
}
unsigned int Student::getAdvisorID() {
    return advisorID;
}
string Student::getName() {
    return name;
}
string Student::getLevel() {
    return level;
}
string Student::getMajor() {
    return major;
}
double Student::getGPA() {
    return gpa;
}

int main() {
    return 0;
}