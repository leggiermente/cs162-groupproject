#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

#include "readCSV.h"
#include "Struct.h"
#include "run.h"

Student* readStudentCSV(string filename, int& numStu) {
    ifstream file(filename);
    string line;

    // Get the row of the csv file
    numStu = 0;
    while (getline(file, line))
        numStu++;

    //Reset file
    file.clear();
    file.seekg(0, ios::beg);

    //Create array for students
    Student* newStudent = new Student[numStu];

    //Store data to a array
    int indexStu = 0;
    while (getline(file, line)) {
        stringstream s(line);
        //Pass No data in CSV
        getline(s, line, ',');
        getline(s, line, ','); newStudent[indexStu].studentID = line;
        getline(s, line, ','); newStudent[indexStu].firstName = line;
        getline(s, line, ','); newStudent[indexStu].lastName = line;
        getline(s, line, ','); newStudent[indexStu].femaleGender = stoi(line);
        getline(s, line, ','); newStudent[indexStu].dob = line;
        getline(s, line, ','); newStudent[indexStu].socialID = line;

        //Auto generate password = 1
        newStudent[indexStu].password = "1";
        indexStu++;
    }
    file.close();
    return newStudent;
}
Staff* readStaffCSV(string filename, int& numStaff) {
    ifstream file(filename);
    string line;

    // Get the row of the csv file
    numStaff = 0;
    while (getline(file, line))
        numStaff++;

    //Reset file
    file.clear();
    file.seekg(0, ios::beg);

    //Create array for students
    Staff* newStaff = new Staff[numStaff];

    //Store data to a array
    int indexStaff = 0;
    while (getline(file, line)) {
        stringstream s(line);

        //Pass No data in CSV
        getline(s, line, ',');
        getline(s, line, ','); newStaff[indexStaff].staffID = line;
        getline(s, line, ','); newStaff[indexStaff].firstName = line;
        getline(s, line, ','); newStaff[indexStaff].lastName = line;

        //Auto generate password = 1
        newStaff[indexStaff].password = "1";
        indexStaff++;
    }
    file.close();
    return newStaff;
}
//Course* readDirectory(string path, int& numCourse) {
//    string line;
//    ifstream file(path + "/course.txt");
//    if (!file) cout << "Can't open file\n";
//
//    getline(file, line);
//    numCourse = stoi(line);
//
//    Course* course = new Course[numCourse];
//    for (int i = 0; i < numCourse; i++) {
//        getline(file, line);
//        course[i].ID = line;
//    }
//    file.close();
//
//    for (int i = 0; i < numCourse; ++i) {
//        ifstream file(path + "/" + course[i].ID + ".csv");
//        if (!file) cout << "Can't open file\n";
//        
//        file.seekg(0, ios::beg);
//        getline(file, line);
//        stringstream s(line);
//        getline(s, line, ',');
//        getline(s, line, ','); course[i].courseName = line;
//        getline(s, line, ','); course[i].className = line;
//        getline(s, line, ','); course[i].teacher = line;
//        getline(s, line, ','); course[i].numCredits = stoi(line);
//        getline(s, line, ','); course[i].maxStudents = stoi(line);
//    }
//    return course;
//}
Student* readStudentText(string path, int& numStu) {
    ifstream fin(path + "/ID_Stu.txt");
    if (!fin.is_open()) std::cout << "Can't load file txt\n";
    string line;
    fin >> line;
    numStu = stoi(line);
    Student* stuArr = new Student[numStu];
    for (int i = 0; i < numStu; ++i) {
        fin >> line;
        stuArr[i].studentID = line;
    }
    fin.close();

    for (int i = 0; i < numStu; ++i) {
        string filename = path + "/" + stuArr[i].studentID + ".txt";
        fin.open(filename);
        if (!fin.is_open()) cout << "Can't load file text\n";
        getline(fin, line);
        getline(fin, line); stuArr[i].firstName = line;
        getline(fin, line); stuArr[i].lastName = line;
        getline(fin, line); stuArr[i].femaleGender = (line == "0") ? false : true;
        getline(fin, line); stuArr[i].dob = line;
        getline(fin, line); stuArr[i].socialID = line;
        getline(fin, line); stuArr[i].password = line;
        fin.close();
    }
    return stuArr;
}
schoolYear* readSchoolYear(string path, int& numSchoolYear) {
    string line;
	ifstream file(path + "/schoolyear.txt");
    if (!file) {
        cout << "Can't open school year file\n";
        return nullptr;
    }
	getline(file, line); numSchoolYear = stoi(line);
    schoolYear* schoolYearArr = new schoolYear[numSchoolYear];
    for (int i = 0; i < numSchoolYear; i++) {
        std::getline(file, line, ','); schoolYearArr[i].period = line;
        std::getline(file, line); schoolYearArr[i].numSemester = std::stoi(line);
        schoolYearArr[i].listSemester = new Semester[schoolYearArr[i].numSemester];
        for (int j = 0; j < schoolYearArr[i].numSemester; ++j) {
            schoolYearArr[i].listSemester[j].numSemesterInSchoolYear = j + 1;
        }
    }
    file.close();
    
    for (int i = 0; i < numSchoolYear; ++i) {
        for (int j = 0; j < schoolYearArr[i].numSemester; ++j) {
            string path = "database/semester/" + schoolYearArr[i].period + "_" + to_string(j + 1) + ".txt";
            replace(path.begin(), path.end(), '-', '_');
            readSemesterInSchoolYear(path, schoolYearArr[i].listSemester[j]);
        }
    }
	return schoolYearArr;
}
void readSemesterInSchoolYear(string path, Semester& semester) {
    string line;
    ifstream file(path);
    if (!file) {
		cout << "Can't open semester file\n";
		return;
	}
    getline(file,line, ','); semester.startDate = line;
    getline(file,line); semester.endDate = line;
    getline(file,line); semester.numCourses = stoi(line);
    if (semester.numCourses == 0) {
		semester.coursesListInSemester = nullptr;
		return;
	}
    semester.coursesListInSemester = new Course[semester.numCourses];
    for (int i = 0; i < semester.numCourses; ++i) {
		getline(file, line); semester.coursesListInSemester[i].ID = line;
	}
    return;
}
void readCourseInSemester(string path, schoolYear* schoolYearArr, int numSchoolYear) {
    for (int i = 0; i < numSchoolYear; ++i) {
        for (int j = 0; j < schoolYearArr[i].numSemester; ++j) {
            for (int v = 0; v < schoolYearArr[i].listSemester[j].numCourses; ++v) {
                ifstream file(path + "/" + schoolYearArr[i].listSemester[j].coursesListInSemester[v].ID + ".txt");
                if (!file) {
					cout << "Can't open course file\n";
                    file.close();
                    continue;
				}
                string line;
                getline(file, line); 
                getline(file, line); schoolYearArr[i].listSemester[j].coursesListInSemester[v].courseName = line;
                getline(file, line); schoolYearArr[i].listSemester[j].coursesListInSemester[v].teacher = line;
                getline(file, line); schoolYearArr[i].listSemester[j].coursesListInSemester[v].numCredits = stoi(line);
                getline(file, line); schoolYearArr[i].listSemester[j].coursesListInSemester[v].session = line;
                getline(file, line); schoolYearArr[i].listSemester[j].coursesListInSemester[v].dayOfWeek = line;
                getline(file, line); schoolYearArr[i].listSemester[j].coursesListInSemester[v].maxStudents = stoi(line);
                getline(file, line); int curStu = stoi(line); 
                schoolYearArr[i].listSemester[j].coursesListInSemester[v].currStudents = curStu;
                if (curStu != 0)
                    schoolYearArr[i].listSemester[j].coursesListInSemester[v].listStudentInCourse = new Student[curStu];
                for (int k = 0; k < schoolYearArr[i].listSemester[j].coursesListInSemester[v].currStudents; ++k) {
                    getline(file, line); schoolYearArr[i].listSemester[j].coursesListInSemester[v].listStudentInCourse[k].studentID = line;
                }
                file.close();
            }
        }
    }
    return;
}
Class* readClass(string path, int& numClass) {
    string line;
	ifstream file(path + "/class.txt");
    if (!file) {
        cout << "Can't open class file\n";
    	return nullptr;
    }
	getline(file, line);
    numClass = stoi(line);
    Class* classArr = new Class[numClass];
    for (int i = 0; i < numClass; i++) {
		getline(file, line); 
        classArr[i].classID = line;
	}
    file.close();
    for (int i = 0; i < numClass; i++) {
        file.open(path + "/" + classArr[i].classID + ".txt");
        if (!file) {
			cout << "Can't open class id file\n";
			return nullptr;
		}
        getline(file, line);
		classArr[i].numStudent = stoi(line);
		classArr[i].listStudent = new Student[classArr[i].numStudent];
        for (int j = 0; j < classArr[i].numStudent; j++) {
			getline(file, line);
			classArr[i].listStudent[j].studentID = line;
		}
        readStudentTXT("database/student", classArr[i]);
		file.close();
	}
    return classArr;
}
void readStudentTXT(string path, Class& classStu) {
    for (int i = 0; i < classStu.numStudent; ++i) {
        ifstream file(path + "/" + classStu.listStudent[i].studentID + ".txt");
        if (!file) {
            cout << "Can't open student id file\n";
            cout << classStu.listStudent[i].studentID << endl;
            return;
        }
        string line;
        getline(file, line);
        getline(file, line); classStu.listStudent[i].firstName = line;
        getline(file, line); classStu.listStudent[i].lastName = line;
        getline(file, line); classStu.listStudent[i].femaleGender = (line == "0") ? false : true;
        getline(file, line); classStu.listStudent[i].dob = line;
        getline(file, line); classStu.listStudent[i].socialID = line;
        getline(file, line); classStu.listStudent[i].password = line;
        file.close();
    }
    return;
}
void printTest(Class* classArr, int numClass, schoolYear* schoolYearArr, int numSchoolYear) {
    for (int i = 0; i < numClass; i++) {
		cout << classArr[i].classID << endl;
        for (int j = 0; j < classArr[i].numStudent; j++) {
			cout << classArr[i].listStudent[j].studentID << endl;
            cout << classArr[i].listStudent[j].firstName << endl;
            cout << classArr[i].listStudent[j].lastName << endl;
            cout << classArr[i].listStudent[j].femaleGender << endl;
            cout << classArr[i].listStudent[j].dob << endl;
            cout << classArr[i].listStudent[j].socialID << endl;
            cout << classArr[i].listStudent[j].password << endl;
            cout << endl;
		}
	}
    cout << endl;

    for (int i = 0; i < numSchoolYear; ++i) {
        cout << schoolYearArr[i].period << endl;
        cout << schoolYearArr[i].numSemester << endl;
        for (int j = 0; j < schoolYearArr[i].numSemester; ++j) {
            cout << schoolYearArr[i].listSemester[j].startDate << endl;
            cout << schoolYearArr[i].listSemester[j].endDate << endl;
            cout << schoolYearArr[i].listSemester[j].numSemesterInSchoolYear << endl;
            cout << schoolYearArr[i].listSemester[j].numCourses << endl;
            for (int k = 0; k < schoolYearArr[i].listSemester[j].numCourses; ++k) {
                cout << schoolYearArr[i].listSemester[j].coursesListInSemester[k].ID << endl;
                cout << schoolYearArr[i].listSemester[j].coursesListInSemester[k].currStudents << endl;
                cout << schoolYearArr[i].listSemester[j].coursesListInSemester[k].dayOfWeek << endl;
                for (int v = 0; v < schoolYearArr[i].listSemester[j].coursesListInSemester[k].currStudents; ++v) {
					cout << schoolYearArr[i].listSemester[j].coursesListInSemester[k].listStudentInCourse[v].studentID << endl;
				}
            }
        }
        cout << endl;
    }
    return;
}