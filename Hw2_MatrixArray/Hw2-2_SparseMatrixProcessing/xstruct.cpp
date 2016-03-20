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

void encode(unsigned int &toff,bool &x){
    /**
        using 4 byte to contain 2 col info (+-1) & (timestamp)
        by saving timestamp's offset as uint32 from the first row in data .
    */
    toff = toff << 1;
    toff += x;  //save this !

}

bool decode(unsigned int &toff_e){
    /**
        using 4 byte to contain 2 col info (+-1) & (timestamp)
        by saving timestamp's offset as uint32 from the first row in data .
    */
    //get bool x:
    bool x;
    x=(toff_e << 31 )>> 31;
    //decode time stamp
    toff_e= toff_e >>1;
    return x;
}


int test_format(mMap &ID_Dic,vector<vector<unsigned int>> &db){
    FILE * pFile;

    char line[40];
    //int itr=0;
    unsigned int i=0;
    unsigned int iteridx=0;
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
        map<unsigned int,unsigned int>::iterator idx;
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

            //debug :
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
                    else if(atoi(string4)-T0>Tos_max)
                        Tos_max=atoi(string4)-T0;
                    Tos_prev=atoi(string4);
                }
            //
            idx=ID_Dic.find(atoi(string1));
            if(idx== ID_Dic.end()){
                //cout << "\n newID found ! :" << atoi(string1) << "at iteridx : "<< iteridx << endl;
                ID_Dic.insert(pair<unsigned int,unsigned int>(atoi(string1),iteridx));
                iteridx++;
                db.push_back(vector<unsigned int>(1,pos));

            }else{

                db.at(idx->second).push_back(pos);

            }
            //cout << string1<<endl;
            //ID_addr.insert(make_pair(atoi(string1),pos));

            i++;
            //if(i==1000000000) break;
        //printf( "%s\t%s\t%s\n",                    string1, string2, string3 );
        }
    fclose(pFile);

    cout << "map of total keys conut:" << ID_Dic.size() << endl;
    /*
    cout << "map keys:" << endl;
    for(mMap::iterator it = ID_Dic.begin(); it != ID_Dic.end(); ++it) {
        cout << it->second <<"\t"<<  it->first << "\n";
    }
    */

    cout << "dbase #row: " << db.size() << endl;
    /*
    for(int j=0;j<db.size();j++)
        cout << "dbase #col for row " << j << " :" << db.at(j).size() << endl;
    */
    cout << "ID_min: " << ID_MIN << endl;
    cout << "ID_max: " << ID_MAX << endl;
    cout << "T0 : " << T0 << endl;
    cout << "Max time offset: " << Tos_max <<endl;
    cout << "VM : " << getVMValue()/1024 << "MB" <<endl;
    cout << "PM : " << getPMValue()/1024 << "MB" <<endl;
    }


    return i;



    //if ( fgetws (mystring , 100 , pFile) != NULL )
}



