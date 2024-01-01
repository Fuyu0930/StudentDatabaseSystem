#include <iostream>
#include <fstream>
#include <iomanip> // supports setw function that is used to give spaces on the output screen

using namespace std;

int rollNumToBeUpdated = 0;

// Create student class for the system
class Student {
     private:
          char studentName[50];
          int rollNum;
          int socialStudiesMarks, statMarks, mathsMarks, englishMarks, computerMarks;
          double studentPercentage;
          char studentGrade;
          // flag = false: when input roll number does not exist in file student.dat
          // flag = true: when input roll number exists in file student.dat
          bool flag;
          void CalculateGrade();
          
     public:
          Student();
          void GetData();
          void CheckForDuplicationInFile();
          void ShowData();
          void TabularDisplay(); // Used to display the result of all students in the form of a table
          int GetStudentRollNum(); // Returns the roll number of the current student
          void ShowStudentRecord(int); // is used to display record of a student with a particular roll number given in function argument
          void WriteStudentRecordInFile(); // Write user input in file student.dat
          void UpdateStudentRecord(int); // accepts roll number and update record of binary file, i.e., student.dat
          void DeleteStudentRecord(int); // DELETES A STUDENT RECORD that belongs to rollno provided by the user from the file student.dat
          void DeleteFromDuplicateFile(int);// deletes record from file DuplicateCheckingFile.txt(that contains only roll no of all students..)
          void ShowResultMenu(); // shows the Result Menu to the user that takes choice from the user to see whether user wants to see class result or individual student result
          void DisplayClassResult(); // displays the result of complete class on the output screen

};

void intro();
void pause();
void EntryMenu();
void DisplayAll();

int main() {
     char ch;
     Student student;
     cout.setf(ios::fixed | ios::showpoint);
     cout << setprecision(2); // 88.98989 => 88.98
     intro();
     do {
          system("clear");
          intro();
          cout << "\n\n\n\t\t\t\tHOME SCREEN\n\n\n";
          cout << "\n\n\t1. Result Calculation System";
          cout << "\n\n\t2. Student Database Management System";
          cout << "\n\n\t3. Exit";
          cout << "\n\n\n\n\nPlease Select Your Option (1-3): ";
          cin >> ch;
          switch(ch) {
               case '1':
                    //shows Result Calculation System
                    student.ShowResultMenu();
                    break;
               case '2':
                    //shows student database management system code
                    EntryMenu();
                    break;
               case '3':
                    // use wants to exit the system
                    break;
               default: cout << "\a";
          }
     } while (ch != '3');
    
     cout << "\nYou exit the home page.";
     pause();

     return 0;
}

void intro() {
     cout << "\n\n\n**** WELCOME TO STUDENT DATABASE MANAGEMENT AND RESULT CALCULATION SYSTEM ****\n\n";
}

void pause() {
     cout << "\nPress any key to exit ";
     cin.ignore();
     std::getchar();
}

void EntryMenu() {
     //1. Variables declaration
     char input;
     int num; // get the input from the user
     Student student;
     system("clear");

     //2. Print the menu on the output screen
     cout << "\n\n\n\t\t\tSTUDENT DATABASE MANAGEMENT MENU";
     cout << "\n\n\t1. CREATE STUDENT RECORD";
     cout << "\n\n\t2. SHOW RECORDS OF ALL STUDENTS";
     cout << "\n\n\t3. SEARCH STUDENT RECORD";
     cout << "\n\n\t4. UPDATE STUDENT RECORD";
     cout << "\n\n\t5. DELETE STUDENT RECORD";
     cout << "\n\n\t6. BACK TO HOME SCREEN";
     cout << "\n\n\n\n\tPlease Enter Your Choice (1-6): ";

     //3. Take input from user that are numbers from 1 - 6
     cin >> input;
     system("clear");

     //4. Add switch and add 6 cases in the switch
     switch(input) {
          case '1':
               // Create student record
               student.WriteStudentRecordInFile();
               break;
          case '2':
               // Show records of all students in the file
               DisplayAll(); // It is showing records of all students in the file
               break;
          case '3':
               // Searching a record of a student
               cout << "\n\n\t Please Enter the Roll Number: ";
               cin >> num; // We are receiving roll number from the system user
               student.ShowStudentRecord(num);
               break;
          case '4':
               // Updating student's record
               // Searching a record of a student
               cout << "\n\n\t Please Enter the Roll Number: ";
               cin >> num; // We are receiving roll number from the system user
               student.UpdateStudentRecord(num);
               break;
          case '5': 
               // Delete student's record
               cout << "\n\n\t Please Enter the Roll Number: ";
               cin >> num;
               student.DeleteStudentRecord(num);
               break;
          case '6':
               // Go back to the home screen
               break;
          default: 
               cout << "\a";
               EntryMenu();
     }
}

