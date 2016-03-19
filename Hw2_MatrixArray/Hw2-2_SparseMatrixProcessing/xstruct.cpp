#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <map>
#include "xstruct.hpp"
#include <climits>
using namespace std;



int parseLine(char* line){
    int i = strlen(line);
    while (*line < '0' || *line > '9') line++;
    line[i-3] = '\0';
    i = atoi(line);
    return i;
}


int getVMValue(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];


    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}
int getPMValue(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];


    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int test_format(mMap &ID_addr){
    FILE * pFile;

    char line[40];
    //int itr=0;
    unsigned int i=0;
    //bool fid=0;
    char *string1;
    char *string2;
    char *string3;
    char *string4;
    unsigned int pos;
    unsigned int ID_MIN=UINT_MAX;
    unsigned int ID_MAX=0;
    unsigned int Tos_prev=0;
    unsigned int Tos_max=0;
    unsigned int T0;

    //mMap ID_addr;

    //pFile = fopen ("/run/media/kaywu/F40C-9290/rec_log_train.txt" , "rb");
    pFile = fopen ("/run/media/kaywu/F40C-9290/rec_log_train.txt" , "rb");
    if (pFile != NULL){

        while(1){
        //for(int i=0;i<10;i++){

            //wrong?
            pos=ftell(pFile);
            if(fgets(line,sizeof(line),pFile)==NULL) break;
            //sscanf( line,"%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", string1,string2,string3,string4);
            //sscanf( line,"%[^\t]\t%[^\n]\n", string1,string1b);
            string1= strtok(line,"\t");
            string2 = strtok(NULL, "\t");
            string3 = strtok(NULL, "\t");
            string4 = strtok(NULL, "\n");
            if(atoi(string1)>ID_MAX)
                ID_MAX=atoi(string1);
            if(atoi(string1)<ID_MIN)
                ID_MIN=atoi(string1);
            if(i==0){
                Tos_prev=atoi(string4);
                T0=atoi(string4);
            }else{
                if(Tos_prev>atoi(string4))
                    cout << "ERROR! time is not sort." << endl;
                else if(atoi(string4)-Tos_prev>Tos_max)
                    Tos_max=atoi(string4)-Tos_prev;
                Tos_prev=atoi(string4);
            }

            //cout << string1<<endl;
            //ID_addr.insert(make_pair(atoi(string1),pos));

            i++;
            //cout << i << endl;

            //cout << i << endl;
        //printf( "%s\t%s\t%s\n",                    string1, string2, string3 );
        }

    }

    fclose(pFile);
    cout << "ID_min: " << ID_MIN << endl;
    cout << "ID_max: " << ID_MAX << endl;
    cout << "T0 : " << T0 << endl;
    cout << "Max time offset: " << Tos_max <<endl;
    cout << "VM : " << getVMValue()/1024 << "MB" <<endl;
    cout << "PM : " << getPMValue()/1024 << "MB" <<endl;
    return i;



    //if ( fgetws (mystring , 100 , pFile) != NULL )
}



