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
        if (targetSchoolYear.classList != nullptr ) delete [] targetSchoolYear.classList;
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

void createNewClassToFile(string &filename)
{
    Class* newClass = new Class;
    cout <<"Input Class ID: ";
    cin >> newClass->classID;
    cout <<"Input year studied: ";
    cin >> newClass->yearStudied;
    
    ofstream file(filename,ios::app);
    if(file.is_open())
    {
        file <<newClass->classID <<",";
        file << newClass->yearStudied <<"\n";
        file.close();
        cout <<"Class information written to: " << filename <<" successfully\n";
    }
    else cout <<"Can not open file: " << filename <<"\n";
    delete newClass;
}
