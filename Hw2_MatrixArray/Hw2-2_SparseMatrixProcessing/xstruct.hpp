#ifndef XSTRUCT_HPP_INCLUDED
#define XSTRUCT_HPP_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <map>
#include <vector>
using namespace std;

//ID dictionary realization type
typedef map<unsigned int,unsigned int> mMap;

//variable proto
extern  mMap ID_idx;
extern  vector<vector<pair<unsigned int,unsigned int>>> dbase;
extern  unsigned int T_start;
extern  vector<unsigned int> toff2fpos;


unsigned int test_format(mMap &,vector<vector<pair<unsigned int,unsigned int>>> &);

//crypto routine:
unsigned int encode(unsigned int  ,bool );
pair<bool,unsigned int> decode(unsigned int &);

//memory mesurement:
int getVMValue();
int getPMValue();
int parseLine(char* );


//query :
int accept(unsigned int ,unsigned int ,unsigned int );
int items(unsigned int ,unsigned int );
int users(unsigned int ,unsigned int,unsigned int ,unsigned int) ;
int acct_ratio(unsigned int,unsigned int );
int findtime_item(unsigned int,const vector<unsigned int> &);
#endif // XSTRUCT_HPP_INCLUDED
