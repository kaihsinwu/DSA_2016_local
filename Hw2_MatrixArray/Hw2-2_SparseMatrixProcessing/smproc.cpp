#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>
#include "xstruct.hpp"
#include <vector>
#include <sstream>
using namespace std;


//global variable
mMap ID_idx;
vector<vector<pair<unsigned int,unsigned int>>> dbase;
unsigned int T_start;

int main(int argc,char* argv[]){


// do something


    /**
      map : [ID0 -> 0 |ID1 -> 1 | ID2 -> 2 |ID3 -> 3 |ID4 -> 4 |]

            | id=0        | id=1        | id=2        | id=3        |  ...
      --------------------------------------------------------------------
      dbase:[<itm0,eval0>][<itm0,eval0>]
            [<itm1,eval1>][<itm1,eval1>]
            [<itm2,eval2>][<itm2,eval2>]
                  .             .
                  .             .
                  .             .
       NOTE: <itm,eval> == <item , encoded val = result @ timeoffset >
    */
    //read:


    T_start=read_DB(ID_idx,dbase);


    int n; //# of query
    string qtype;
    unsigned int qargv[4];
    vector<unsigned int> argUsidv;
    string stmp;
    unsigned int tmparg;

    cin >> n;

    while(1){

        if(!(cin >> qtype)) break;


            if(qtype== "accept"){
                for(int j=0;j<3;j++) cin>>qargv[j];
                //for(int ww=0;ww<3;ww++) cout << qargv[ww] << "\t";
                accept(qargv[0],qargv[1],qargv[2]);
            }
            else if(qtype== "items"){
                for(int j=0;j<2;j++) cin>>qargv[j];
                //for(int ww=0;ww<3;ww++) cout << qargv[ww] << "\t";
                items(qargv[0],qargv[1]);
            }
            else if(qtype== "users"){
                for(int j=0;j<4;j++) cin>>qargv[j];
                //for(int ww=0;ww<3;ww++) cout << qargv[ww] << "\t";
                users(qargv[0],qargv[1],qargv[2],qargv[3]);
            }
            else if(qtype== "ratio"){
                for(int j=0;j<2;j++) cin>>qargv[j];
                //for(int ww=0;ww<3;ww++) cout << qargv[ww] << "\t";
                acct_ratio(qargv[0],qargv[1]);
            }
            else if(qtype== "findtime_item"){
                argUsidv.clear();

                cin.ignore();
                getline(cin,stmp);
                istringstream ss(stmp);
                ss >> qargv[0];
                while(1){
                    if(!(ss >> tmparg))break;
                        argUsidv.push_back(tmparg);
                }
                //for(int ww=0;ww<3;ww++) cout << qargv[ww] << "\t";
                findtime_item(qargv[0],argUsidv);
            }

    }



    return 0;
}
