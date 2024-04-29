#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

struct Student;
struct Class;
struct schoolYear;
struct Course;
struct Semester;
struct ScoreStu;
struct Student{
    string studentID=""; //ID of the student
    int semesterStudied=0; //number of semester that a student has studied
    string password=""; //password of the student's account
    string firstName="",lastName=""; //name of the student
    bool femaleGender=0; //sexuality of the student
    string DD="",MM="",YY=""; //Birth date.
    string socialID="";
    double overallGPA=0; //updating overallGPA in student.csv
    int numCourses=0; //total number of courses that a student has learned from the 1st year.
    ScoreStu* scoreOfStudent=nullptr; //array saves score of a student
};
struct Class{
    string classID=""; //ID of the class
    int yearStudied=0; //state of the class, 1-st year, 2-nd year,...
    int numStudent=0; //updating number of Student in a class.
    Student* listStudent=nullptr; //list of student in the class
};
struct schoolYear{
    string period=""; //period name of the school year, 2023-2024,...
    int semCount=0; //count the number of semester in a school year.
    Semester *sem=nullptr;
};
struct Course{
    string ID=""; //ID of a course
    string courseName=""; //name of the course
    string className=""; //name for the class
    string teacher=""; //name of the teacher
    string dayoftheWeek=""; //day of the week, followed the format
    string sessionTime=""; //time session, followed the format
    int numCredits=0;
    int maxStudents=50;
    int numStudents=0;
    Student** listStudentInCourse=nullptr; //list of the student studied in this course
};
struct Semester{
    int numSemesterInSchoolYear=0; //number of semester in the school year
    int startDate=0,startMonth=0,startYear=0;
    int endDate=0,endMonth=0,endYear=0;
    int numCourses=0; //number of courses in the semester
    Course *coursesListInSemester=nullptr; //list of all courses in the semester
};
struct ScoreStu{
    string courseID="";
    string semester="";
    string year="";
    float quiz=0; //point of quiz, mid, final, total
    float mid=0;
    float fin=0;
    float total=0;
};
#endif // STRUCT_H_INCLUDED
