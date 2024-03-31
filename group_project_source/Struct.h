#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

struct Student;
struct Class;
struct schoolYear;
struct Course;
struct Semester;
struct ScoreStu;
struct Student{
    string studentID="";
    int semesterStudied=0;
    string password="";
    string firstName="",lastName="";
    bool femaleGender=0;
    string DD="",MM="",YY="";
    string socialID="";
    double overallGPA=0; //updating overallGPA in student.csv
    ScoreStu* scoreOfStudent=nullptr;
};
struct Class{
    string classID="";
    int yearStudied=0;
    int numStudent=0; //updating number of Student in a class.
    Student* listStudent=nullptr;
};
struct schoolYear{
    string period="";
    int semCount=0; //count the number of semester in a school year.
    Semester *sem=nullptr;
};
struct Course{
    string ID="";
    string courseName="";
    string className="";
    string teacher="";
    string dayoftheWeek="";
    string sessionTime="";
    int numCredits=0;
    int maxStudents=50;
    int numStudents=0;
    Student** listStudentInCourse=nullptr;
};
struct Semester{
    int numSemesterInSchoolYear=0;
    int startDate=0,startMonth=0,startYear=0;
    int endDate=0,endMonth=0,endYear=0;
    int numCourses=0; //update numCourses
    Course *coursesListInSemester=nullptr;
};
struct ScoreStu{
    string courseID="";
    string semester="";
    string year="";
    float quiz=0;
    float mid=0;
    float final=0;
};
#endif // STRUCT_H_INCLUDED
