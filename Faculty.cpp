#include "Assignment-5.h"

Faculty::Faculty() {
    id = -1;
    level = -1;
    department = "null";
}

Faculty::Faculty(int id, string level, string department) {
    this->id = id;
    this->level = level;
    this->department = department;
}

int Faculty::GetId() {
    return id;
}

string Faculty::GetLevel() {
    return level;
}

int Faculty::GetAdviseeNumber() {
    return adviseesIds->getSize();
}

string Faculty::GetDepartment() {
    return department;
}

void Faculty::SetId(int newId) {
    id = newId;
}

void Faculty::SetLevel(string newLevel) {
    level = newLevel;
}

void Faculty::SetDepartment(string newDepartment) {
    department = newDepartment;
}

void Faculty::AddAdviseesById(int id){
  adviseesIds->insertFront(id);
}

void Faculty::PrintStats() {
    cout << "\nFaculty Id: " << GetId() << endl;
    cout << "Level: " << GetLevel() << endl;
    cout << "Department: " << GetDepartment() << endl;
    PrintFacultyMemberAdvisees();
}

void Faculty::PrintFacultyMemberAdvisees() {
    cout << "Advisees Ids: " << endl;
    adviseesIds->printList();
}
void Faculty::AddAdvisees() {
    int input;
    string checkAdd;
    while (input != -1) {
        cout << "Enter Student Id's of Advisees (-1 to stop): ";
        cin >> input;

        if (input != -1) {
            /*
            if(CheckToSeeIfStudentExists(input)) {
                adviseesIds->insertFront(input);
            }
            else {
                cout << "The student Id that you entered does not exist.  Do you still want to add it? (yes/no): ";
                cin >> checkAdd;

                if (checkAdd == "yes") {
                    adviseesIds->insertFront(input);
                }
            }
            */
           adviseesIds->insertFront(input);
        }
    }
}
void Faculty::RemoveAdvisee(int studentId) {
    int pos = adviseesIds->find(studentId);
    int deletedStudentId = adviseesIds->deletePos(pos);
}

void Faculty::PrintStatsToFile(ofstream& outfile) {
    outfile << GetId() << endl;
    outfile << GetLevel() << endl;
    outfile << GetDepartment() << endl;
    outfile << "Advisees:" << endl;
    adviseesIds->printListToFile(outfile);
    outfile << "----------" << endl;
}

int Faculty::RemoveFrontAdvisee() {
    return adviseesIds->removeFront();
}

bool Faculty::CheckIfThereAreAdvisees() {
    if (adviseesIds->isEmpty())
        return false;
    return true;
}

void Faculty::AddAdvisee(int studentId) {
    adviseesIds->insertFront(studentId);
}