#include <iostream>
#include <cstdlib>
#include "matrix.h"

using namespace std;

bool matrix_init(Matrix &M,int nrow,int ncol)
{
	M.nrow = nrow;
	M.ncol = ncol;
	M.data = new double[nrow*ncol]; // new is malloc in C
	if( M.data == NULL ) return false;
	return true;
}

void matrix_clear(Matrix &M)
{
	M.nrow = M.ncol = 0;
	delete[] M.data;	// delete is free in C
	M.data = NULL;
}

void matrix_fill_randint(Matrix &M,int start,int end)
{
	for( int i=0 ; i<M.nrow*M.ncol ; i++ ) {
		M.data[i] = rand()%(end-start+1)+start ;
	}
}

// A <- A+B, return true if succeeds. return false for any failure
bool matrix_add(Matrix &A,Matrix &B)
{
	if(A.nrow==B.nrow && A.ncol==B.ncol){
		for(int i=0; i<A.nrow*A.ncol; i++){
			A.data[i] = A.data[i]+B.data[i];
		}
	return true;
	}
	else return false;

}

// A <- A*B, return true if succeeds. return false for any failure
bool matrix_multiply(Matrix &A,Matrix &B)
{
	if(A.ncol == B.nrow){	
		Matrix T;
		matrix_init(T,A.nrow,B.ncol);
		for(int i = 0; i < A.nrow; i++){
			for(int j=0; j<B.ncol; j++){
				int temp = 0;
				for(int k =0; k< A.ncol; k++){
					temp += A.data[i*A.nrow+k]*B.data[k*B.ncol+j];
				}
				T.data[i*A.nrow+j] = temp;
			}
		}
		A=T;
		matrix_clear(T);
		return true;
	}
	else return false;

}

// A <- t(A), return true if succeeds. return false for any failure
bool matrix_transpose(Matrix &A)
{
	Matrix T;
	matrix_init(T,A.ncol,A.nrow);
	for(int i=0; i<A.nrow;i++){
		for(int j=0; j<A.ncol;j++){
			T.data[j*A.ncol+i] = A.data[i*A.nrow+j];
		}
	}
	A=T;
	return true;
}

// show a matrix
void matrix_show(Matrix &M)
{
	for(int i=0; i < M.nrow; i++){
		for(int j=0; j < M.ncol; j++){
			cout << M.data[i*M.nrow + j] << "	";
		}
		cout << "\n";
	}
}


