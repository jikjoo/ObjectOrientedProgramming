#ifndef _MATRIX_H_
#define _MATRIX_H_

// matrix data structure
struct Matrix {
	int nrow, ncol;
	double *data;
};

// matrix init and clear
bool matrix_init(Matrix &M,int nrow,int ncol);
void matrix_clear(Matrix &M);

// matrix arithmetics
void matrix_fill_randint(Matrix &M,int start=0,int end=9);
bool matrix_add(Matrix &A,Matrix &B); // A = A+B
bool matrix_multiply(Matrix &A,Matrix &B); // A = AB
bool matrix_transpose(Matrix &A); // A = t(A);

// show
void matrix_show(Matrix &A);

#endif
