#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#include <string>
using namespace std;

struct GPA {
    string year = "";
    float gpaS[4] = {-1};
};
struct ScoreStu {
    string year = "";
    string semester = "";
    string courseID = "";
    float totalSc = -1;
    float finalSc = -1;
    float midSc = -1;
    float otherSc = -1;
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
    string year;
    string semester;
    string ID = "";
    string courseName = "";
    string className = "";
    string teacher = "";
    string dayOfWeek = "";
    string session = "";
    int numCredits = 0;
    int maxStudents = 50;
    int currStudents = 0;
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
    string firstName = "", lastName = "";
    bool femaleGender = false;
    string dob = "";
    string socialID = "";
    string password = "";
    float overallGPA = 0;
    GPA gpaList[4];
    ScoreStu* scoreList = nullptr;
    int numCourse = 0;
};
#endif // STRUCT_H_INCLUDED

