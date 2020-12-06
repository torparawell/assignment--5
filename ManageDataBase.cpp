#include "Assignment-5.h"

ManageDataBase::ManageDataBase() {
    // Initialize
}

ManageDataBase::~ManageDataBase() {
    // Bye ManageDataBase
}

void ManageDataBase::PromptUser() {
  updateBSTsFromFile();

  ofstream outFileFaculty;
  ofstream outFileStudent;
  outFileFaculty.open("facultyTable.out");
  outFileStudent.open("studentTable.out");
  // Pass the filename as a parameter, then open the file inside the function

  int optionNumber;
  while (optionNumber != 14) {
    cout << "\n1. Print all students and their information (sorted by ascending id #)" << endl;
    cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << "3. Find and display student information given the students id" << endl;
    cout << "4. Find and display faculty information given the faculty id" << endl;
    cout << "5. Given a student’s id, print the name and info of their faculty advisor" << endl;
    cout << "6. Given a faculty id, print ALL the names and info of his/her advisees." << endl;
    cout << "7. Add a new student" << endl;
    cout << "8. Delete a student given the id" << endl;
    cout << "9. Add a new faculty member" << endl;
    cout << "10. Delete a faculty member given the id." << endl;
    cout << "11. Change a student’s advisor given the student id and the new faculty id." << endl;
    cout << "12. Remove an advisee from a faculty member given the ids" << endl;
    cout << "13. Rollback" << endl;
    cout << "14. Exit" << endl;
    // Calculate mean GPA of students.
    // Average number of faculty student advisees
    // Print in decending order.
    // Add names for student's and advisors?

    cout << "Enter Option Number: ";
    cin >> optionNumber;

    if (optionNumber == 1) { //Print students in acending id order
      studentTree->printTree();
    }
    else if (optionNumber == 2) { //Print faculty and their information in ascending id order
      facultyTree->printTree();
    }
    else if (optionNumber == 3) { //Display student information given students id
      PrintStudent();
    }
    else if (optionNumber == 4) { //Displays faculty information given the faculty id
      PrintFacultyMember(false);
    }
    else if (optionNumber == 5) { //Given student id, print name and info of the advisor
      PrintAdvisor();
    }
    else if (optionNumber == 6) { //Given faculty id, print all the names and info of the students
      PrintFacultyMember(true);
    }
    else if (optionNumber == 7) { //Add new student
      CreateStudent();
    }
    else if (optionNumber == 8) { //Deletes a student given an id.
      DeleteStudent();
    }
    else if (optionNumber == 9) { //Creates a faculty member
      CreateFacultyMember();
    }
    else if (optionNumber == 10) { //Deletes a faculty member, if the faculty member had advisees, they need to be reassigned.
      DeleteFaculty();
    }
    else if (optionNumber == 11) { //Change the student's advisor given the students ID and the new advisors ID.
      ChangeAdvisor();
    }
    else if (optionNumber == 12) { //Remove an advisee from a faculty member given the ID
      RemoveAdvisee();
    }
    else if (optionNumber == 13) { //Roll back
      Rollback();
    }
    else if (optionNumber == 14) { //Exit
      facultyTree->printTreeToFile(outFileFaculty);
      studentTree->printTreeToFile(outFileStudent);
    }
  }
}

void ManageDataBase::updateBSTsFromFile(){
  updateFacultyBST();
  updateStudentBST();
}

void ManageDataBase::updateFacultyBST(){
  string line;
  ifstream facultyFile;
  facultyFile.open("facultyTable.out");
  if(facultyFile.is_open()){
    int id;
    int lineCount = 0;
    string level;
    string department;
    bool areMoreAdvisees = false;
    while(getline(facultyFile,line)){
      lineCount++;
      if(line.find("----------") != -1){
        lineCount = 0;
      }
      else if(lineCount == 1)
        id = stoi(line);
      else if(lineCount == 2)
        level = line;
      else if(lineCount == 3){
        department = line;
        Faculty *faculty = new Faculty(id, level, department);
        facultyTree->insertNode(faculty);
      }
      else if(lineCount == 4)
        continue;
      else if(lineCount > 4){
        Faculty *faculty = facultyTree->getNodeById(id);
        faculty->AddAdviseesById(stoi(line));
      }
    }
  }
  else{
    cout << "File facultyTable.out could not be found, proceed with empty faculty tree" << endl;
  }
}

