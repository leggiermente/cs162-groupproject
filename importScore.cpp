#include "importScore.hpp"

void importScore(string path, Course &course)
{
    ifstream file(path);
    if (!file)
    {
        cout <<"Can not open: " << path <<"\n";
        return;
    }
    
    string line;
    getline(file,line);
    
    while (getline(file,line))
    {
        istringstream iss(line);
        string token;
        getline(iss, token, ',');  // Discard No
        getline(iss, token, ','); // Student ID
        int i = 0;
        
        for(; i < course.currStudents; i++)
        {
            if(course.listStudentInCourse[i]->studentID == token) break;
        }
        course.listStudentInCourse[i]->numCourse++;
        ScoreStu* listScore = new ScoreStu[course.listStudentInCourse[i]->numCourse];
        for (int j = 0; j < course.listStudentInCourse[i]->numCourse - 1; j++)
        {
            listScore[j] = course.listStudentInCourse[i]->scoreList[j];
        }
        listScore[course.listStudentInCourse[i]->numCourse - 1].year = course.year;
        listScore[course.listStudentInCourse[i]->numCourse - 1].courseID = course.ID;
        listScore[course.listStudentInCourse[i]->numCourse - 1].semester = course.semester;
        
        getline(iss, token, ','); // Discard fullname
        getline(iss, token, ','); // Discard total mark
        listScore[course.listStudentInCourse[i]->numCourse - 1].totalSc = stof(token);
        getline(iss, token, ','); // Discard final mark
        listScore[course.listStudentInCourse[i]->numCourse - 1].finalSc = stof(token);
        getline(iss, token, ','); // Discard midterm mark
        listScore[course.listStudentInCourse[i]->numCourse - 1].midSc = stof(token);
        getline(iss, token, ','); // Discard other mark
        listScore[course.listStudentInCourse[i]->numCourse - 1].otherSc = stof(token);
        
        delete[] course.listStudentInCourse[i]->scoreList; // Deallocate previous memory
        course.listStudentInCourse[i]->scoreList = listScore;
        
        string filename = course.listStudentInCourse[i]->studentID + ".txt";
        ofstream fout(filename);
        if (!fout)
        {
            cout <<"Can not create/open : " << filename <<"\n";
            continue;
        }
        
        fout << course.listStudentInCourse[i]->studentID <<"\n";
        fout << course.listStudentInCourse[i]->firstName <<"\n";
        fout << course.listStudentInCourse[i]->lastName <<"\n";
        fout << (course.listStudentInCourse[i]->femaleGender ? "1\n" : "0\n");
        fout << course.listStudentInCourse[i]->dob <<"\n";
        fout << course.listStudentInCourse[i]->socialID <<"\n";
        fout << course.listStudentInCourse[i]->password <<"\n";
        fout << course.listStudentInCourse[i]->numCourse <<"\n";
        for (int j = 0; j < course.listStudentInCourse[i]->numCourse; j++)
        {
            fout << course.listStudentInCourse[i]->scoreList[j].year << ",";
            fout << course.listStudentInCourse[i]->scoreList[j].courseID << ",";
            fout << course.listStudentInCourse[i]->scoreList[j].totalSc << ",";
            fout << course.listStudentInCourse[i]->scoreList[j].midSc << ",";
            fout << course.listStudentInCourse[i]->scoreList[j].finalSc << ",";
            fout << course.listStudentInCourse[i]->scoreList[j].otherSc << "\n";
        }
        fout.close();
    }
    file.close();
}

