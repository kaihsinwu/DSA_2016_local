#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

using namespace std;
/**
    class "XLRMatrix"

    -realize the 2D-square triangular array in 1D structure
    -reduce memory usage.
    ERROR code :
    1: init error
        element number is negative or 0

*/
template<typename Tpy>
class XLRMatrix{
    Tpy* M;
    bool tp;
    int D;
    Tpy Zero=0;
    public:
        XLRMatrix(int n,bool type){
            tp=type; // 0 = L 1 = R
            if(n<=0){
                cout << "##ERROR, the element number n can't be negative and 0" <<endl<<"##EXIT!"<< endl;
                exit(1);
            }
            D=n;
            M= (Tpy*)malloc((D*(D+1)/2)*sizeof(Tpy));

        }

        ~XLRMatrix(){
            free(M);
        }

        Tpy& get(int a, int b){
            if(a<0 || b<0 || a>=D || b>=D){
                    cout << "##ERROR, index out of bound."<<endl<<"##EXIT!"<< endl;
                    exit(2);
            }

            if(!tp){
                //L
                if(a<b)
                    return Zero;
                else
                    return M[a*(a+1)/2+b];
            }else{
                //R
                if(a>b)
                    return Zero;
                else
                    return M[a*D-(a-1)*(a)/2+D-1-b];

            }


        }

        void put(int a, int b,Tpy x){
            if(a<0 || b<0 || a>=D || b>=D){
                    cout << "##ERROR, index out of bound."<<endl<<"##EXIT!"<< endl;
                    exit(2);
            }

            if(!tp){
                //L
                if(a<b){
                    cout << "##ERROR, invalid operation on [ "<<a <<" "<<b << " ]will destroy the triangular structure, "<<endl<<"##EXIT!";
                    exit(3);

                }else
                    M[a*(a+1)/2+b]=x;

            }else{
                //R
                if(a>b){
                    cout << "##ERROR, invalid operation on [ "<<a <<" "<<b << " ]will destroy the triangular structure, "<<endl<<"##EXIT!";
                    exit(3);

                }else
                    M[a*D-(a-1)*(a)/2+b]=x;

            }


        }


        void randomize(int seed){

            srand(seed);

            for(int i=0;i<(1+D)*D/2;i++){
                M[i]=static_cast<Tpy> (rand()) / static_cast<Tpy>(RAND_MAX)*65535;
            }

        }





};



int main(int argc,char *argv[]){

    //creat L triangular matrix.
    int n=5;
    XLRMatrix<float> L(n,0);  // type: 0 = Lower tri-array ; 1 = Upper tri-array

    //initialize:
    L.randomize(99);

    //print matrix:
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            printf("%5.6f\t",L.get(i,j));
        cout << endl;
    }

    //change the element:
    L.put(1,0,3);


    //print matrix:
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            printf("%5.6f\t",L.get(i,j));
        cout << endl;
    }


    return 0;

}
