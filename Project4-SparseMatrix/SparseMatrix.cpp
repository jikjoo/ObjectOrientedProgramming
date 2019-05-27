#include "SparseMatrix.h"

void SparseMatrix::sort() {
	std::sort(rcvs.begin(), rcvs.end(), this->compRowCol);
}

void SparseMatrix::setVal(int row, int col, double val) {
	if (val == 0) return;
	rcvs.push_back({row, col, val});
}

void SparseMatrix::setValue(int row, int col, double val) {
	for (int i = 0; i < rcvs.size(); i++) { // check duplicate
		if (rcvs[i].row == row && rcvs[i].col == col) {
			rcvs.erase(rcvs.begin() + i);
		}
	}
	setVal(row, col, val);
	sort();
}

void SparseMatrix::print() {
#ifdef DEBUG
	cout << "row:[";
	for (int i = 0; i < rcvs.size(); i++) {
		cout << rcvs[i].row << " ";
	}
	cout << "] col:[";
	for (int i = 0; i < rcvs.size(); i++) {
		cout << rcvs[i].col << " ";
	}
	cout << "] val:[";
	for (int i = 0; i < rcvs.size(); i++) {
		cout << rcvs[i].val << " ";
	}

	cout << "]" << endl;
#endif
}

double SparseMatrix::getValue(int row, int col) {
	for (int pos = 0; pos < rcvs.size(); pos++) {
		if (rcvs[pos].row == row && rcvs[pos].col == col)
			return rcvs[pos].val;
	}
	return 0;
}

void SparseMatrix::resize(int nr, int nc) {
	for (int pos = 0; pos < rcvs.size(); pos++) {
		if (rcvs[pos].row > nr || rcvs[pos].col > nc) {
			rcvs.erase(rcvs.begin() + pos);
		}
	}
	nCol = nc;
	nRow = nr;
	sort();
}

bool SparseMatrix::readFromFile(string filename) {
	ifstream infile(filename);
	if (!infile.is_open()) {
		cout << "can not open";
		return false;
	}
	int row;
	int col;
	double val;
	while (infile >> row >> col >> val) {
		if (nRow < row) resize(row, nCol);
		if (nCol < col) resize(nRow, col);
		setVal(row, col, val);
	}
	sort();
	return true;
}

SparseMatrix SparseMatrix::operator+(SparseMatrix &M) {
	return plus_minus(M, true);
}

SparseMatrix SparseMatrix::operator-(SparseMatrix &M) {
	return plus_minus(M, false);
}

SparseMatrix SparseMatrix::plus_minus(SparseMatrix &M, bool isPlus) {
	SparseMatrix tmp(nRow, nCol);
	int a = 0;
	int b = 0;
	while (a < rcvs.size() && b < M.rcvs.size()) {
		int &row_a = rcvs[a].row;
		int &row_b = M.rcvs[b].row;
		int &col_a = rcvs[a].col;
		int &col_b = M.rcvs[b].col;
		double &val_a = rcvs[a].val;
		double &val_b = M.rcvs[b].val;
		if (row_a == row_b) {
			if (col_a == col_b) {
				double new_val = isPlus ? val_a + val_b : val_a - val_b;
				tmp.setVal(row_a, col_a, new_val);
				a += 1;
				b += 1;
			} else if (col_a < col_b) {
				tmp.setVal(row_a, col_a, val_a);
				a += 1;
			} else {
				tmp.setVal(row_b, col_b, val_b);
				b += 1;
			}
		} else if (row_a < row_b) {
			tmp.setVal(row_a, col_a, val_a);
			a += 1;
		} else {
			tmp.setVal(row_b, col_b, val_b);
			b += 1;
		}
	}
	return tmp;
}

SparseMatrix SparseMatrix::operator*(SparseMatrix &M) {
	SparseMatrix tmp(nRow, M.nCol);
	int a = 0;
	int b = 0;
	double new_val = 0;
	int size_a = rcvs.size();
	int size_b = M.rcvs.size();
	for (; a < size_a; a++) {
		int &row_a = rcvs[a].row;
		int &col_a = rcvs[a].col;
		double &val_a = rcvs[a].val;

		for (b = 0; b < size_b; b++) {
			int &row_b = M.rcvs[b].row;
			int &col_b = M.rcvs[b].col;
			double &val_b = M.rcvs[b].val;
			if (col_a == row_b) {
				new_val = tmp.getValue(row_a, col_b) + val_a * val_b;
				tmp.setValue(row_a, col_b, new_val);
			}
		}
	}
	return tmp;
}

bool SparseMatrix::operator==(SparseMatrix &M) {
	return false;
}

SparseMatrix SparseMatrix::operator-() {
	SparseMatrix tmp;
	return tmp;
}

double SparseMatrix::rowSum(int row) { // calculate the sum of elements in a "row"-th row
	return 0;
}
double SparseMatrix::colSum(int col) { // calculate the sum of elements in a "col"-th column
	return 0;
}
double SparseMatrix::sum() { // calculate the sum of all elements
	return 0;
}
bool SparseMatrix::isAllAbsLessThan(double val) {
	return false;
}