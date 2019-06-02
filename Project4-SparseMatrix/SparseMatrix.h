#ifndef _SPARSE_MATRIX_H_
#define _SPARSE_MATRIX_H_
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

class SparseMatrix {
public:
	// nr x nc sparse matrix is constructed. If they are not given, 1x1 matrix by default
	SparseMatrix(int nr = 1, int nc = 1) {
		this->nRow = nr;
		this->nCol = nc;
		rows = vector_rows(nr+1,vector<pair_cv>());
	}
	~SparseMatrix() {
		rows.clear();
	}

	typedef pair<int, double> pair_cv;
	typedef vector<vector<pair_cv>> vector_rows;
	
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
	void plus_minus_part(vector_rows *rows_part, SparseMatrix *tmp, bool isPlus, int from, mutex *mtx);
	SparseMatrix operator*(SparseMatrix &M); // matrix multiplication
	SparseMatrix multiply(SparseMatrix &M);
	bool operator==(SparseMatrix &M);		 // true if all elements are equal
	SparseMatrix operator-();				 // inverting the sign of all elements
	
	// summary
	double rowSum(int row);			   // calculate the sum of elements in a "row"-th row
	double colSum(int col);			   // calculate the sum of elements in a "col"-th column
	double sum();					   // calculate the sum of all elements
	bool isAllAbsLessThan(double val); // true if the absolute value of all elements are less than val
	//print
	void print();


private:
	// declare whatever you want
	int nRow, nCol, core;
	void setVal(uint32_t row, uint32_t col, double val); // setValues without sortbool
	vector_rows rows;
};

#endif
