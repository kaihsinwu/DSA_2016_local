#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <sys/stat.h>
using namespace std;

/*
    b01202014 Kai-Hsin Wu 2016/03
    Simple version of Inverse Square Matrix
    Reqirement :
        -rank 2
        -dimensions for each rank 0 < n < 201
        -Ipt is non singular
    Input argument needed:
        - Path of input matrix file
*/

//debug routine
template<typename Tpy>
void printMatrix(Tpy **Mat,int drow,int dcol){
    cout << "Matrix :" << endl
         <<" row : "<< drow <<" col : "<< dcol;
    for(int i=0;i<drow;i++){
        cout << endl;
        for(int j=0;j<dcol;j++)
            cout <<setprecision(1)<<Mat[i][j] << "\t";
     }
    cout << endl;
}

double invmat(double **, double **, int );
double Max_error(double **,double **,int );

int main(int argc,char *argv[]){


    int n;
    double **M , **invM ,**M_LUform;
    double Norm;

   
    //input matrix :
    cin >> n;

    if(n<=0 ){
        cout << "#ERROR: please enter the correct dimension. Exit";
        exit(0);
    }

    //malloc 2D array
    M = (double**)malloc( n*sizeof(double*) ); // original;
    M_LUform = (double**)malloc( n*sizeof(double*) ); //to reshape to LU form
    invM = (double**)malloc( n*sizeof(double*) );
    for(int i=0;i<n;i++){
        M[i] = (double*)malloc( n*sizeof(double) );
        M_LUform[i] = (double*)malloc( n*sizeof(double) );
        invM[i] = (double*)calloc( n,sizeof(double) );
    }

    //read
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> M[i][j];
            //identity matrix
            if(i==j)
                invM[i][j]=1;
        }
        memcpy(M_LUform[i],M[i],n*sizeof(double));
    }


    //find inversion
    Norm=invmat(M_LUform,invM,n);


    //debug:
    /*
    cout << "Read from stdin.";
    cout << "Dimension = " << n << endl;
    cout << "input matrix M" << endl;
        printMatrix(M,n,n);

    cout << "M.LUform" << endl;
        printMatrix(M_LUform,n,n);
    */


    //print max error::

    {
        double merr;
        merr=Max_error(M,invM,n);
        cout << setprecision(8)<< merr << endl;
    }

    //cout result :
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
        	cout << setprecision(8)<< invM[i][j] << "\t" ;
        cout << endl;
    }


    //release mem.
    for(int i=0;i<n;i++){
        free(M[i]);
        free(invM[i]);
        free(M_LUform[i]);
    }
    free(M);
    free(invM);
    free(M_LUform);



    
    return 0;

}

double invmat(double **A , double **B ,int d){
    /**
        Implementation using LU decomp method
        and return the norm of A.
        $NOTE$ norm = 0 iif A is singular.
    */

    //LU decomp
    for(int itr=0;itr<d-1;itr++){
        //process row of downline
        for(int r=itr+1;r<d;r++){
            //pilot term:
            A[r][itr] = A[r][itr] / A[itr][itr];
            //process the elems in a row
            for(int c=itr+1;c<d;c++)
                A[r][c] = A[r][c] - A[r][itr] * A[itr][c];
        }

    }

    //LD = I
    for(int bcol=0; bcol<d; bcol++)
        for(int bce=1; bce<d; bce++)
            for(int itr=0; itr<bce; itr++)
                B[bce][bcol] -= A[bce][itr] * B[itr][bcol];

    //UinvA = D
    for(int bcol=0; bcol<d; bcol++)
        for(int bce=0; bce<d; bce++){
            for(int itr=0; itr<bce; itr++)
                B[(d-1)-bce][bcol] -= A[(d-1)-bce][(d-1)-itr] * B[(d-1)-itr][bcol];
            B[(d-1)-bce][bcol]/=A[(d-1)-bce][(d-1)-bce];

        }

    //calculate norm:
    double norm=1;
    for(int i=0;i<d;i++)
        norm*=A[i][i];

    return norm;

}

double Max_error(double **A,double **invA,int d){
    double itr,err=0;
    for(int i=0;i<d;i++)
        for(int j=0;j<d;j++){
                itr=0;
                for(int k=0;k<d;k++)
                    itr += A[i][k] * invA[k][j];
                if(i==j)
                    itr-=1;
                if(abs(itr)>abs(err)) err = itr;
        }

    return err;

}
