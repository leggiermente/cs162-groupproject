#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
//struct Course{
//    string ID;
//    string CourseName;
//    string ClassName;
//    string Teacher;
//    int numCredits;
//    int maxStudents=50;
//};
//struct Semester{
//    int NumSemesterInSchoolYear;
//    int StartDate,StartMonth,StartYear;
//    int EndDate,EndMonth,EndYear;
//    Course *CoursesListInSemester;
//};
struct Student;
struct Class;
struct School_Year;
struct Student{
    int Student_ID;
    int Year_Studied;
    string Password;
    string FirstName,LastName;
    bool FemaleGender;
    int DD,MM,YY;
    int Social_ID;
    Class* ClassofStudent;
};
struct Class{
    string Class_ID;
    int Year_Studied;
    Student* ListStudent;
};
struct School_Year{
    string Period;
    Class* ClassList;
    //Semester SemesterInSchoolYear[3];
};
#endif // STUDENT_H_INCLUDED
