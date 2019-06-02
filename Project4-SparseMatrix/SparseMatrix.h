#ifndef _SPARSE_MATRIX_H_
#define _SPARSE_MATRIX_H_
#define DEBUG

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <thread>

using namespace std;

class SparseMatrix {
public:
	// nr x nc sparse matrix is constructed. If they are not given, 1x1 matrix by default
	SparseMatrix(int nr = 1, int nc = 1) {
		this->nRow = nr;
		this->nCol = nc;
		rows = vector<vector<pair_cv>>(nr+1,vector<pair_cv>());
	}
	~SparseMatrix() {
		rows.clear();
	}

	// resize the matrix to nr x nc.
	// if increased, the added parts are filled with zeros
	void resize(int nr, int nc);

	int getNumRows() { return nRow; };		   // return number of rows
	int getNumCols() { return nCol; };		   // return number of columns
	int getNumOfNonZeros(); // return number of non-zero elements

	// file access
	// read a sparse matrix from a text file
	// the file format is "row col val"
	bool readFromFile(string filename);
	// data access
	void setValue(int row, int col, double val);			  // write val at (i,j)
	double getValue(int row, int col);						  // read value of (i,j)
	void getSetValue(int row, int col, double val, bool isPlus); // set val at (i,j) with function
	void sort();
	// operations
	SparseMatrix operator+(SparseMatrix &M); // matrix addition
	SparseMatrix operator-(SparseMatrix &M); // matrix subtraction
	SparseMatrix plus_minus(SparseMatrix &M, bool isPlus);
	SparseMatrix operator*(SparseMatrix &M); // matrix multiplication
	bool operator==(SparseMatrix &M);		 // true if all elements are equal
	SparseMatrix operator-();				 // inverting the sign of all elements

	// summary
	double rowSum(int row);			   // calculate the sum of elements in a "row"-th row
	double colSum(int col);			   // calculate the sum of elements in a "col"-th column
	double sum();					   // calculate the sum of all elements
	bool isAllAbsLessThan(double val); // true if the absolute value of all elements are less than val
	//print
	void print();

	typedef pair<int, double> pair_cv;
	vector<vector<pair_cv>> rows;

private:
	// declare whatever you want
	int nRow, nCol, nNzero;
	void setVal(uint32_t row, uint32_t col, double val); // setValues without sortbool
};

#endif
