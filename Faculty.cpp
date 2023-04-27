#include "Faculty.h"

Faculty::Faculty() {};
Faculty::Faculty(unsigned int f, string n, string l, string d) {
    facultyID = f;
    name = n;
    level = l;
    listOfStudents = new TDoublyLinkedList<unsigned int>();
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

unsigned int Faculty::getFacultyID() {
    return facultyID;
}

string Faculty::getName() {
    return name;
}

string Faculty::getLevel() {
    return level;
}

TDoublyLinkedList<unsigned int>* Faculty::getListOfStudents() {
    return listOfStudents;
}

int main() {
    return 0;
}