#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#include <string>
using namespace std;


struct Class;
struct SchoolYear;
struct Course;
struct Semester;
struct Student;
struct ScoreStu;
struct rowStuUI;
struct Class {
    string classID = "";
    int yearStudied = 0;
    int numStudent = 0; //updating number of Student in a class.
    Student* listStudent = nullptr;
};
struct SchoolYear {
    string period = "";
    //int classCount = 0; //count the number of class in a school year.
    //Class* classList;
    int numSemester = 0;
    Semester* listSemester = nullptr;
};
struct Course {
    string ID = "";
    string courseName = "";
    string className = "";
    string teacher = "";
    string dayOfWeek = "";
    string session = "";
    int numCredits = 0; 
    int maxStudents = 50; 
    int currStudents = 0;
    ScoreStu* listStudent = nullptr;
};

struct Semester {
    int numSemesterInSchoolYear = 0;
    string startDate = "";
    string endDate = "";
    int numCourses = 0;
    Course* coursesListInSemester = nullptr;
};
struct Student {
    string studentID = "";
    string firstName = "", lastName = "";
    bool femaleGender = false;
    string dob = "";
    string socialID = "";
    string password = "";
    double overallGPA = 0;
    int semesterStudied = 0;
    ScoreStu* score = nullptr;
    //Course* courseOfStudent = nullptr;
};

// Temeporary struct for Score
struct ScoreStu {
    int No;
    string ID;
    string firstName;
    string lastName;
    float quiz;
    float mid;
    float final;
    float other;
    bool isInClass = 0;
};

#endif // STRUCT_H_INCLUDED