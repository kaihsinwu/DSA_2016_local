#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <ctime>
#include "xstruct.hpp"
#include <vector>
using namespace std;

int main(int argc,char* argv[]){

    const clock_t begin_time = clock();
// do something

    mMap ID_idx;
    vector<vector<unsigned int>> dbase;




    cout << "elements #: "<<test_format(ID_idx,dbase) << endl;
    cout << "execution time "<<float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s\n";
    cout << "OK" <<endl;

    return 0;
}
