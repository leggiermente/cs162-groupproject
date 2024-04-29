#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#include "Staff.h"
#include "Struct.h"
#include "Student.h"
schoolYear importSchoolYear(string name){ //import schoolyear from the database
    schoolYear schyrs;
    ifstream inp;
    inp.open("database/schoolyear/"+name+".txt"); //open the data of the class in the school year.
    if (!inp.is_open()){
        inp.close();
        return {}; //there's no data of the current school year that needs to make new school year.
    }
    string str; //string for getting the input file, needs to also implement schoolyear.txt, involving name of the class of the last school year.
    getline(inp,str); // getting the period of the school year
    schyrs.period=str;
    inp >> schyrs.semCount;
    inp.close();
    return schyrs;
}
Class readClass(string fileName,string nameClass){ //import a class from the database
    ifstream inp;
    string str;
    inp.open(fileName);
    Class *tmpClass=new Class; //class file format
    tmpClass->classID=nameClass;
    inp >> tmpClass->yearStudied; //year studied in this class
    inp >> tmpClass->numStudent; //number of students in this class
    if (tmpClass->numStudent>0) tmpClass->listStudent=new Student[tmpClass->numStudent];
    else tmpClass->listStudent=nullptr;
    inp.get();
    for (int i=0;i<tmpClass->numStudent;i++){
        getline(inp,str,','); //in each line
        tmpClass->listStudent[i].studentID=str; //student id, first name, last name, sexuality, dob, social id
        getline(inp,str,',');
        tmpClass->listStudent[i].firstName=str;
        getline(inp,str,',');
        tmpClass->listStudent[i].lastName=str;
        getline(inp,str,',');
        tmpClass->listStudent[i].femaleGender=stoi(str);
        getline(inp,str,',');
        tmpClass->listStudent[i].DD=str;
        getline(inp,str,',');
        tmpClass->listStudent[i].MM=str;
        getline(inp,str,',');
        tmpClass->listStudent[i].YY=str;
        getline(inp,str,'\n');
        tmpClass->listStudent[i].socialID=str;
    }
    inp.close();
    return *tmpClass;
}
Student *readStudentCSV(string fileName, int& numStu){//import Student CSV, merge from the work of izahai

}
void updateStudentFromInput(Class &curClass){ //import students from the input
    system("CLS");
    string str;
    cout << "Please input number of students: ";
    cin >> curClass.numStudent;
    cin.get();
    curClass.listStudent=new Student[curClass.numStudent];
    for (int i=0;i<curClass.numStudent;i++){ //in each line
        system("CLS");
        cout << "Please input student ID of student " << i+1 << ": ";
        getline(cin,str);
        curClass.listStudent[i].studentID=str; //student id, first name, last name, sexuality, dob, social id
        cout << "Please input first name of student " << i+1 << ": ";
        getline(cin,str);
        curClass.listStudent[i].firstName=str;
        cout << "Please input last name of student " << i+1 << ": ";
        getline(cin,str);
        curClass.listStudent[i].lastName=str;
        cout << "Please input state of gender of student " << i+1 << " (1 for female, 0 for male): ";
        getline(cin,str);
        curClass.listStudent[i].femaleGender=stoi(str);
        cout << "Please input day of birth of student " << i+1 << ": ";
        getline(cin,str);
        curClass.listStudent[i].DD=str;
        cout << "Please input month of birth of student " << i+1 << ": ";
        getline(cin,str);
        curClass.listStudent[i].MM=str;
        cout << "Please input year of birth of student " << i+1 << ": ";
        getline(cin,str);
        curClass.listStudent[i].YY=str;
        cout << "Please input social ID of student " << i+1 << ": ";
        getline(cin,str);
        curClass.listStudent[i].socialID=str;
    }
}
void ImportStudentsToCoursesInSemester(Student **students, int numStu, Course thisCourse){ //merge from the work of lehoangan02

}
void addNewSchoolYear(schoolYear schyrs){ //create a new school year
    system("CLS");
    cout << "Please input the period of the new school year below: " << endl;
    getline(cin,schyrs.period);
    outputSchoolYear(schyrs);
    system("CLS");
}
void addStudentintoClass(Class &curClass){ //add a student into class
    system("CLS");
    if (curClass.yearStudied!=1){ //check if there are 1-st year classes to add
        cout << "The class is not 1-st year to add new student." << endl;
        Sleep(3000);
        return;
    }
    system("CLS");
    cout << "Please choose an option for updating new student to the class." << endl;
    int options=0; //variable to check for the option
    cout << "1: Input students directly." << endl;
    cout << "2: Input students from file student.csv (import from /import/student.csv)" << endl;
    do{
        cin >> options;
        if (options!=1 && options!=2){
            cout << "Please input again in this line: ";
        }
    }
    while (options!=1 && options!=2);
    if (options==1){
        updateStudentFromInput(curClass); //implement from above function
    }
    else{
        cout << "Please choose the directory for the import file student.csv";
        string str;
        getline(cin,str);
        curClass.listStudent=readStudentCSV(str+"student.csv", curClass.numStudent); //import from CSV, work of izahai
    }
    outputClass("database/class/"+curClass.classID+".txt",curClass);
}
void importSemesterandCourse(schoolYear &schyrs,Semester &sems,int target){ //import semester and course from the function
    ifstream inp;
    inp.open("database/semester/"+schyrs.period+"_"+to_string(target)+".txt");
    for (int i=0;i<sems.numCourses;i++){ //delete pointer section
        for (int j=0;j<sems.coursesListInSemester[i].numStudents;j++){
            delete []sems.coursesListInSemester[i].listStudentInCourse[j]->scoreOfStudent;
            delete []sems.coursesListInSemester[i].listStudentInCourse;
        }
    }
    delete []sems.coursesListInSemester;
    inp >> sems.numSemesterInSchoolYear; //import semester data
    inp >> sems.startDate >> sems.startMonth >> sems.startYear;
    inp >> sems.endDate >> sems.endMonth >> sems.endYear;
    inp >> sems.numCourses;
    inp.get();
    sems.coursesListInSemester=new Course[sems.numCourses];
    for (int i=0;i<sems.numCourses;i++){
        getline(inp,sems.coursesListInSemester[i].ID);
    }
    inp.close();
    for (int i=0;i<sems.numCourses;i++){
        inp.open("database/course/"+sems.coursesListInSemester[i].ID+".txt"); //import each course from the semester
        getline(inp,sems.coursesListInSemester[i].ID);
        getline(inp,sems.coursesListInSemester[i].courseName);
        getline(inp,sems.coursesListInSemester[i].className);
        getline(inp,sems.coursesListInSemester[i].teacher);
        inp >> sems.coursesListInSemester[i].numCredits;
        inp >> sems.coursesListInSemester[i].maxStudents;
        inp.get();
        getline(inp,sems.coursesListInSemester[i].dayoftheWeek);
        getline(inp,sems.coursesListInSemester[i].sessionTime);
        inp >> sems.coursesListInSemester[i].numStudents;
        inp.get();
        int numStu=sems.coursesListInSemester[i].numStudents;
        sems.coursesListInSemester[i].listStudentInCourse=new Student* [numStu];
        for (int j=0;j<sems.coursesListInSemester[i].numStudents;j++){ //import each student from each course
            sems.coursesListInSemester[i].listStudentInCourse[j]=new Student;
            getline(inp,sems.coursesListInSemester[i].listStudentInCourse[j]->studentID);
        }
        inp.close();
    }
}
void addCourse(schoolYear &schyrs,Semester &sems){ //add a course to the current semester
    Course* tmp=sems.coursesListInSemester;
    sems.numCourses++;
    sems.coursesListInSemester=new Course[sems.numCourses]; //update the size of dynamic allocated array to add a new course
    for (int i=0;i<sems.numCourses-1;i++){
        sems.coursesListInSemester[i]=tmp[i];
    }
    int curPos=sems.numCourses-1;
    cout << "Please input the course id: "; //input information of a course
    getline(cin,sems.coursesListInSemester[curPos].ID);
    cout << "Please input the course name: ";
    getline(cin,sems.coursesListInSemester[curPos].courseName);
    cout << "Please input the class name: ";
    getline(cin,sems.coursesListInSemester[curPos].className);
    cout << "Please input the teacher name: ";
    getline(cin,sems.coursesListInSemester[curPos].teacher);
    cout << "Please input the number of credits in this course: ";
    cin >> sems.coursesListInSemester[curPos].numCredits;
    cout << "Please input the maximum of students in the class (default is 50): ";
    cin >> sems.coursesListInSemester[curPos].maxStudents;
    cin.get();
    cout << "Please input day of the week, following format (can be uppercase and lowercase): " << endl; //day of the week process
    cout << "MON | TUE | WED | THU | FRI | SAT" << endl;
    while (getline(cin,sems.coursesListInSemester[curPos].dayoftheWeek) && //check if valid input
           !checkFormatDayOfTheWeek(sems.coursesListInSemester[curPos].dayoftheWeek)){
        cout << "Invalid input! Please try again in this line: ";
    }
    for (int i=0;i<sems.coursesListInSemester[curPos].dayoftheWeek.size();i++){
        sems.coursesListInSemester[curPos].dayoftheWeek[i]=toupper(sems.coursesListInSemester[curPos].dayoftheWeek[i]);
    }
    cout << "Please input the session, follows the following format (must be uppercase): "; //session process
    cout << "S1 | S2 | S3 | S4" << endl;
    cout << "Note: S1 (7:30), S2(9:30), S3(13:30), S4(15:30)" << endl;
    while (getline(cin,sems.coursesListInSemester[curPos].sessionTime) && //check if valid input
           !checkFormatSession(sems.coursesListInSemester[curPos].sessionTime)){
        cout << "Invalid input! Please try again in this line: ";
    }
    ImportStudentsToCoursesInSemester(sems.coursesListInSemester[curPos].listStudentInCourse,sems.coursesListInSemester[curPos].numStudents,
                                      sems.coursesListInSemester[curPos]); //import student.csv, merge later from the work of lehoangan02
    outputSemester(schyrs,sems);
    outputCourse("database/course/"+sems.coursesListInSemester[curPos].ID+".txt",sems.coursesListInSemester[curPos]); //save to database
}
void removeCourse(schoolYear &schyrs,Semester &sems){ //remove a course from the semester
    if (sems.numCourses==0){
        cout << "You don't have any classes to remove." << endl;
        Sleep(3000);
        return;
    }
    cout << "Please choose a course to remove: " << endl;
    for (int i=0;i<sems.numCourses;i++){
        cout << i+1 << ": " << sems.coursesListInSemester[i].ID << endl;
    }
    cout << "Please input a number to delete at this line: ";
    int command=0;
    while (cin >> command && (command<=0 || command>sems.numCourses)){
        cout << "Invalid input! Please try again at this line: ";
    }
    command--;
    string tmpdir="database/course/"+sems.coursesListInSemester[command].ID+".txt";
    int dirsize=tmpdir.size()+1;
    char dir[dirsize]="";
    for (int i=0;i<dirsize-1;i++) dir[i]=tmpdir[i];
    dir[dirsize-1]=0;
    remove(dir);
    sems.numCourses--; //decrease number of course
    if (sems.numCourses==0){ //copy, edit and replace into the sems structure
        sems.coursesListInSemester=nullptr;
    }
    else{
        Course *tmp=new Course[sems.numCourses];
        int add=0;
        for (int i=0;i<sems.numCourses+1;i++){
            if (i!=command){
                tmp[add++]=sems.coursesListInSemester[i];
            }
        }
        for (int i=0;i<=sems.numCourses;i++){
            for (int j=0;j<sems.coursesListInSemester[i].numStudents;j++){
                delete sems.coursesListInSemester[i].listStudentInCourse[j]->scoreOfStudent;
            }
            delete [] sems.coursesListInSemester[i].listStudentInCourse;
        }
        delete []sems.coursesListInSemester;
        sems.coursesListInSemester=tmp;
    }
    outputSemester(schyrs,sems);
}
void outputSemester(schoolYear schyrs, Semester sems){ //save the semester into the database
    ofstream out;
    out.open("database/semester/"+schyrs.period+"-"+to_string(sems.numSemesterInSchoolYear)+".txt");
    out << sems.numSemesterInSchoolYear << endl;
    out << sems.startDate << " " << sems.startMonth << " " << sems.startYear << endl;
    out << sems.endDate << " " << sems.endMonth << " " << sems.endYear << endl;
    out << sems.numCourses << endl;
    for (int i=0;i<sems.numCourses;i++){
        out << sems.coursesListInSemester[i].ID << endl;
    }
    out.close();
}
void outputClass(string fileName,Class curClass){ //save the class into the database
    ofstream out;
    string str;
    out.open(fileName);
    out << curClass.yearStudied << endl;
    out << curClass.numStudent << endl;
    for (int i=0;i<curClass.numStudent;i++){
        Student curStudent=curClass.listStudent[i];
        out << curStudent.studentID << "," << curStudent.firstName << "," << curStudent.lastName << "," << ((curStudent.femaleGender)? 1: 0);
        out << "," << curStudent.DD << "," << curStudent.MM << "," << curStudent.YY << "," << curStudent.socialID;
        out << endl;
    }
    out.close();
    system("CLS");
    cout << curClass.yearStudied << endl;
    cout << curClass.numStudent << endl;
    for (int i=0;i<curClass.numStudent;i++){
        Student curStudent=curClass.listStudent[i];
        cout << curStudent.studentID << "," << curStudent.firstName << "," << curStudent.lastName << "," << ((curStudent.femaleGender)? 1: 0);
        cout << "," << curStudent.DD << "," << curStudent.MM << "," << curStudent.YY << "," << curStudent.socialID;
        cout << endl;
    }
}
void outputSchoolYear(schoolYear &schyrs){ //save the school year into the database
    ofstream out;
    string str;
    out.open("database/schoolyear/"+schyrs.period+".txt"); //output the period, number of classes, and list of classes.
    out << schyrs.period << endl;
    out.close();
}
void outputCourse(string fileName,Course curCourse){ //save the course into the database
    ofstream out;
    string str;
    out.open(fileName); //output the information of courses, and student ID involved in course.
    out << curCourse.ID << endl;
    out << curCourse.courseName << endl;
    out << curCourse.className << endl;
    out << curCourse.teacher << endl;
    out << curCourse.numCredits << endl;
    out << curCourse.maxStudents << endl;
    out << curCourse.dayoftheWeek << endl;
    out << curCourse.sessionTime << endl;
    out << curCourse.numStudents << endl;
    for (int i=0;i<curCourse.numStudents;i++){
        out << curCourse.listStudentInCourse[i]->studentID << endl;
    }
    out.close();
}
void outputCourseScoreBoard(schoolYear schyrs, Semester sems, Course curCourse){ //import the scoreboard from a database and output to screen
    ifstream inp;
    inp.precision(2);
    for (int i=0;i<curCourse.numStudents;i++){ //open student's file
        Student* curStu=curCourse.listStudentInCourse[i];
        string ID=curStu->studentID,str="";
        inp.open("database/scoreboard/"+ID+".txt");
        do{
            string yearCourse="",semCourse="",nameCourse="",str="";
            double total=0,fin=0,mid=0,other=0;
            getline(inp,yearCourse,',');
            getline(inp,semCourse,',');
            getline(inp,nameCourse,',');
            getline(inp,str,',');
            total=stof(str);
            getline(inp,str,',');
            fin=stof(str);
            getline(inp,str,',');
            mid=stof(str);
            getline(inp,str,'\n');
            other=stof(str);
            if (yearCourse==schyrs.period && stoi(semCourse)==sems.numSemesterInSchoolYear && curCourse.ID==nameCourse){
                cout << curStu->studentID << " " << curStu->firstName << " " << curStu->lastName << " "
                    << total << " " << fin << " " << mid << " " << other << endl; //outputx
                break;
            }
        }
        while (!inp.eof());
        inp.close();
    }
}
void outputClassResult(Class curClass, Semester sems, schoolYear schyrs){ //output class result into the screen
    int numStudent=curClass.numStudent;
    system("CLS");
    cout << "Number of students in the class: " << numStudent << endl;
    for (int i=0;i<curClass.numStudent;i++){
        Student curStu=curClass.listStudent[i];
        int numCoursesSemester=0,numCoursesTotal=0,s,quiz,mid,fin,total; float sumGPASem=0,sumGPATotal=0;
        string dir="database/student/"+curStu.studentID+".txt";
        ifstream inp(dir);
        string tmp,period,curCourse;
        cout << "Student ID: " << curStu.studentID << endl;
        for (int j=0;j<7;j++) getline(inp,tmp);
        inp >> numCoursesTotal;
        for (int j=0;j<numCoursesTotal;j++){
            getline(inp,period,' ');
            inp >> s;
            getline(inp,curCourse,' ');
            inp >> total >> fin >> mid >> quiz;
            sumGPATotal+=total;
            if (period==schyrs.period && s==sems.numSemesterInSchoolYear){
                numCoursesSemester++;
                sumGPASem+=total;
                cout << "Name courses: " << curCourse << endl;
                cout << "Final exam marks: " << fin << endl;
                cout << endl;
            }
        }
        cout << "Semester GPA: ";
        if (numCoursesSemester>0) cout << sumGPASem/numCoursesSemester << endl;
        else cout << 0 << endl;
        cout << "Total GPA: ";
        if (numCoursesTotal>0) cout << sumGPATotal/numCoursesTotal << endl;
        else cout << 0 << endl;
        inp.close();
    }
    Sleep(5000);
}
bool checkFormatDayOfTheWeek(string format){ //return true if it's in the right format of day of the week
    for (unsigned int i=0;i<format.size();i++){
        format[i]=toupper(format[i]);
    }
    return (format=="MON" || format=="TUE" || format=="WED" || format=="THU" || format=="FRI" || format=="SAT");
}
bool checkFormatSession(string format){ //return true if it's in the right format of session
    return (format=="S1" || format=="S2" || format=="S3" || format=="S4");
}
