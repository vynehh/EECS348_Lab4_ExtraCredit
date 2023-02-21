
#include <iostream>
#include <fstream>

using namespace std;


const int MATCHES = 5;


bool progPrefCur(int pref[2*MATCHES][MATCHES],int pIndex,int dep,int curDep)
{
    for(int i = 0; i < MATCHES; i++)
    {
        if(pref[pIndex][i] == curDep)
        {
            return true;
        }
        if(pref[pIndex][i] == dep)
        {
            return false;
        }
    }
    
    return false;
}

void thePreferences(int pref[2*MATCHES][MATCHES])
{  
    int prog[MATCHES] = {-1,-1,-1,-1,-1};
    
    bool takenDepartment[MATCHES] = {};
    int freeDep = 5;

    while(freeDep > 0)
    {
        int d;
        
        for(d = 0; d < MATCHES; d++)
        {
            if(takenDepartment[d] == false)
            {
                break;
            }
        }
        
        for(int a = 0; a < MATCHES && takenDepartment[d] == false; a++)
        {
            
            int progPref = pref[d][a];
            
            if(prog[progPref - 1]== -1)
            {
                prog[progPref - 1]= d;
                takenDepartment[d]= true;
                freeDep--;
            }
            else
            {
                
                int curDep = prog[progPref - 1];
                
                if(progPrefCur(pref, progPref + 4, d + 1, curDep+1) == false)
                {
                    prog[progPref - 1]= d;
                    takenDepartment[d]= true;
                    takenDepartment[curDep]=false;
                }
            }
        }
    }
    
    for (int i = 0; i < MATCHES; i++)
    {
        for(int j = 0; j < MATCHES; j++)
        {
            if(i == prog[j])
            {
                cout << "Department #" << i + 1 << " will get Programmer " << j + 1 << "\n"; 
            }
        }
    }
}
int main()
{
    
    int pref[2*MATCHES][MATCHES] = {-1};
    
    
    ifstream inFile;
    inFile.open("input.txt");
    
    if(inFile.fail())
    {
        cout << "File opening failed. \n"; 
    }
    else
    {
        while(inFile)
        {
            for(int i = 0; i < MATCHES; i++)
            {
                for(int j = 0; j < MATCHES; j++)
                {
                    inFile >> pref[j][i];                    
                }
            }
            for(int i = 0; i < MATCHES; i++)
            {
                for(int j = MATCHES; j < MATCHES*2; j++)
                {
                    inFile >> pref[j][i];             
                }
            }
        }
    }
    inFile.close();

    thePreferences(pref);
    return 0;
}