void DisplayAll() {
     // 1. Declare variables
     Student student;
     ifstream inFile;

     // 2. Open the file
     inFile.open("student.dat", ios::binary);

     // 3. If file did not open, print error message and return function using return statement
     if (!inFile) {
          cout << "File could not be opened!! Press any key ...";
          cin.ignore();
          cin.get();
          return;
     }
     
     // 4. If file opens, read records one by one and call ShowData() for each one
     cout << "\n\n\n\n\t\tDISPLAY ALL RECORDs \n\n";
     while (inFile.read(reinterpret_cast<char *> (&student), sizeof(Student))) {
          student.ShowData(); // ShowData is executed for each record of student in the file
     }

     // 5 Close file using object & clear input buffers
     inFile.close();
     cin.ignore();
     cin.get();
     return;
}


/* **************** The Student Class **************** */
// Constructor
Student::Student() {
     // creating student.dat
     ofstream outFile("student.dat", ios::binary | ios::app); // creating ofstream object and creating file student.dat
     outFile.close();

     // creating DuplicateCheckingFile.txt
     ofstream outDFile("DuplicateCheckingFile.txt", ios::app);
     outDFile.close();
}

void Student::GetData() {
     // Takes input as student data from user
     flag = false;
     cout << "\nEnter the roll number of the student: ";
     cin >> rollNum;

     // Here we will check for duplication in txt file
     if (rollNumToBeUpdated != rollNum) {
          CheckForDuplicationInFile();
     }
     
     if (flag == true) {
          cout << "Error duplicate record" << endl;
          return; // function returns
     }

     // if flag == false, then we will ask user to enter the remaining data of the student
     cout << "\n\nEnter the Name of student: ";
     cin.ignore();
     cin.getline(studentName, 50);
     cout << "Enter the marks in Social studies out of 100: ";
     cin >> socialStudiesMarks;
     cout << "Enter the marks in Statistics out of 100: ";
     cin >> statMarks;
     cout << "Enter the marks in Maths out of 100: ";
     cin >> mathsMarks;
     cout << "Enter the marks in English out of 100: ";
     cin >> englishMarks;
     cout << "Enter the marks in Computer out of 100: ";
     cin >> computerMarks;
     CalculateGrade();
}

void Student::CheckForDuplicationInFile() {
     // Open file DuplicateCheckingFile.txt
     // Compare the roll number that user entered with all roll number of file .txt
     // if found, make flag = true, otherwise flag = false

     int currentRollNum = 0;
     flag = false;
     ifstream infile("DuplicateCheckingFile.txt");

     while (!infile.eof()) {
          infile >> currentRollNum;
          if (currentRollNum == rollNum) {
               flag = true;
          }
         
     }
     infile.close();
     if (flag == false) {
          // We are writing the roll number in DuplicateCheckingFile.txt
          ofstream outfile("DuplicateCheckingFile.txt", ios::app);
          outfile << "\n" << rollNum;
          outfile.close();
     }
}

void Student::ShowData() {
     cout << "\nRoll Number of student: " << rollNum;
     cout << "\nName of student: " << studentName;
     cout << "\nMarks in Social Studies: " << socialStudiesMarks;
     cout << "\nMarks in Statistics: " << statMarks;
     cout << "\nMarks in Maths: " << mathsMarks;
     cout << "\nMarks in English: " << englishMarks;
     cout << "\nMarks in Computer: " << computerMarks;
     cout << "\nPercentage of student: " << studentPercentage;
     cout << "\nGrade of student: " << studentGrade;
     cout << "\n***************************************************";
}

