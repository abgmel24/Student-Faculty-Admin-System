#include "Configuration.h"

int main(int argc, char** argv) {
    Configuration *c = new Configuration();

    /*** UNCOMMENT TO CREATE AN INITIAL DATABASE OF 2 STUDENTS AND 2 FACULTY ***/
    // Faculty* f1 = new Faculty(100, "Edgin", "Professor");
    // Faculty* f2 = new Faculty(101, "Xenk", "Dean");
    // Student* s1 = new Student(4, 100, "Simon", "freshman", "Data Science", 5.3);
    // f1->addStudent(s1->getStudentID());
    // Student* s2 = new Student(3, 100, "Jarnathan", "freshman", "Computer Science", 4.4);
    // f1->addStudent(s2->getStudentID());

    // c->students->insert(s1);
    // c->students->insert(s2);

    // c->faculty->insert(f1);
    // c->faculty->insert(f2);


    while(c->runProgram()) {
        cout << endl;
    }

    delete c;
}