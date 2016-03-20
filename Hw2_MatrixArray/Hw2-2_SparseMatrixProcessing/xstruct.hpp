#ifndef XSTRUCT_HPP_INCLUDED
#define XSTRUCT_HPP_INCLUDED
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <map>
#include <vector>
using namespace std;
typedef map<unsigned int,unsigned int> mMap;

int test_format(mMap &,vector<vector<unsigned int>> &);
int getVMValue();
int getPMValue();
int parseLine(char* );
void encode(unsigned int &,bool &);
bool decode(unsigned int &);

#endif // XSTRUCT_HPP_INCLUDED
