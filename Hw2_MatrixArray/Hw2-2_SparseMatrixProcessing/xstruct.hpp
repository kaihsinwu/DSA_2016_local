#ifndef XSTRUCT_HPP_INCLUDED
#define XSTRUCT_HPP_INCLUDED
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <map>
using namespace std;
typedef multimap<int, int> mMap;

int test_format(mMap &);
int getVMValue();
int getPMValue();
int parseLine(char* );
#endif // XSTRUCT_HPP_INCLUDED