void Student::CalculateGrade() {
     studentPercentage =  (socialStudiesMarks + statMarks + mathsMarks + englishMarks + computerMarks) / 5.0;
     if (studentPercentage >= 80) {
          studentGrade = 'A';
     } else if (studentPercentage >= 70 && studentPercentage < 80) {
          studentGrade = 'B';
     } else if (studentPercentage >= 60 && studentPercentage < 70) {
          studentGrade = 'C';
     } else if (studentPercentage < 60) {
          studentGrade = 'F';
     }
}

void Student::TabularDisplay() {
      // setw(4): give the 4 spaces
     cout << rollNum << setw(4) << " " << studentName << setw(20-strlen(studentName)) << socialStudiesMarks << setw(6) << statMarks << setw(6) << mathsMarks << setw(6) << englishMarks << setw(6) << computerMarks << setw(8) << studentPercentage << setw(8) << studentGrade << endl;
}

int Student::GetStudentRollNum() {
     return rollNum;
}

void Student::ShowStudentRecord(int target) {
     ifstream inFile;
     inFile.open("student.dat", ios::binary);

     if (!inFile) {
          cout << "File could not be opended!! Press any key to continue";
          cin.ignore();
          cin.get();
          return;
     }

     bool flag = false; // Use it as an indicator to know whether that roll number is found in the file or not
     // Now here will take the roll number and find student record in the file "student.dat"

     while (inFile.read(reinterpret_cast<char *> (this), sizeof(Student))) {
          if (GetStudentRollNum() == target) {
               // the target roll number is found in the file student.dat
               ShowData(); // prints record of current student
               flag = true; // record is found in the file student.dat
          }
     }

     inFile.close();
     if (flag == false) {
          cout << "\n\nRecord does not exist";
     }
     cin.ignore();
     cin.get();
}

void Student::WriteStudentRecordInFile() {
     // 1. Open the file student.dat
     ofstream outFile;
     outFile.open("student.dat", ios::binary | ios::app);
     GetData();

     // 2. if flag = false (no duplication of roll number) -> enter record
     if (flag == false) {
          // Write record in file student.dat
          outFile.write(reinterpret_cast<char *>(this), sizeof(Student));
          cout << "\n\nStudent Record Has Been Created!";
     }

     // 3. if flag = true, print error
     if (flag == true) {
          cout << "Record Not Created Due To Duplication";
     }

     // 4. close file
     outFile.close();
     cin.ignore();
     cin.get();

}

void Student::UpdateStudentRecord(int num) {
     // 1. Declare variables
     // true when num is found in the file; false when num is not found in the file
     rollNumToBeUpdated = num;
     bool found = false;
     fstream File;

     // 2. Open file student.dat
     File.open("student.dat", ios::binary | ios::in | ios::out); // reading and writing
     if (!File) {
          cout << "File could not be open!! Press any key...";
          cin.ignore();
          cin.get();
          return;
     }

     // 3. if file opens -> reach each record one by one till we reach to the record of the student having roll number
          // 1) Print student record on the output screen using ShowData() function
          // 2) Take input (student record) from user with changes in it using GetData()
          // 3) If flag == false (means no duplication of roll number exists), write the updated or changed record of student in the file
     while (!File.eof() && found == false) {
          File.read(reinterpret_cast<char *>(this), sizeof(Student));
          if (GetStudentRollNum() == num) {
               ShowData();
               cout << "\n\nPlease Enter the New Details of Student" << endl;
               GetData();
               if (flag == false) { // no duplication
                    int pos = (-1) * static_cast<int>(sizeof(*this));
                    File.seekp(pos, ios::cur);
                    File.write(reinterpret_cast<char *>(this), sizeof(Student));
               }
               found = true;
          }
          if (flag == true) {
               cout << "Could not update because this Roll Number already exists.";
          }
     }

     File.close();
     if (found == false) {
          cout << "\n\nRecord  Not Found";
     }

     cin.ignore();
     cin.get();
     
     if (flag == false && found == true && rollNumToBeUpdated != rollNum){
          DeleteFromDuplicateFile(num);
     }
     rollNumToBeUpdated = 0;
}

