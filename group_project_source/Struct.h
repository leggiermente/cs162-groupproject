#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

struct Student;
struct Class;
struct School_Year;
struct Course;
struct Semester;
struct Student{
    int Student_ID;
    int Semester_Studied;
    string Password;
    string FirstName,LastName;
    bool FemaleGender;
    int DD,MM,YY;
    int Social_ID;
    double overallGPA; //updating overallGPA in student.csv
    Class* ClassofStudent;
};
struct Class{
    string Class_ID;
    int Year_Studied;
    int numStudent; //updating number of Student in a class.
    Student* ListStudent;
};
struct School_Year{
    string Period;
    int ClassCount; //count the number of class in a school year.
    Class* ClassList;
};
struct Course{
    string ID;
    string CourseName;
    string ClassName;
    string Teacher;
    int numCredits;
    int maxStudents=50;
    Student* ListStudentinCourse;
};
struct Semester{
    int NumSemesterInSchoolYear;
    int StartDate,StartMonth,StartYear;
    int EndDate,EndMonth,EndYear;
    Course *CoursesListInSemester;
};
#endif // STRUCT_H_INCLUDED
