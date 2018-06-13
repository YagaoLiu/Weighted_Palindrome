#include <iostream>
#include <math.h>

using namespace std;

void FunctionWMPA(int * MP, int n){
    
    int MPL[int(n/2)+1][int(n/2)+1];
    int MMPL[int(n/2)+1];
    int PA[int(n/2)+1];

    
    for(int i=0;i<(int(n/2)+1);i++)
    {
        MPL[i][0]=0;
        MMPL[i]=0;

    }
    
    for(int i=0;i<n;i++)
    {
        int x=int((i+MP[i])/2);
        ++MPL[x][0];
        MPL[x][MPL[x][0]]=MP[i];
    }
    
    
    for(int i=0;i<=(int(n/2));i++)
    {
        if(MPL[i][0]!=0)
        {
            MMPL[i]=MPL[i][1];
        }
        else
        {
            MMPL[i]=0;
        }
    
    }
    
    PA[int(n/2)]=MMPL[int(n/2)];
    
    for(int i=(int(n/2)-1);i>=0;i--)
    {
        if((PA[i+1]-2)>=MMPL[i])
        {
            PA[i]=PA[i+1]-2;
        }
        else
        {
            PA[i]=MMPL[i];
        }
    }
    /*
    for(int i=0;i<=(int(n/2));i++)
    {
        if(MPL[i][0]!=0)
        {
            
            for(int s=1; s<=MPL[i][0];s++)
                cout<<"MPL["<<i<<"]["<<s<<"]="<<MPL[i][s]<<endl;
            cout<<"\n+++++++++++++++++\n"<<endl;
        }
        
    }
    
    for(int i=0;i<=(int(n/2));i++)
    {
        cout<<"MMPL["<<i<<"]="<<MMPL[i]<<endl;
        cout<<"\n+++++++++++++++++\n"<<endl;

        
    }
    
    for(int i=0;i<=(int(n/2));i++)
    {
        cout<<"PA["<<i<<"]="<<PA[i]<<endl;
        cout<<"\n+++++++++++++++++\n"<<endl;
        
        
    }

    cout<<"\n*************************************************\n";
*/
}


