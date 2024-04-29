#include "Struct.h"
#ifndef STAFF_H_INCLUDED
#define STAFF_H_INCLUDED
struct Staff;
struct Staff{
    int staffID;
    string password;
    string firstName,lastName;
};
schoolYear importSchoolYear(string name); //import schoolyear from the database
Class readClass(string fileName,string nameClass); //import a class from the database
Student *readStudentCSV(string fileName, int& numStu); //import Student CSV, merge from the work of izahai
void updateStudentFromInput(Class &curClass); //import students from the input
void ImportStudentsToCoursesInSemester(Student **students, int numStu, Course thisCourse); //merge from the work of lehoangan02
void importSemesterandCourse(schoolYear &schyrs,Semester &sems,int target);  //import semester and course from the database
void addNewSchoolYear(schoolYear schyrs); //create a new school year
void addStudentintoClass(Class &curClass); //add a student into class
void addCourse(schoolYear &schyrs,Semester &sems); //add a course to the current semester
void removeCourse(schoolYear &schyrs,Semester &sems); //remove a course from the semester
void outputClass(string fileName,Class curClass); //save the class into the database
void outputSemester(schoolYear schyrs, Semester sems);  //save the semester into the database
void outputSchoolYear(schoolYear &schyrs); //save the school year into the database
void outputCourse(string fileName,Course curCourse); //save the course into the database
void outputCourseScoreBoard(schoolYear schyrs, Semester sems, Course curCourse); //import the scoreboard from a database and output to screen
void outputClassResult(Class curClass, Semester sems, schoolYear schyrs); //output class result into the screen
bool checkFormatDayOfTheWeek(string format); //return true if it's in the right format of day of the week
bool checkFormatSession(string format); //return true if it's in the right format of session
#endif // STAFF_H_INCLUDED
