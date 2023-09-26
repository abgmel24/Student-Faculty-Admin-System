#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "LazyBST.h"
#include "Student.h"
#include "Faculty.h"

using namespace std;

class Configuration {
    public:
        LazyBST<Student*>* students;
        LazyBST<Faculty*>* faculty;
    public:
        Configuration();
        ~Configuration();

        void printOptions();
        bool runProgram();

        void output(ostream &os);
        void outputStudents(ostream &os);
        void outputFaculty(ostream &os);

        void removeAdvisees(Faculty *f); 
};



#endif