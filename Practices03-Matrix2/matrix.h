#ifndef _MATRIX_H_
#define _MATRIX_H_

class Matrix
{
public:
	Matrix(int nr,int nc);
	~Matrix();
	
	// functions in the previous C program
	void fillRandInt(int start=0,int end=9);
	bool add(Matrix &M);
	bool multiply(Matrix &M);
	bool transpose();
	void show();

	// additional functions
	int getNrow();		// return the number of rows
	int getNcol();		// return the number of columns
	// calculate the determinant
	// for a non-square matrix, return 0.
	// for 1 x 1 matrix, return the element of (1,1).
	// for the calculation of n x n matrix determinant
	// refer http://www.mathsisfun.com/algebra/matrix-determinant.html
	double det();	
	int getData(int i);
	void fillData(int i, int val);
	
private:
	double *mData;
	int mNrow, mNcol;
	//double *tempData;
	// add more private variables and functions if you need
};


#endif
