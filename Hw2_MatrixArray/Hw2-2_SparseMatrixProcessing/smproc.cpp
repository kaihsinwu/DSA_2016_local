#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <ctime>
#include "xstruct.hpp"
#include <vector>
using namespace std;


mMap ID_idx;
vector<unsigned int> toff2fpos; // save the position of file every 1000 timestemp offset.
vector<vector<pair<unsigned int,unsigned int>>> dbase;
unsigned int T_start;

int main(int argc,char* argv[]){

    clock_t begin_time = clock();
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


    T_start=test_format(ID_idx,dbase);


    int xxx;
    float fxxx;

    cout << "read time "<<float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s\n";
    begin_time=clock();

    xxx = accept(601635,462104,1318348785);//good

    cout << "accept() time "<<float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s\n";
    //cout << "result: "<<xxx << endl;
    begin_time=clock();

    xxx = items(601635,451392);

    cout << "items() time "<<float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s\n";
    //cout << "result: "<<xxx << endl;
    begin_time=clock();

    xxx = users(1774722,563514,1318348785,1318348800);

    cout << "users() time "<<float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s\n";
    begin_time=clock();

    xxx = acct_ratio(1774722,20);

    cout << "acct_ratio() time "<<float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s\n";
    begin_time=clock();

    vector<unsigned int> testv={451392,601635};
    xxx = findtime_item(1774722,testv);

    cout << "acct_ratio() time "<<float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s\n";


    cout << "OK" <<endl;


    return 0;
}
