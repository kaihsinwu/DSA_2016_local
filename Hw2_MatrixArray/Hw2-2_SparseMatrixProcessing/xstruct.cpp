#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <map>
#include "xstruct.hpp"
#include <climits>
#include <algorithm>
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

unsigned int encode( unsigned int toff,bool x){
    /**
        using 4 byte to contain 2 col info (+-1) & (timestamp)
        by saving timestamp's offset from the first data as uint32.
    */

    toff=(toff << 1);
    toff +=x;
    return (unsigned int)((toff << 1) + x);

}

bool decode(unsigned int &toff_e,unsigned int &out_toff){
    /**
        using 4 byte to contain 2 col info (+-1) & (timestamp)
        by saving timestamp's offset as uint32 from the first row in data .
    */
    //get bool x:
    out_toff=(toff_e >>1);
    //decode time stamp
    //toff_e= toff_e >>1;
    return (bool)((toff_e << 31 )>> 31);
}


bool pairComp_2(const pair<unsigned int,unsigned int> &A, const pair<unsigned int,unsigned int> &B) {

  return (unsigned int)(A.second >> 1) <  (unsigned int)(B.second >> 1 ) ;

}

unsigned int test_format(mMap &ID_Dic,vector<vector<pair<unsigned int,unsigned int>>> &dbid){
    FILE * pFile;

    char line[40];//buffer

    unsigned int i=0;//file line index
    unsigned int iteridx=0;//currect #of ID iterator

    //formattor:
    char *string1;
    char *string2;
    char *string3;
    char *string4;

    unsigned int T0;

    //debug info :
    unsigned int pos;
    unsigned int ID_MIN=UINT_MAX;
    unsigned int ID_MAX=0;
    unsigned int Tos_prev=0;
    unsigned int Tos_max=0;



    pFile = fopen ("/run/media/kaywu/F40C-9290/rec_log_train.txt" , "rb");
    if (pFile != NULL){
       mMap::iterator idxr;

        while(1){
        //for(int i=0;i<10;i++){

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
                    T0=atoi(string4); /**crutial*/
                }else{
                    if(Tos_prev>atoi(string4))
                        cout << "ERROR! time is not sort." << endl;
                    else if(atoi(string4)-T0>Tos_max)
                        Tos_max=atoi(string4)-T0;
                    Tos_prev=atoi(string4);
                }
                if((atoi(string4)-T0)%1000==0)
                    toff2fpos.push_back(pos);
            //
            idxr=ID_Dic.find(atoi(string1));
            if(idxr== ID_Dic.end()){
                //cout << "\n newID found ! :" << atoi(string1) << "at iteridx : "<< iteridx << endl;
                ID_Dic.insert(pair<unsigned int,unsigned int>(atoi(string1),iteridx));
                iteridx++;
                //save all:
                dbid.push_back( vector<pair<unsigned int,unsigned int>>(1,pair<unsigned int,unsigned int>(atoi(string2),encode(atoi(string4)-T0,(bool)(atoi(string3)+1)))
                                                                        )

                               );
                //save the first elem:
                //db.push_back(vector<unsigned int>(1,atoi(string2)));

            }else{
                //save pos:

                dbid.at(idxr->second).push_back(pair<unsigned int,unsigned int>(atoi(string2),encode(atoi(string4)-T0,(bool)(atoi(string3)+1))));
                //save the first elem:
                //dbid.at(idx->second).push_back(atoi(string2));
            }
            //cout << string1<<endl;
            //ID_addr.insert(make_pair(atoi(string1),pos));

            i++;
            //if(i==50000000) break;

        }
        fclose(pFile);

        cout << "map of total keys conut:" << ID_Dic.size() << endl;
        /*
        cout << "map keys:" << endl;
        for(mMap::iterator it = ID_Dic.begin(); it != ID_Dic.end(); ++it) {
            cout << it->second <<"\t"<<  it->first << "\n";
        }
        */

        cout << "dbase #row: " << dbid.size() << endl;
        /*
        for(int j=0;j<dbid.size();j++){
            cout << "dbase #col for row " << j << " :" << dbid.at(j).size() <<endl;
            for(int k=0;k<dbid.at(j).size();k++)
                cout << "\t"<<dbid.at(j).at(k).second << " : " ;
            cout << "\n" ;
        }
        */
        cout << "ID_min: " << ID_MIN << endl;
        cout << "ID_max: " << ID_MAX << endl;
        cout << "T0 : " << T0 << endl;
        cout << "saved data in toff2fpos: " << toff2fpos.size() << endl;
        cout << "Max time offset: " << Tos_max <<endl;
        cout << "VM : " << getVMValue()/1024 << "MB" <<endl;
        cout << "PM : " << getPMValue()/1024 << "MB" <<endl;
    }


    return T0;



    //if ( fgetws (mystring , 100 , pFile) != NULL )
}







