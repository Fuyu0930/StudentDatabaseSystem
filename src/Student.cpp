#include "Student.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

// Set up the global variable
int rollNumToBeUpdated = 0;
vector<Student> studentList;

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

int Student::GetStudentRollNum() {
     return rollNum;
}

string Student::GetStudentName() {
     return string(studentName);
}

int Student::GetStudentSocMarks() {
     return socialStudiesMarks;
}

int Student::GetStudentStatMarks() {
     return statMarks;
}

int Student::GetStudentMathsMarks() {
     return mathsMarks;
}

int Student::GetStudentEnglishMarks() {
     return englishMarks;
}

int Student::GetStudentCSMarks() {
     return computerMarks;
}

double Student::GetStudentPercentage() {
     return studentPercentage;
}

char Student::GetStudentGrade() {
     return studentGrade;
}

bool Student::CompareName(Student& a, Student& b) {
     return a.GetStudentName() <= b.GetStudentName();
}

bool Student::CompareRollNum(Student& a, Student& b) {
     return a.GetStudentRollNum() <= b.GetStudentRollNum();
}

bool Student::CompareSocMarks(Student& a, Student& b) {
     return a.GetStudentSocMarks() >= b.GetStudentSocMarks();
}

bool Student::CompareStatMarks(Student& a, Student& b) {
     return a.GetStudentStatMarks() >= b.GetStudentStatMarks();
}

bool Student::CompareMathsMarks(Student& a, Student& b) {
     return a.GetStudentMathsMarks() >= b.GetStudentMathsMarks();
}

bool Student::CompreEnglishMarks(Student& a, Student& b) {
     return a.GetStudentEnglishMarks() >= b.GetStudentEnglishMarks();
}

bool Student::CompareCSMarks(Student& a, Student& b) {
     return a.GetStudentCSMarks() >= b.GetStudentCSMarks();
}

bool Student::ComparePercentage(Student& a, Student& b) {
     return a.GetStudentPercentage() >= b.GetStudentPercentage();
}

bool Student::CompareGrade(Student& a, Student& b) {
     return a.GetStudentGrade() >= b.GetStudentGrade();
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
                    cout << "\nUpdate is complete. Press the ENTER key to exit.";
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
     // 0. Declare variables
     char userInput;

     do {
          system("clear");
          // 1. Opens file student.dat
          ifstream inFile;
          inFile.open("student.dat", ios::binary);

          // 2. If file does not open, print error message
          if (!inFile) {
               cout << "File could not be opened... Press any key ";
               cin.ignore();
               cin.get();
               return;
          }

          // 3. If file opens:          

          // Use a while loop and it will run as long as it is reading records from the file student.dat
          if (studentList.empty()) {
               while (inFile.read(reinterpret_cast<char*>(this), sizeof(Student))) {
                    studentList.push_back(*this); // Adds a copy of the current object
               }    
          }
          
          // 4. Close file
          inFile.close();

          // 5. Show the Header and Tabular display
          cout << "\n\n\t\tALL CLASS RESULT \n\n";
          cout << "=========================================================================\n";
          cout << "R.No          Name          Soc  Stats  M     E       CS    %age    Grade" << endl;
          cout << "=========================================================================\n";
          for (int i = 0; i < studentList.size(); i++) {
               studentList[i].TabularDisplay();
          }

          // 5. Clear input buffer
          cout << "\nPress 1 to export the CSV file.";
          cout << "\nPress 2 to sort by Student Name";
          cout << "\nPress 3 to sort by Roll Number";
          cout << "\nPress 4 to sort by Social Study Marks";
          cout << "\nPress 5 to sort by Statistics Marks";
          cout << "\nPress 6 to sort by Maths Marks";
          cout << "\nPress 7 to sort by English Marks";
          cout << "\nPress 8 to sort by Computer Science Marks";
          cout << "\nPress 9 to sort by Overall Percentage";
          cout << "\nPress a to sort by Overall Grade";
          cout << "\nPress b to exit";
          cout << "\nPlease enter your option: ";
          cin >> userInput;

          switch(userInput) {
               case '1':
                    system("clear");
                    ExportResultCSV(studentList);
                    studentList.clear();
                    break;
               case '2':
                    sort(studentList.begin(), studentList.end(), CompareName);
                    continue;
               case '3':
                    sort(studentList.begin(), studentList.end(), CompareRollNum);
                    continue;
               case '4':
                    sort(studentList.begin(), studentList.end(), CompareSocMarks);
                    continue;
               case '5':
                    sort(studentList.begin(), studentList.end(), CompareStatMarks);
                    continue;
               case '6':
                    sort(studentList.begin(), studentList.end(), CompareMathsMarks);
                    continue;
               case '7':
                    sort(studentList.begin(), studentList.end(), CompreEnglishMarks);
                    continue;
               case '8':
                    sort(studentList.begin(), studentList.end(), CompareCSMarks);
                    continue;
               case '9':
                    sort(studentList.begin(), studentList.end(), ComparePercentage);
                    continue;
               case 'a':
                    sort(studentList.begin(), studentList.end(), CompareGrade);
                    continue;
               case 'b':
                    studentList.clear();
                    continue;
               default:
                    cout << '\a';
          }
     } while (userInput != '1' && userInput != 'b');
     
}

string Student::CSVDisplay() {
      string rollNumStr = to_string(rollNum);
      string socialStudiesStr = to_string(socialStudiesMarks);
      string statStr = to_string(statMarks);
      string mathsStr = to_string(mathsMarks);
      string englishStr = to_string(englishMarks);
      string computerStr = to_string(computerMarks);
      string percentageStr = to_string(studentPercentage);
      return rollNumStr + ", " + studentName + ", " + socialStudiesStr + ", " + statStr + ", " + mathsStr + ", " + englishStr + ", " + computerStr + ", " + percentageStr + ", " + studentGrade + ",\n";
}

