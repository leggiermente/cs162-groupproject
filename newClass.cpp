#include "newClass.h"

int countLine (string filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        int lineCount = 0;
        string line;

        while (getline(file, line)) lineCount++;

        file.close();
        return lineCount;
    }
    else
    {
        cerr << "Can not open file: " << filename <<"\n";
        return 0;
    }
}
void loadClassFromFile(string &filename, schoolYear &targetSchoolYear) {
    targetSchoolYear.classCount = countLine(filename);
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        targetSchoolYear.classList = new Class[targetSchoolYear.classCount];
        for (int i = 0; i<targetSchoolYear.classCount; i++)
        {
            getline(file,line);
            stringstream ss(line);
            char comma;
            ss>> targetSchoolYear.classList[i].classID;
            ss>>comma;
            ss>> targetSchoolYear.classList[i].yearStudied;
        }
        file.close();
    } else {
        cout << "Cannot open file: " << filename << "\n";
    }
}

void createNewClass(schoolYear &targetSchoolYear)
{
    Class* newClassList = new Class[targetSchoolYear.classCount +1];
    
    for (int i=0; i < targetSchoolYear.classCount; i++)
    {
        newClassList[i] = targetSchoolYear.classList[i];
    }
    
    cout <<"Input Class ID: ";
    cin >> newClassList[targetSchoolYear.classCount].classID;
    cout <<"Input Year Studied: ";
    cin >> newClassList[targetSchoolYear.classCount].yearStudied;
    
    if(targetSchoolYear.classCount > 0) delete [] targetSchoolYear.classList;
    targetSchoolYear.classList = newClassList;
    targetSchoolYear.classCount++;
}

void updateFileSchoolYear(string &filename, schoolYear &targetSchoolYear)
{
    ofstream file(filename);
    
    if (!file.is_open()) cout <<"Can not open file\n";
    else
    {
        for (int i=0; i<targetSchoolYear.classCount; i++)
        {
            file <<targetSchoolYear.classList[i].classID <<",";
            file <<targetSchoolYear.classList[i].yearStudied<<"\n";
        }
        if (file.good())
        {
            cout <<"School year information updated in "<< filename <<" successfully\n";
        }
        else cout <<"Error: Writing to file failed: "<<filename <<"\n";
        file.close();
    }
}
