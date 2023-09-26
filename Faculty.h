#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include <string>
#include "TSingleLinkedList.h"

using namespace std;

class Faculty {
    public:
        Faculty();
        Faculty(int id);
        Faculty(int f, string n, string l);
        ~Faculty();

        bool operator==(Faculty *f);
        bool operator!=(Faculty *f);
        bool operator>(Faculty *f);
        bool operator<(Faculty *f);

        void toFile(ostream& os);
        void addStudent(int i);
        int removeStudent(int i);
    
    private:
        int facultyID;
        string name;
        string level;
        TSingleLinkedList<int>* listOfStudents;

    public:
        int getFacultyID();
        string getName();
        string getLevel();
        TSingleLinkedList<int>* getListOfStudents();
};


#endif