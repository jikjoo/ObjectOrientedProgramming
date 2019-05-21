#ifndef _SPARSE_MATRIX_H_
#define _SPARSE_MATRIX_H_

#include <vector>
#include <map>

using namespace std;

class SparseMatrix {
public:
	// nr x nc sparse matrix is constructed. If they are not given, 1x1 matrix by default
	SparseMatrix(int nr = 1, int nc = 1) {
		nRow = nr;
		nCol = nc;
	}
	~SparseMatrix() {
		vals.clear();
		rows.clear();
		cols.clear();
	}

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
	void setValue(int row, int col, double val); // write val at (i,j)
	double getValue(int row, int col);			 // read value of (i,j)

	// operations
	SparseMatrix operator+(SparseMatrix &M); // matrix addition
	SparseMatrix operator-(SparseMatrix &M); // matrix subtraction
	SparseMatrix operator*(SparseMatrix &M); // matrix multiplication
	bool operator==(SparseMatrix &M);		 // true if all elements are equal
	SparseMatrix operator-();				 // inverting the sign of all elements

	// summary
	double rowSum(int row);			   // calculate the sum of elements in a "row"-th row
	double colSum(int col);			   // calculate the sum of elements in a "col"-th column
	double sum();					   // calculate the sum of all elements
	bool isAllAbsLessThan(double val); // true if the absolute value of all elements are less than val

private:
	// declare whatever you want
	vector<double> vals;
	vector<int> rows, cols;
	int nRow, nCol;
	//map<int , double> vals;
	
};

void SparseMatrix::setValue(int row, int col, double val) {
	int idx = row * nCol + col;
	//vals.insert(pair<int, double>(idx, val));
}
double SparseMatrix::getValue(int row, int col){
	vector<int>::iterator iter;
}
#endif
