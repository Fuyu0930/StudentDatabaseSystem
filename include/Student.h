#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

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
          string GetStudentName();
          int GetStudentRollNum(); // Returns the roll number of the current student
          int GetStudentSocMarks();
          int GetStudentStatMarks();
          int GetStudentMathsMarks();
          int GetStudentEnglishMarks();
          int GetStudentCSMarks();
          double GetStudentPercentage();
          char GetStudentGrade();
          static bool CompareName(Student& a, Student& b);
          static bool CompareRollNum(Student& a, Student& b);
          static bool CompareSocMarks(Student& a, Student& b);
          static bool CompareStatMarks(Student& a, Student& b);
          static bool CompareMathsMarks(Student& a, Student& b);
          static bool CompreEnglishMarks(Student& a, Student& b);
          static bool CompareCSMarks(Student& a, Student& b);
          static bool ComparePercentage(Student& a, Student& b);
          static bool CompareGrade(Student& a, Student& b);
          void ShowStudentRecord(int); // is used to display record of a student with a particular roll number given in function argument
          void WriteStudentRecordInFile(); // Write user input in file student.dat
          void UpdateStudentRecord(int); // accepts roll number and update record of binary file, i.e., student.dat
          void DeleteStudentRecord(int); // DELETES A STUDENT RECORD that belongs to rollno provided by the user from the file student.dat
          void DeleteFromDuplicateFile(int);// deletes record from file DuplicateCheckingFile.txt(that contains only roll no of all students..)
          void ShowResultMenu(); // shows the Result Menu to the user that takes choice from the user to see whether user wants to see class result or individual student result
          void DisplayClassResult(); // displays the result of complete class on the output screen
          string CSVDisplay(); // displays student information in terms of CSV format
          
};

#endif