void Student::DeleteStudentRecord(int num) {
     // 1. Declare variable
     ifstream inFile;
     
     // 2. Open file     
     inFile.open("student.dat", ios::binary);

     // If file does not open, print error
     if (!inFile) {
          cout << "\nFile could not be opened... Press any key";
          cin.ignore();
          cin.get();
          return;
     }

     // If file opens
     ofstream outFile;
     outFile.open("Temp.dat", ios::out);
     inFile.seekg(0, ios::beg); // place the file pointer in the beginning

     // 1) Create and open another file temp.dat while reading each record of student.dat
     while (inFile.read(reinterpret_cast<char*> (this), sizeof(Student))) {
          if (GetStudentRollNum() != num) {
               // 2) Copy records to temp.dat except the one we wanted to delete 
               outFile.write(reinterpret_cast<char*> (this), sizeof(Student));
          }
     }

     // 3) Close both files
     outFile.close();
     inFile.close();

     // Remove student.dat, and rename temp.dat as student.dat
     remove("student.dat");
     rename("temp.dat", "student.dat");
     cout << "\n\nRecord deleted... Press any key";

     // 3. Call function DeleteFromDuplicateFile to delte user's record from file DuplicateCheckingFile.txt
     DeleteFromDuplicateFile(num);
}

void Student::DeleteFromDuplicateFile(int rollNumOfRecord) {
     // 1. Open files DuplicateCheckingFile.txt and tempory file tempFile.txt
     int currentRollNum;
     ifstream inFile("DuplicateCheckingFile.txt");
     ofstream outFile("TempFile.txt");
     inFile.seekg(0, ios::beg); // put the pointer in the starting position

     // 2. Copy contents of DuplicateCheckingFile.txt in temp file except the roll number of record to be deleted that was the target
     while (!inFile.eof()) {
          inFile >> currentRollNum;
          if (currentRollNum != rollNumOfRecord) {
               outFile << "\n" << currentRollNum;
          }
     }

     // 3. Close both files
     inFile.close();
     outFile.close();

     // 4. Remove DuplicateCheckingFile.txt
     remove("DuplicateCheckingFile.txt");

     // 5. Rename tempFile.txt as DuplicateCheckingFile.txt to make it DuplicateCheckingFile.txt
     rename("TempFile.txt", "DuplicateCheckingFile.txt");

     // 6. Clear input buffers
     cin.ignore();
     cin.get();
}

void Student::ShowResultMenu() {
     // 1. Declare variable and clear screen
     char input;
     int rollInput;
     system("clear");

     // 2. Print menu using cout
     cout << "\n\n\n\tRESULT MENU";
     cout << "\n\n\n\t1. Class Result";
     cout << "\n\n\n\t2. Student Report Card";
     cout << "\n\n\n\t3. Back to Main Menu";
     cout << "\n\n\n\tEnter Choice (1/2/3): ";
     cin >> input;
     system("clear");

     // 3. Add switch to add code to the options provided by the menu
     switch(input) {
          case '1':
               DisplayClassResult();
               break;
          case '2':
               cout << "\n\n\tEnter the Roll Number of the Student: ";
               cin >> rollInput;
               ShowStudentRecord(rollInput);
               break;
          case '3':
               break;
          default:
               cout << "\a";
     }
}

void Student::DisplayClassResult() {
     // 1. Opens file student.dat
     ifstream inFile;
     inFile.open("student.dat", ios::binary);

     // 2. If file does not open, print error message
     if (!inFile) {
          cout << "File could not be opened... Press any key";
          cin.ignore();
          cin.get();
          return;
     }

     // 3. If file opens:

     // 3.1 system will give heading of class result on output screen
     cout << "\n\n\t\tALL CLASS RESULT \n\n";
     cout << "=========================================================================\n";
     cout << "R.No          Name          Soc  Stats  M     E       CS    %age    Grade" << endl;
     cout << "=========================================================================\n";

     // 3.2 Use a while loop and it will run as long as it is reading records from the file student.dat
     while (inFile.read(reinterpret_cast<char*>(this), sizeof(Student))) {
          // Inside the loop, call the function Tabular Display that prints student's data on the screen
          TabularDisplay();
     }    
     
     // 4. Close file
     inFile.close();

     // 5. Clear input buffer
     cin.ignore();
     cin.get();
}