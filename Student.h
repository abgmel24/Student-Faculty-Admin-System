#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Student {
    public:
        Student();
        Student(int id);
        Student(int s, int a, string n, string l, string m, double gpa);
        Student(int s, string n, string l, string m, double gpa);
        ~Student();

        // bool operator==(Student* s);
        bool operator ==(Student* s);
        bool operator!=(Student* s);

        bool operator>(Student* s);
        bool operator<(Student* s);

        void toFile(ostream &os);

        // ostream& operator<<(const ostream &os);
    private:
        int studentID;
        int advisorID;
        string name;
        string level;
        string major;
        double gpa;

    public:
        int getStudentID();
        int getAdvisorID();
        void setAdvisorID(int i);
        string getName();
        string getLevel();
        string getMajor();
        double getGPA();
};

#endif