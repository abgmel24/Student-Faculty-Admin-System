#include "Configuration.h"

Configuration::Configuration() {
    students = new LazyBST<Student*>();
    faculty = new LazyBST<Faculty*>();
}

Configuration::~Configuration() {
    delete students;
    delete faculty;
}

bool Configuration::runProgram() {
    string input;
    printOptions();
    getline(cin, input);
    if(input == "1") {
        //Students info in ascending order
        outputStudents(cout);
    } else if(input == "2") {
        //Faculty info in ascending order
        outputFaculty(cout);
    //Display particular student info
    } else if(input == "3") {
        //get student id
        if(students->isEmpty()) {
            cout << "There are currently no students in the database." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
        }
        int id = -1;
        cout << "Enter a valid student ID: ";
        string temp;
        getline(cin, temp);
        id = stoi(temp);
        //find and print student
        Student *tempStudent = new Student(id);
        tempStudent = students->find(tempStudent);
        if(tempStudent == NULL) {
            cout << "A student with that Student ID does not exist." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
            return true;
        }
        tempStudent->toFile(cout);
        tempStudent = NULL;
    //Display particular faculty info
    } else if(input == "4") {
        //get faculty id
        int id = -1;
        cout << "Enter a valid faculty ID: ";
        string temp;
        getline(cin, temp);
        id = stoi(temp);
        //print faculty info
        Faculty *tempFaculty = new Faculty(id);
        tempFaculty = faculty->find(tempFaculty);
        if(tempFaculty == NULL) {
            cout << "A member with that Faculty ID does not exist." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
            return true;
        }
        tempFaculty->toFile(cout);
        tempFaculty = NULL;
    //add a new student
    } else if(input == "5") {
        //if there's no faculty
        if(faculty->isEmpty()) {
            //ask to add faculty first
            cout << "Enter a faculty before trying to add a student." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
            //break
            return true;
        }
        //get student id
        int sID = -1;
        cout << "Enter a valid student ID: ";
        string temp;
        getline(cin, temp);
        sID = stoi(temp);
        Student *tempStudent = new Student(sID);
        tempStudent = students->find(tempStudent);
        if(tempStudent != NULL) {
            cout << "A student with that ID already exists." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
            tempStudent = NULL;
            return true;
        }
        //advisor id
        int fID = -1;
        cout << "Enter a valid faculty ID: ";
        getline(cin, temp);
        fID = stoi(temp);
        Faculty *tempFaculty = new Faculty(fID);
        tempFaculty = faculty->find(tempFaculty);
        if(tempFaculty == NULL) {
            cout << "A member with that Faculty ID does not exist." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
            return true;
        }

        //name
        string sName;
        cout << "Enter the student's name: ";
        getline(cin, sName);
        //major
        string sMajor;
        cout << "Enter the student's major: ";
        getline(cin, sMajor);
        //level
        string sLevel;
        cout << "Enter the student's level: ";
        getline(cin, sLevel);
        //gpa
        double sGPA;
        cout << "Enter the student's GPA: ";
        getline(cin, temp);
        sGPA = stod(temp);
            
        //create student
        tempStudent = new Student(sID, fID, sName, sLevel, sMajor, sGPA);
        students->insert(tempStudent);
        //add student to faculty's list
        tempFaculty->addStudent(sID);
    //delete student
    } else if(input == "6") {
        //get id
        int sID = -1;
        cout << "Enter a valid student ID: ";
        string temp;
        getline(cin, temp);
        sID = stoi(temp);
        Student *tempStudent = students->find(new Student(sID));
        if(tempStudent == NULL) {
            cout << "A student with that ID does not exist." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
            tempStudent = NULL;
            return true;
        }
        //remove student from advisor list
        Faculty *tempFaculty = faculty->find(new Faculty(tempStudent->getAdvisorID()));
        if(tempFaculty == NULL) {
            cout << "A member with that Faculty ID does not exist." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
            return true;
        }
        tempFaculty->removeStudent(sID);
        //remove student from tree
        students->remove(tempStudent);
    //add faculty member
    } else if(input == "7") {
        //get faculty id
        int fID = -1;
        cout << "Enter a valid faculty ID: ";
        string temp;
        getline(cin, temp);
        fID = stoi(temp);
        Faculty *tempFaculty = new Faculty(fID);
        tempFaculty = faculty->find(tempFaculty);
        if(tempFaculty != NULL) {
            cout << "A member with that Faculty ID already exists." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
            return true;
        }
        //get name
        string fName;
        cout << "Enter the faculty member's name: ";
        getline(cin, fName);
        //get level
        string fLevel;
        cout << "Enter the faculty member's level: ";
        getline(cin, fLevel);
        //create faculty and add to tree
        tempFaculty = new Faculty(fID, fName, fLevel);
        faculty->insert(tempFaculty);
    //delete faculty
    } else if(input == "8") {
        //get id
        int fID = -1;
        cout << "Enter a valid faculty ID: ";
        string temp;
        getline(cin, temp);
        fID = stoi(temp);
        Faculty *tempFaculty = new Faculty(fID);
        tempFaculty = faculty->find(tempFaculty);
        if(tempFaculty == NULL) {
            cout << "A member with that Faculty ID does not exist." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
            return true;
        }
        //set student advisors to -1
        removeAdvisees(tempFaculty);
        //remove from tree
        faculty->remove(tempFaculty);
    //change advisor
    } else if(input == "9") {
        //get student id
        int sID = -1;
        cout << "Enter a valid student ID: ";
        string temp;
        getline(cin, temp);
        sID = stoi(temp);
        Student *tempStudent = new Student(sID);
        tempStudent = students->find(tempStudent);
        if(tempStudent == NULL) {
            cout << "A student with that ID does not exist." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
            return true;
        }
        //get new faculty
        int fID = -1;
        cout << "Enter a valid faculty ID: ";
        getline(cin, temp);
        fID = stoi(temp);
        Faculty *tempFaculty = new Faculty(fID);
        tempFaculty = faculty->find(tempFaculty);
        if(tempFaculty == NULL) {
            cout << "A member with that Faculty ID does not exist." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
            return true;
        }
        //get faculty id to remove
        int oldID = tempStudent->getAdvisorID();
        Faculty *old = faculty->find(new Faculty(oldID));
        if(old == NULL) {
            cout << "A member with that Faculty ID does not exist." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
            return true;
        }
        //remove student from advisor's list
        old->removeStudent(sID);
        //set advisor to new advisor
        tempStudent->setAdvisorID(fID);
        //add student to new advisor's list
        tempFaculty->addStudent(sID);
    //remove advisee
    } else if(input == "10") {
        //get faculty id
        int fID = -1;
        cout << "Enter a valid faculty ID to remove from: ";
        string temp;
        getline(cin, temp);
        fID = stoi(temp);
        Faculty *tempFaculty = new Faculty(fID);
        tempFaculty = faculty->find(tempFaculty);
        if(tempFaculty == NULL) {
            cout << "A member with that Faculty ID does not exist." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
            return true;
        }
        //get student id to remove
        int sID = -1;
        cout << "Enter a valid student ID to remove: ";
        getline(cin, temp);
        sID = stoi(temp);
        Student *tempStudent = new Student(sID);
        tempStudent = students->find(tempStudent);
        if(tempStudent == NULL) {
            cout << "A student with that ID does not exist." << endl;
            cout << "Press any key to go back to the main menu." << endl;
            string c;
            getline(cin, c);
            return true;
        }
        //remove student from advisor's list
        tempFaculty->removeStudent(sID);
        //set student's advisor value to -1
        tempStudent->setAdvisorID(-1);
    //exit
    } else if(input == "11") { 
        cout << "Exiting program . . . ." << endl;
        ofstream outFS;
        outFS.open("runLog.txt");

        if(!outFS.is_open()) {
            throw runtime_error("Could not open file runLog.txt");
        }
        output(outFS);
        cout << "The output can be found in a file called runLog.txt" << endl;
        outFS.close();
        return false;
    } else {
        cout << "Please only select one of the options displayed options." << endl;
    }

    cout << "Press any key to go back to the main menu." << endl;
    string c;
    getline(cin, c);
    cout << endl;
    return !(input == "11");
}

