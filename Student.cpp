#include "Student.h"
Student::Student() {
    studentID = -1;
    advisorID = -1;
    name = "";
    level = "";
    major = "";
    gpa = -1.0;
}

Student::Student(int id) {
    studentID = id;
    advisorID = -1;
    name = "";
    level = "";
    major = "";
    gpa = -1.0;
}

Student::Student(int s, int a, string n, string l, string m, double gpa) {
    studentID = s;
    advisorID = a;
    name = n;
    level = l;
    major = m;
    this->gpa = gpa;
}

Student::Student(int s, string n, string l, string m, double gpa) {
    studentID = s;
    advisorID = -1;
    name = n;
    level = l;
    major = m;
    this->gpa = gpa;
}

Student::~Student() {}

//https://www.tutorialspoint.com/cplusplus/relational_operators_overloading.htm
bool Student::operator ==(Student* s) {
    return studentID == s->getStudentID();
}

bool Student::operator !=(Student* s) {
    return !(this == s);
}

//TODO
bool Student::operator> (Student* s) {
    return this->studentID > s->getStudentID();
}
bool Student::operator< (Student* s) {
    return this->studentID < s->getStudentID();
}

// ostream& Student::operator<<(const ostream &os) {
//     os << "ID " << studentID << ", " << "Name: " << ", Major: " << major << ", Level: " << level << ", GPA: " << gpa << ", Advisor ID: " << advisorID;  
//     return os;
// }

void Student::toFile(ostream &os) {
    if(studentID == -1) {
        os << "There is no student with that ID." << endl;
        return;
    }
    os << "ID " << studentID << ", " << "Name: " << name << ", Major: " << major << ", Level: " << level;
    os << ", GPA: " << gpa;
    if(advisorID == -1) {
        os << endl << "This student has no advisor." << endl;
    } else {
        os << ", Advisor ID: " << advisorID << endl;
    }
}

//getters and setters
int Student::getStudentID() {
    return studentID;
}
int Student::getAdvisorID() {
    return advisorID;
}
void Student::setAdvisorID(int i) {
    advisorID = i;
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