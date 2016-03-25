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

    return (unsigned int)((toff << 1) + x);

}

bool decode(unsigned int &toff_e,unsigned int &out_toff){
    /**
        using 4 byte to contain 2 col info (+-1) & (timestamp)
        by saving timestamp's offset as uint32 from the first row in data .
    */
    //decode time stamp
    out_toff=(toff_e >>1);

    //return  bool x:
    return (bool)(toff_e & MASK );
}


unsigned int read_DB(mMap &ID_Dic,vector<vector<pair<unsigned int,unsigned int>>> &dbid){
    FILE * pFile;

    char line[40];//buffer

    unsigned int i=0;//file line index
    unsigned int iteridx=0;//currect #of ID iterator

    //formattor:
    char *string1;
    char *string2;
    char *string3;
    char *string4;

    int T0;

    //debug info :
    unsigned int pos;
    unsigned int ID_MIN=UINT_MAX;
    unsigned int ID_MAX=0;
    unsigned int Tos_prev=0;
    unsigned int Tos_max=0;



    pFile = fopen(DB_PATH , "rb");
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
            //if(atoi(string1)==1341923) cout << "EXIST" << endl;

            if(i==0){
                T0=atoi(string4); /**crutial*/
            }


            //
            idxr=ID_Dic.find(atoi(string1));
            if(idxr== ID_Dic.end()){

                ID_Dic.insert(pair<unsigned int,unsigned int>(atoi(string1),iteridx));
                iteridx++;
                //save all:
                dbid.push_back( vector<pair<unsigned int,unsigned int>>(1,pair<unsigned int,unsigned int>(atoi(string2),encode(atoi(string4)-T0,(bool)(atoi(string3)+1)))
                                                                        )

                               );


            }else{
                //save pos:

                dbid.at(idxr->second).push_back(pair<unsigned int,unsigned int>(atoi(string2),encode(atoi(string4)-T0,(bool)(atoi(string3)+1))));

            }

            i++;


        }
        fclose(pFile);

        //sort process:
        unsigned int uitmp,uitmp2,j;
        for(int so=0;so <dbase.size();so++){
            uitmp=0; uitmp2=0; j=0;
            sort(dbase.at(so).begin(),dbase.at(so).end());
            //remove duplicate:
            while(j!=dbase.at(so).size()){

                if(dbase.at(so).at(j).first==uitmp && dbase.at(so).at(j).second==uitmp2){dbase.at(so).erase(dbase.at(so).begin()+j);}
                else{
                    uitmp=dbase.at(so).at(j).first;
                    uitmp2=dbase.at(so).at(j).second;
                    j++;
                }
            }

        }
        /*
        cout << "T0 : " << T0 << endl;
        cout << "VM : " << getVMValue()/1024 << "MB" <<endl;
        cout << "PM : " << getPMValue()/1024 << "MB" <<endl;
        */
    }


    return T0;



    //if ( fgetws (mystring , 100 , pFile) != NULL )
}




int accept(const unsigned int &uid,const unsigned int &itm,const unsigned int &tstmp){
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
    //int fnum=0;
    bool x;
    unsigned int t_off;
    mMap::iterator idxr=ID_idx.find(uid);

    if(idxr!=ID_idx.end()){
            //cout << "find! " << "elements" << dbase.at(idxr->second).size() << endl;
            for(int j=0;j<dbase.at(idxr->second).size();j++)
                if(dbase.at(idxr->second).at(j).first==itm){
                    //fnum++;
                    //cout << "item match" << fnum << endl;
                    x=decode(dbase.at(idxr->second).at(j).second,t_off);
                    //t_off=t_off>>1;
                    //cout << x << " " << t_off << endl;
                    //cout << "T0="<< T_start << "tstmp="<<tstmp << endl;
                    if(t_off==tstmp-T_start){
                        cout << (2*(int)x-1) << endl;
                        return 1;
                    }

                }


    }

    cout << 0 << endl;
    return 0; // no found;
}

