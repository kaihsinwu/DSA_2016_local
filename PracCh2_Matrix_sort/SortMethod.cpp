#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <random>
using namespace std;
#define seed 99

mt19937 mt_engine(seed);
uniform_int_distribution<int> uniint(0,3000);



template<typename Tpy,size_t SzOfArr>
void PrintArray(Tpy (&A)[SzOfArr]){
    //cout << SzOfArr<< endl;
    for(int i=0;i<SzOfArr;i++)
        cout << setprecision(3)<<A[i] << "\t";
    cout << endl;
}

template<typename Tpy2,size_t sz2>
void Simple_Sort(Tpy2 (&Ipt)[sz2]){
    if(sz2==0){
        cout << "#######################################" <<endl;
        cout << "### Warning! -: void Simple_Sort()  ###" <<endl;
        cout << "### --Empty elements of ipt array.  ###" <<endl;
        cout << "### --       no operation.          ###" <<endl;
        cout << "#######################################" <<endl;
    }else{
        Tpy2 tmp;
        for(int i=0;i<sz2;i++){
            for(int j=i;j>0;j--){
                if(Ipt[j-1] <= Ipt[j]){
                    //cout << i << "\t" << j << Ipt[j-1] <<  "\t"<<Ipt[j] <<endl;
                    tmp= Ipt[j-1];
                    Ipt[j-1]=Ipt[j];
                    Ipt[j]=tmp;
                }
            }
        }
    }
}

template<typename Tpy3,size_t sz3>
void Selection_Sort(Tpy3 (&Ipt)[sz3]){
    if(sz3==0){
        cout << "#########################################" <<endl;
        cout << "### Warning! -: void Selection_Sort() ###" <<endl;
        cout << "### --Empty elements of ipt array.    ###" <<endl;
        cout << "### --       no operation.            ###" <<endl;
        cout << "#########################################" <<endl;
    }else{
        Tpy3 tmp,comp;
        int idx;
        for(int i=0;i<sz3;i++){
            comp=Ipt[i];
            idx=i;
            for(int j=i+1;j<sz3;j++){
                if(Ipt[j]>comp){
                    comp=Ipt[j];
                    idx=j;
                }
            }
            tmp=Ipt[i];
            Ipt[i]=comp;
            Ipt[idx]=tmp;

        }

    }


}



int main(int argc,char* argv[]){

    double A[]={5,9,3,4,5,3,2};
    cout << "Selection Sort:" << endl;

    cout << "Before: ";
    PrintArray(A);

    Selection_Sort(A);

    cout << "After:  ";
    PrintArray(A);



    double B[]={5,9,3,4,5,3,2};
    cout << "Simple Sort:" << endl;

    cout << "Before: ";
    PrintArray(B);

    Simple_Sort(B);

    cout << "After:  ";
    PrintArray(B);


    return 0;
}


