#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#include <string>
using namespace std;

// Temeporary struct for Score
struct ScoreStu {
    string courseID;
    string semester;
    string year;
    float quiz;
    float mid;
    float final;
};
struct Class;
struct SchoolYear;
struct Course;
struct Semester;
struct Student;
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
    int currStudents = 43;
    Student** listStudentInCourse = nullptr;
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
    int semesterStudied = 0;
    string password = "";
    string firstName = "", lastName = "";
    bool femaleGender = 0;
    string dob = "";
    //int DD = 0, MM = 0, YY = 0;
    string socialID = "";
    double overallGPA = 0; //updating overallGPA in student.csv
    ScoreStu* score = nullptr;
    Course* courseOfStudent = nullptr;
};

#endif // STRUCT_H_INCLUDED
