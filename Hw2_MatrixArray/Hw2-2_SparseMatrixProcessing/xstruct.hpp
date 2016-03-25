#ifndef XSTRUCT_HPP_INCLUDED
#define XSTRUCT_HPP_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <map>
#include <vector>
using namespace std;


#define DB_PATH "/run/media/kaywu/F40C-9290/rec_log_train.txt"
#define MASK (0x00000001)

//ID dictionary realization type
typedef map<unsigned int,unsigned int> mMap;

//variable proto
extern  mMap ID_idx;
extern  vector<vector<pair<unsigned int,unsigned int>>> dbase;
extern  unsigned int T_start;


//read database
unsigned int read_DB(mMap &,vector<vector<pair<unsigned int,unsigned int>>> &);

//crypto routine:
unsigned int encode(unsigned int  ,bool );
bool decode(unsigned int &,unsigned int &);

//memory mesurement:
int getVMValue();
int getPMValue();
int parseLine(char* );


//query :
int accept(const unsigned int &,const unsigned int & ,const unsigned int &);
int items(const unsigned int &,const unsigned int &);
int users(const unsigned int &,const unsigned int &,const unsigned int &,const unsigned int &) ;
int acct_ratio(const unsigned int &,const unsigned int &);
int findtime_item(const unsigned int &,vector<unsigned int> &);


#endif // XSTRUCT_HPP_INCLUDED
