#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#include <string>
using namespace std;
struct Student;
struct Class;
struct schoolYear;
struct Course;
struct Semester;
struct Student{
    int studentID=0;
    int semesterStudied=0;
    string password="";
    string firstName="",lastName="";
    bool femaleGender=0;
    int DD=0,MM=0,YY=0;
    int socialID=0;
    double overallGPA=0; //updating overallGPA in student.csv
    Class* classOfStudent;
};
struct Class{
    string classID="";
    int yearStudied=0;
    int numStudent=0; //updating number of Student in a class.
    Student* listStudent;
};
struct schoolYear{
    string period="";
    int classCount=0; //count the number of class in a school year.
    Class* classList;
};
struct Course{
    string ID="";
    string courseName="";
    string className="";
    string teacher="";
    int numCredits=0;
    int maxStudents=50;
    int numStu = 0;
    Student* listStudentInCourse;
};
struct Semester{
    int numSemesterInSchoolYear=0;
    int startDate=0,startMonth=0,startYear=0;
    int endDate=0,endMonth=0,endYear=0;
    Course *coursesListInSemester;
};
#endif // STRUCT_H_INCLUDED
