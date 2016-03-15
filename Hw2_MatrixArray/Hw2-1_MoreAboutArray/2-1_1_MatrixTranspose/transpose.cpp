#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <random>

using namespace std;



int main(int argc ,char *argv[]){

    if(argc<2){
        cout << "please give the dimension argument. EXIT";
        exit(0);
    }

    srand(99);

    int n=atoi(argv[1]);
    float M[n][n];

    //random creat
    cout << endl;
    cout << "Before: " << endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            M[i][j]=static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/65535));
            cout << M[i][j] << "\t";
        }
        cout <<  "\n";
    }
    //transpose using swap
    float tmp;
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            tmp=M[i][j];
            M[i][j]=M[j][i];
            M[j][i]=tmp;
        }
    }


    //print final array :
    cout << endl;
    cout << "After: " << endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << M[i][j] << "\t";
        }
        cout <<  "\n";
    }






    return 0;


}