int items(const unsigned int &uid1,const unsigned int &uid2){
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
    //chk if ID EXIST.
    /*
    if(idxr1==ID_idx.end()){
        cout << "## Query ERROR ## items(u1,u2):" << endl << " user1 ID: "<<uid1<< "is not found." << endl;
        return -1;
    }
    if(idxr2==ID_idx.end()){
        cout << "## Query ERROR ## items(u1,u2):" << endl << " user2 ID: "<<uid2<< "is not found." << endl;
        return -1;
    }
    */

    for(int i=0;i<dbase.at(idxr1->second).size();i++){
        if(prev!=dbase.at(idxr1->second).at(i).first){
            prev=dbase.at(idxr1->second).at(i).first;
            for(int j=0;j<dbase.at(idxr2->second).size();j++)
                if(prev==dbase.at(idxr2->second).at(j).first){
                    cout <<prev << endl;
                    itern++;
                    break;
                }

        }

    }


    if(itern==0)
        cout << "EMPTY" << endl;

}

int users(const unsigned int &itm1,const unsigned int &itm2,const unsigned int &t1,const unsigned int &t2){
    vector<unsigned int> res;
    unsigned int itml = (itm1 > itm2) ? itm1:itm2;
    unsigned int itms = (itm1 < itm2) ? itm1:itm2;
    unsigned int idxlstart,tmpu,flag;
    for(mMap::iterator it = ID_idx.begin(); it != ID_idx.end(); ++it){
        flag=0;idxlstart=dbase.at(it->second).size();
        //small one;
        for(int j=0;j<dbase.at(it->second).size();j++){
            if(dbase.at(it->second).at(j).first > itms){ idxlstart=j; break;}
            else if(dbase.at(it->second).at(j).first==itms){
                tmpu=(dbase.at(it->second).at(j).second>>1) + T_start ;
                if(tmpu >= t1 && tmpu <= t2){ idxlstart=j+1; flag++; break;}
            }
        }
        for(int j=idxlstart;j<dbase.at(it->second).size();j++){
            if(dbase.at(it->second).at(j).first > itml){ break;}
            else if(dbase.at(it->second).at(j).first==itml){
                tmpu=(dbase.at(it->second).at(j).second>>1) + T_start ;
                if(tmpu >= t1 && tmpu <= t2){  flag++; break;}
            }
        }
        if(flag==2)
            res.push_back(it->first);
    }
    if(res.size()==0) cout << "EMPTY" << endl;
    else{
      for(int i=0;i<res.size();i++)
            cout << res[i] << endl;
    }
    return 0;

}


int acct_ratio(const unsigned int &itm,const unsigned int &thold){





    /**
        Description:
            get the acceptance ratio of # of users
            accept when users have item "itm"
            more than threadhold times.

        Input param
            itm  : Item
            thold: threadhold

        return
            >=0 : the ratio of which require.
            -1  : no users have item more than threadhold times.

    */


    int cnt_have=0,cnt_acc=0;


    for(int i=0;i<dbase.size();i++){
        if(dbase.at(i).size() > thold){
            cnt_have ++;
            for(int j=0;j<dbase.at(i).size();j++){
                if(dbase.at(i).at(j).first==itm && (bool)( dbase.at(i).at(j).second & MASK ) ){
                    cnt_acc += 1;
                    break;
                }

            }
        }
    }

    cout << cnt_acc << "/" <<cnt_have << endl;
    return 1;


}





int findtime_item(const unsigned int &itm,vector<unsigned int> &Usid){

    mMap::iterator it;
    vector<unsigned int> toff_list;
    for(int i=0;i<Usid.size();i++){
        it=ID_idx.find(Usid[i]);

        for(int j=0;j<dbase.at(it->second).size();j++){
            if(dbase.at(it->second).at(j).first==itm){

                toff_list.push_back( (unsigned int)(dbase.at(it->second).at(j).second >> 1) );
            }
        }

    }

    if(toff_list.size()==0){

        cout << "EMPTY" << endl;

    }else{
        unsigned int tmp=0;
        sort(toff_list.begin(),toff_list.end());
        for(int i=0;i<toff_list.size();i++)
            if(tmp!=toff_list[i]){
                tmp=toff_list[i];
                cout << toff_list[i] + T_start << endl;
            }

    }


    return 1;



}
