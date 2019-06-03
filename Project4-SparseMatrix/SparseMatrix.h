#ifndef _SPARSE_MATRIX_H_
#define _SPARSE_MATRIX_H_
#define DEBUG

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class SparseMatrix {
public:
	// nr x nc sparse matrix is constructed. If they are not given, 1x1 matrix by default
	SparseMatrix(int nr = 1, int nc = 1) {
		this->nRow = nr;
		this->nCol = nc;
		rows = vector_rows(nr + 1);
		for (auto &i : rows) {
			i = new vector<pair_cv>();
		}
	}
	~SparseMatrix() {
		for (auto &i : rows) {
			delete i;
		}
		rows.shrink_to_fit();
	}

	typedef pair<int, double> pair_cv;
	typedef map<int, double> map_cv;
	typedef vector<vector<pair_cv> *> vector_rows;
	vector_rows rows;
	// resize the matrix to nr x nc.
	// if increased, the added parts are filled with zeros
	void resize(int nr, int nc);

	int getNumRows() { return nRow; }; // return number of rows
	int getNumCols() { return nCol; }; // return number of columns
	int getNumOfNonZeros();			   // return number of non-zero elements

	// file access
	// read a sparse matrix from a text file
	// the file format is "row col val"
	bool readFromFile(string filename);
	// data access
	void setValue(int row, int col, double val);				 // write val at (i,j)
	double getValue(int row, int col);							 // read value of (i,j)
	void getSetValue(int row, int col, double val, bool isPlus); // set val at (i,j) with function

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
	

private:
	// declare whatever you want
	int nRow, nCol;
};

#endif