void Configuration::printOptions() {
    cout << "Select one of the following options by entering the corresponding number" << endl;
    cout << "========================================================================" << endl;
    cout << "1 - Print all students and their information" << endl;
    cout << "2 - Print all faculty and their information" << endl;
    cout << "3 - Find and display one student's information" << endl;
    cout << "4 - Find and display one advisor's information" << endl;
    cout << "5 - Add a new student" << endl;
    cout << "6 - Delete a student" << endl;
    cout << "7 - Add a new advisor" << endl;
    cout << "8 - Delete an advisor" << endl;
    cout << "9 - Change a student's advisor" << endl;
    cout << "10 - Remove an advisee from a faculty member's list" << endl;
    cout << "11 - Output to file and quit the program" << endl;
    cout << "Pick an option: ";
}

void Configuration::output(ostream& os) {
    outputStudents(os);
    outputFaculty(os);
}

void Configuration::outputStudents(ostream& os) {
    os << "Student Directory" << endl;
    os << "=================" << endl;   
    students->toFile(os);
}

void Configuration::outputFaculty(ostream& os) {
    os << "Faculty Directory" << endl;
    os << "=================" << endl;
    faculty->toFile(os);
}

void Configuration::removeAdvisees(Faculty* f) {
    int sID = -1;
    Student *temp;
    while(f->getListOfStudents()->getSize() > 0) {
        sID = f->getListOfStudents()->removeFront();

        temp = new Student(sID);
        temp = students->find(temp);
        if(temp == NULL) {
            throw runtime_error("Error deleting student with ID " + sID);
        }

        temp->setAdvisorID(-1);
    }
}
