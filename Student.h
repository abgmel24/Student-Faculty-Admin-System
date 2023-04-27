#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
using namespace std;

class Student {
    public:
        Student();
        Student(unsigned int s, unsigned int a, string n, string l, string m, double gpa);
        ~Student();

        bool operator==(Student* s);
        bool operator!=(Student* s);

        bool operator>(Student* s);
        bool operator<(Student* s);
    private:
        unsigned int studentID;
        unsigned int advisorID;
        string name;
        string level;
        string major;
        double gpa;

    public:
        unsigned int getStudentID();
        unsigned int getAdvisorID();
        string getName();
        string getLevel();
        string getMajor();
        double getGPA();
};

#endif