void ManageDataBase::updateStudentBST(){
  string line;
  ifstream studentFile;
  studentFile.open("studentTable.out");
  if(studentFile.is_open()){
    int id;
    int lineCount = 0;
    string level;
    string major;
    double gpa;
    int advisorId;
    while(getline(studentFile,line)){
      lineCount++;
      if(lineCount == 1)
        id = stoi(line);
      else if(lineCount == 2)
        level = line;
      else if(lineCount == 3)
        major = line;
      else if(lineCount == 4)
        gpa = stod(line);
      else if(lineCount == 5){
        advisorId = stoi(line);
        Student *student = new Student(id, level, major, gpa, advisorId);
        studentTree->insertNode(student);
        lineCount = -1;
      }
    }
  }
  else{
    cout << "File studentTable.out could not be found, proceed with empty student tree" << endl;
  }
}

void ManageDataBase::CreateStudent() {
  int id;
  string level;
  string major;
  double gpa;
  int advisorId;

  cout << "Enter student's ID: ";
  cin >> id;
  cout << "Enter student's level: ";
  cin >> level;
  cout << "Enter student's major: ";
  cin >> major;
  cout << "Enter student's GPA: ";
  cin >> gpa;
  cout << "Enter student's advisor ID: ";
  cin >> advisorId;

  if (!facultyTree->searchNodeById(advisorId)) { // Check to see if the advisor exists.  If not then prompt to create an advisor.
    cout << "Error: The advisor does not exist.  Please create the advisor as a faculty member now." << endl;
  }

  Student* student = new Student(id, level, major, gpa, advisorId); //create student and add to student BST
  studentTree->insertNode(student);
  studentRollback->push(student);
  insertOperationType(1);
}

void ManageDataBase::DeleteStudent() {
  int studentId;
  cout << "Enter a student's ID to delete: ";
  cin >> studentId;

  if (studentTree->searchNodeById(studentId)) {
    Student* student = studentTree->getNodeById(studentId);

    if (studentTree->deleteNode(student)) {
      cout << "Student deleted." << endl;
      // Rollback
      studentRollback->push(student);
      insertOperationType(1);
      
    }
  }
  else {
    cout << "Student was not found." << endl;
  }
}

void ManageDataBase::PrintStudent() {
  // Initialize values
  int id;

  // Prompt user
  cout << "Enter student Id: ";
  cin >> id;

  Student* student = studentTree->getNodeById(id);
  student->PrintStats();
}

void ManageDataBase::PrintFacultyMember(bool onlyAdvisees) {
  // Initialize values
  int id;

  // Prompt User
  cout << "Enter Faculty Member Id: ";
  cin >> id;

  Faculty *faculty = facultyTree->getNodeById(id);
  if (onlyAdvisees)
    faculty->PrintFacultyMemberAdvisees();
  else
    faculty->PrintStats();
}

void ManageDataBase::ChangeAdvisor() {
  // Initialize Values
  int studentId;
  int advisorId;

  // Prompt user
  cout << "Enter student Id: ";
  cin >> studentId;

  cout << "Enter new advisors Id: ";
  cin >> advisorId;

  Student* student = studentTree->getNodeById(studentId);
  student->SetAdvisorId(advisorId);
}

void ManageDataBase::CreateFacultyMember() {
  // Faculty Member Private Variables
  int id;
  string level;
  string department;
  int input;

  // Prompt user
  cout << "Enter Faculty Id: ";
  cin >> id;

  cout << "Enter level: ";
  cin >> level;

  cout << "Enter Department: ";
  cin >> department;

  Faculty* faculty = new Faculty(id, level, department);
  faculty->AddAdvisees();
  facultyTree->insertNode(faculty);
  facultyRollback->push(faculty);
  insertOperationType(2);
}

