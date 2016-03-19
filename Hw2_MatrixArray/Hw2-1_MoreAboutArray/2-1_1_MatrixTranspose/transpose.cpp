#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <random>

using namespace std;
template<typename Tpy >
class XArray{
    bool tp;
    int rown;
    int coln;
    Tpy *M;


    public:
        XArray(int n,int m){
            tp=0;
            if((n<0 || m<0) || (n==0 && m==0)){
                cout << "ERROR in construct XAarry: init fail, capacity can't be negative and 0";
                exit(0);
            }
            rown=n;
            coln=m;
            M=(Tpy*)malloc(n*m*sizeof(Tpy));
        }

        ~XArray(){

            free(M);

        }

        Tpy& get(int a,int b){


                if(tp){
                    if(a>=coln || b >=rown){
                        cout << "ERROR! index out of bound.";
                        exit(1);
                    }
                    return M[b*rown+a];
                }else{
                    if(b>=coln || a >=rown){
                        cout << "ERROR! index out of bound.";
                        exit(1);
                    }
                    return M[a*rown+b];
                }

        }
        void put(int a,int b,Tpy x){


                if(tp){
                    if(a>=coln || b >=rown){
                        cout << "ERROR! index out of bound.";
                        exit(1);
                    }
                    M[b*rown+a]=x;
                }else{
                    if(b>=coln || a >=rown){
                        cout << "ERROR! index out of bound.";
                        exit(1);
                    }
                    M[a*rown+b]=x;
                }

        }

        void transp(){
            tp=!tp;
        }

        bool istransp(){

            return tp;
        }

        void randomize(int seed){
            srand(seed);
            for(int i=0;i<rown;i++)
                for(int j=0;j<coln;j++)
                    M[i*rown+j]=static_cast <Tpy> (rand()) / (static_cast <Tpy> (RAND_MAX/65535));

        }


};


int main(int argc ,char *argv[]){

    if(argc<2){
        cout << "please give the dimension argument. EXIT";
        exit(0);
    }

    srand(99);
    int n=atoi(argv[1]);

    float M1[n][n];


    //approach 1 : swap one by one
    //random creat
    cout << endl;
    cout << "Before: " << endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            M1[i][j]=static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/65535));
            cout << M1[i][j] << "\t";
        }
        cout <<  "\n";
    }
    //transpose using swap
    float tmp;
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            tmp=M1[i][j];
            M1[i][j]=M1[j][i];
            M1[j][i]=tmp;
        }
    }


    //print final array :
    cout << endl;
    cout << "After: " << endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << M1[i][j] << "\t";
        }
        cout <<  "\n";
    }


    //approch 2 : Class by only change the index (permute)
    XArray<float> M(n,n);

    M.randomize(99);

    cout << endl;
    cout << "Before: " << endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout << M.get(i,j) << "\t";
        cout << endl;
    }

    M.transp();

    cout << endl;
    cout << "After: " << endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout << M.get(i,j) << "\t";
        cout << endl;
    }


    return 0;


}



