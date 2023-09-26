#include "Faculty.h"

Faculty::Faculty() {
    facultyID = -1;
};

Faculty::Faculty(int id) {
    facultyID = id;
}

Faculty::Faculty(int f, string n, string l) {
    facultyID = f;
    name = n;
    level = l;
    listOfStudents = new TSingleLinkedList<int>();
}

Faculty::~Faculty() {
    delete listOfStudents;
}

bool Faculty::operator==(Faculty *f) {
    return this->facultyID == f->getFacultyID();
}
bool Faculty::operator!=(Faculty *f) {
    return this->facultyID != f->getFacultyID();
}
bool Faculty::operator>(Faculty *f) {
    return true;
}
bool Faculty::operator<(Faculty *f) {
    return true;
}

void Faculty::toFile(ostream &os) {
    os << "ID " << facultyID << ", " << "Name: " << name << ", Level: " << level << endl << "      List of Student IDs: ";
    listOfStudents->toFile(os);
    cout << endl;
}

void Faculty::addStudent(int i) {
    listOfStudents->insertFront(i);
}

int Faculty::removeStudent(int i) {
    return listOfStudents->remove(i);
};


//getters
int Faculty::getFacultyID() {
    return facultyID;
}

string Faculty::getName() {
    return name;
}

string Faculty::getLevel() {
    return level;
}

TSingleLinkedList<int>* Faculty::getListOfStudents() {
    return listOfStudents;
}