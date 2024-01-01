#include <iostream>
#include <fstream>
#include <iomanip> // supports setw function that is used to give spaces on the output screen

#include "Student.h"

using namespace std;

// Create student class for the system


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