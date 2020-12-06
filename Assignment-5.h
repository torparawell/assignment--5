//Files
#include "BST.h"
#include "GenStack.h"
#include "DoublyLinkedList.h"

//Libraries
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Person {
    public:
        Person();
        Person(int id, string level);
        ~Person();

        // Getters
        int GetId();
        string GetLevel();

        // Setters
        void SetId(int id);
        void SetLevel(string level);

    protected:
        int id;
        string level;
};

//Inherits from class person.
class Student : public Person {
    public:
        Student();
        Student(int id, string level, string major, double gpa, int advisor);
        ~Student();

        // Core Functions
        void PrintStats();
        void PrintStatsToFile(ofstream& outfile);

        // Getters
        int GetId();
        string GetLevel();
        string GetMajor();
        double GetGpa();
        int GetAdvisorId();

        // Setters
        void SetId(int id);
        void SetLevel(string level);
        void SetMajor(string level);
        void SetGpa(double gpa);
        void SetAdvisorId(int advisorId);
    private:
        string major;
        double gpa;
        int advisorId; // Contains faculty advisor ID.
};

//Inherits from class person
class Faculty : public Person {
    public:
        Faculty();
        Faculty(int id, string level, string department);
        ~Faculty();

        // Core functions
        void PrintFacultyMember(int id);
        void PrintFacultyMemberAdvisees();
        void PrintStats();
        void PrintStatsToFile(ofstream& outfile);
        void RemoveAdvisee(int studentId);
        void AddAdvisees();
        void AddAdviseesById(int id);
        void AddAdvisee(int studentId);
        int RemoveFrontAdvisee();
        bool CheckIfThereAreAdvisees();

        // Getters
        int GetId();
        int GetAdviseeNumber();
        string GetLevel();
        string GetDepartment();

        // Setters
        void SetId(int id);
        void SetLevel(string level);
        void SetDepartment(string department);
    private:
        // Initializing classes
        string department;
        DoublyLinkedList<int> *adviseesIds = new DoublyLinkedList<int>;
};

class ManageDataBase {
    public:
        ManageDataBase();
        ~ManageDataBase();

        // Core functions
        void PromptUser();
        void AddToStack();
        void Rollback(); 
        
        // Manage Students
        void CreateStudent();
        void DeleteStudent();
        void PrintStudent();
        void ChangeAdvisor();
        bool CheckToSeeIfStudentExists(int studentId);
        void PrintAdvisor();

        // Manage Faculty
        void CreateFacultyMember();
        void DeleteFaculty();
        void PrintFacultyMember(bool onlyAdvisees);
        void RemoveAdvisee();
        Faculty GetAdvisorWithLeastAmountOfAdvisees();
    private:
        int lastOptionNumber;
        int optionNumber;
        void insertStudentRollback(Student*& student);
        void insertFacultyRollback(Student*& student);
        void insertOperationType(int num);
        void updateBSTsFromFile();
        void updateFacultyBST();
        void updateStudentBST();


        // ~ CREATE THESE ~
        GenStack<Student*> *studentRollback = new GenStack<Student*>;
        GenStack<Faculty*> *facultyRollback = new GenStack<Faculty*>;
        GenStack<int> *lastOperation = new GenStack<int>;
       

        // Binary Search Trees
        BST<Student*> *studentTree = new BST<Student*>;
        BST<Faculty*> *facultyTree = new BST<Faculty*>;
};

class FileIO {
    public:
        FileIO(ManageDataBase *manageDataBase);
        ~FileIO();
        void ReadFile();
        void OutFile();

        private:
        ManageDataBase *manageDataBase;
};


