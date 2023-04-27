#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include <string>
#include "TDoublyLinkedList.h"

using namespace std;

class Faculty {
    public:
        Faculty();
        Faculty(unsigned int f, string n, string l, string d);
        ~Faculty();

        bool operator==(Faculty *f);
        bool operator!=(Faculty *f);
        bool operator>(Faculty *f);
        bool operator<(Faculty *f);

    
    private:
        unsigned int facultyID;
        string name;
        string level;
        TDoublyLinkedList<unsigned int> *listOfStudents;

    public:
        unsigned int getFacultyID();
        string getName();
        string getLevel();
        TDoublyLinkedList<unsigned int>* getListOfStudents();
};


#endif