int accept(unsigned int uid,unsigned int itm,unsigned int tstmp){
    //assume no collision in database.
    /**
        Description:
            return the accept status +1,-1 of user with
            specific uid, specific item and specific timestamp.

        Input param
            uid1 : user IDs
            itm  : item
            tstmp: timestamp

        return
            0 : not found match data
            1 : accept state
            -1: deny state
    */
    int fnum=0;
    bool x;
    unsigned int t_off;
    mMap::iterator idxr=ID_idx.find(uid);

    if(idxr!=ID_idx.end()){
            for(int j=0;j<dbase.at(idxr->second).size();j++)
                if(dbase.at(idxr->second).at(j).first==itm){
                    fnum++;
                    cout << fnum; //debug
                    x=decode(dbase.at(idxr->second).at(j).second,t_off);
                    if(t_off==tstmp-T_start)
                        return (int)(x-1);
                }


    }
    return 0; // no found;
}

int items(unsigned int uid1,unsigned int uid2){
    /**
        Description:
            stdout the same items shared by users with ID uid1 & uid2.

        Input param
            uid1,uid2 : user IDs

        return
            0 : no data found
            1 : correct behavior and match found
            -1: error occour. (uid not found)
    */

    mMap::iterator idxr1=ID_idx.find(uid1);
    mMap::iterator idxr2=ID_idx.find(uid2);
    int itern=0;
    unsigned int prev=0;
    if(idxr1==ID_idx.end()){
        cout << "## Query ERROR ## items(u1,u2):" << endl << " user1 ID: "<<uid1<< "is not found." << endl;
        return -1;
    }
    if(idxr2==ID_idx.end()){
        cout << "## Query ERROR ## items(u1,u2):" << endl << " user2 ID: "<<uid2<< "is not found." << endl;
        return -1;
    }

    sort(dbase.at(idxr1->second).begin(),dbase.at(idxr1->second).end());
    sort(dbase.at(idxr2->second).begin(),dbase.at(idxr2->second).end());
    cout << "Find the same items of user1: " << uid1 << " & user2: " << uid2 << endl;
    //simple one.
    for(int i=0;i<dbase.at(idxr1->second).size();i++){
        if(prev!=dbase.at(idxr1->second).at(i).first){
            prev=dbase.at(idxr1->second).at(i).first;
            for(int j=0;j<dbase.at(idxr2->second).size();j++)
                if(prev==dbase.at(idxr2->second).at(j).first){
                    cout << " "<<prev << endl;
                    itern++;
                    break;
                }

        }

    }

    cout << "#total found items: " <<itern << endl;
    if(itern==0)
        return 0;
    return 1;

}


int users(unsigned int itm1,unsigned int itm2,unsigned int t1,unsigned int t2){
    FILE * pFile;
    char linebuf[40];
    vector<unsigned int> itm1_IDs;
    vector<unsigned int> itm2_IDs;
    char *s1,*s2,*s4;

    if(t2<=t1){
        cout << "## time range ERROR ## t2 cannot be small or equal t1 ." << endl;
        return -1;

    }

    pFile = fopen ("/run/media/kaywu/F40C-9290/rec_log_train.txt" , "rb");
    if (pFile == NULL){
        cout << "## Read File ERROR ## log file not found." << endl;
        return -2;
    }

    fseek(pFile,0,toff2fpos.at((t1-T_start)/1000));
    while(1){


            if(fgets(linebuf,sizeof(linebuf),pFile)==NULL) break;
            //sscanf( line,"%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", string1,string2,string3,string4);
            //sscanf( line,"%[^\t]\t%[^\n]\n", string1,string1b);
            s1= strtok(linebuf,"\t");
            s2 = strtok(NULL, "\t");
            strtok(NULL, "\t");
            s4 = strtok(NULL, "\n");
            if(atoi(s4)>t2)
                break;
            if(atoi(s4)>=t1 && atoi(s4)<=t2){

                if(atoi(s2)==itm1)
                    itm1_IDs.push_back(atoi(s1));
                if(atoi(s2)==itm2)
                    itm2_IDs.push_back(atoi(s1));

            }


    }
    fclose(pFile);

    sort(itm1_IDs.begin(),itm1_IDs.end());
    sort(itm2_IDs.begin(),itm2_IDs.end());

    unsigned int prevID=0, itern=0;

    cout << "Find the IDs have both item1: " << itm1 << " & item2: " << itm2 <<"from time range: " << t1 << " to " << t2 << endl;
    for(int i=0;i<itm1_IDs.size();i++){
        if(prevID!=itm1_IDs.at(i)){
            prevID=itm1_IDs.at(i);
            for(int j=0;j<itm2_IDs.size();j++)
                if(prevID==itm2_IDs.at(j)){
                    cout << " "<<prevID << endl;
                    itern++;
                    break;
                }

        }
    }

    cout << "#total found IDs: " <<itern << endl;
    if(itern==0)
        return 0;
    return 1;


}