void ManageDataBase::DeleteFaculty() {
  int facultyId;
  int currStudentId;
  GenStack<int> *adviseesToBeReassigned = new GenStack<int>;
  cout << "Enter a Faculty's ID to delete: ";
  cin >> facultyId;

  if (facultyTree->searchNodeById(facultyId)) {
    Faculty* facultyMember = facultyTree->getNodeById(facultyId);

    while (facultyMember->CheckIfThereAreAdvisees()) {
      adviseesToBeReassigned->push(facultyMember->RemoveFrontAdvisee());
    }
    while (!adviseesToBeReassigned->isEmpty()) {
      currStudentId = adviseesToBeReassigned->pop();
      if (studentTree->searchNodeById(currStudentId)) {
        Student* student = studentTree->getNodeById(currStudentId);
        Faculty* newFacultyMember = facultyTree->getRoot();
        student->SetAdvisorId(newFacultyMember->GetId());

        // Rollback
        facultyRollback->push(facultyMember);
        insertOperationType(2);
      }
    }

    if (facultyTree->deleteNode(facultyMember)) {
      cout << "Faculty member deleted." << endl;
    }
  }
  else {
    cout << "Faculty member with id: " << facultyId << " was not found." << endl;
  }
}

void ManageDataBase::PrintAdvisor() {
  // Initialize values
  int studentId;
  int advisorId;

  // Prompt user
  cout << "Enter Student Id: ";
  cin >> studentId;

  // Search to see if the node exists.
  if (studentTree->searchNodeById(studentId)) {
    Student *student = studentTree->getNodeById(studentId);
    advisorId = student->GetAdvisorId();

    Faculty *faculty = facultyTree->getNodeById(advisorId);
    faculty->PrintFacultyMemberAdvisees();
  }
  else {
    cout << "Student with id: " << studentId << " does not exist.  Please try again." << endl;
  }
}

void ManageDataBase::RemoveAdvisee() {
  // Initialize values
  int studentId;
  int advisorId;
  int newAdvisorId;
  int randomFacultyIndex;

  // Prompt user
  cout << "Enter student Id of the advisee you want to remove: ";
  cin >> studentId;

  // Check to see if student exists
  if (studentTree->searchNodeById(studentId)) {
    Student *student = studentTree->getNodeById(studentId);
    advisorId = student->GetAdvisorId();

    Faculty *faculty = facultyTree->getNodeById(advisorId);
    faculty->RemoveAdvisee(studentId);

    cout << "Advisee removed." << endl;
    facultyTree->printTreeId();
    cout << "Enter faculty ID from the ones given above: ";
    cin >> newAdvisorId;
    student->SetAdvisorId(newAdvisorId);
  }
  else {
    cout << "Student that you want to remove does not exist." << endl;
  }
}

void ManageDataBase::insertOperationType(int num) {
  // 1 = student
  // 2 = faculty
  lastOperation->push(num);
}

void ManageDataBase::Rollback(){ //undo the last creation or deletion of a faculty/student
  int lastOperationNum = lastOperation->pop();
  cout << "Rollback initiated." << endl;
  if (lastOperationNum == 1){ //student
    Student *student = studentRollback->pop();
    if (studentTree->searchNodeById(student->GetId())) {
      if (studentTree->deleteNode(student))
        cout << "Removing student from tree." << endl;//student is deleted from the tree.
    }
    else {
      cout << "Adding student back to tree" << endl;
      studentTree->insertNode(student);
    }
  }
  if (lastOperationNum == 2){ //faculty
    Faculty *faculty = facultyRollback->pop();
    if (facultyTree->searchNodeById(faculty->GetId())) {
      if (facultyTree->deleteNode(faculty))
        cout << "Removing faculty from tree." << endl;//stuent deleted
    }
    else {
      cout << "Adding faculty back to tree." << endl;
      facultyTree->insertNode(faculty);
    }
  }
  cout << "Rollback completed." << endl;
}
