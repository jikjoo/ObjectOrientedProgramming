#ifndef _SPARSE_MATRIX_H_
#define _SPARSE_MATRIX_H_
#define DEBUG

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SparseMatrix {
public:
	// nr x nc sparse matrix is constructed. If they are not given, 1x1 matrix by default
	SparseMatrix(int nr = 1, int nc = 1) {
		this->nRow = nr;
		this->nCol = nc;
		IA = vector<int>(nRow+1);
	}
	~SparseMatrix() {
		rcvs.clear();
		IA.clear();
	}

	// resize the matrix to nr x nc.
	// if increased, the added parts are filled with zeros
	void resize(int nr, int nc);

	int getNumRows() { return nRow; };				// return number of rows
	int getNumCols() { return nCol; };				// return number of columns
	int getNumOfNonZeros() { return rcvs.size(); }; // return number of non-zero elements

	// file access
	// read a sparse matrix from a text file
	// the file format is "row col val"
	bool readFromFile(string filename);

	// data access
	void setValue(int row, int col, double val); // write val at (i,j)
	double getValue(int row, int col);			 // read value of (i,j)
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

private:
	// declare whatever you want
	int nRow, nCol;
	void setVal(int row, int col, double val); // setValues without sortbool
	vector<int> IA;
	struct rcv {
		int row;
		int col;
		double val;
		/* data */
	};
	static bool compRowCol(const rcv &a, const rcv &b) {
		return a.row < b.row;
	};
	vector<rcv> rcvs;
};

#endif
