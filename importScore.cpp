#include "importScore.h"

void importScoreBoardCSV(string filename, Course& course)
{
    ifstream file(filename);
    string line;
    
    if(!file){
        cout <<"Can not open file: " << filename <<"\n";
        return;
    }
    
    getline(file,line); // ignore header file
    for (int i=0; i < course.currStudents; i++)
    {
        course.listStudentInCourse[i]->score = new ScoreStu;
        getline(file,line);
        stringstream ss(line);
        getline(ss, line,',');   //No
        getline(ss, line ,',');  //student id
        getline(ss, line, ',');  //student full name
        getline(ss, line, ',');  course.listStudentInCourse[i]->score->totalMark = stof(line);
        getline(ss, line, ','); course.listStudentInCourse[i]->score->finalMark = stof(line);
        getline(ss, line, ',');  course.listStudentInCourse[i]->score->midMark = stof(line);
        getline(ss, line, ','); course.listStudentInCourse[i]->score->otherMark = stof(line);
    }
    
    file.close();
}

//update scoreboard

void updateStudentResult(Student* scoreboard,int numStu ,float otherMark, float midMark, float finalMark, float totalMark, string studentID)
{
    for (int i=0; i<numStu; i++)
    {
        if (scoreboard[i].studentID == studentID)
        {
            scoreboard[i].score->otherMark = otherMark;
            scoreboard[i].score->midMark = midMark;
            scoreboard[i].score->finalMark = finalMark;
            scoreboard[i].score->totalMark = totalMark;
            return;
        }
    }
}
