#include "SparseMatrix.h"
void SparseMatrix::sort() {
	std::sort(rcvs.begin(), rcvs.end(), this->compRowCol);
}

void SparseMatrix::setVal(int row, int col, double val) {
	if (val == 0) return;
	rcv _rcv = {row, col, val};
	rcvs.push_back(_rcv);
}

void SparseMatrix::setValue(int row, int col, double val) {
	for (int i = 0; i < rcvs.size(); i++) { // check duplicate
		if (rcvs[i].row == row && rcvs[i].col == col) {
			rcvs.erase(rcvs.begin() + i);
		}
		else if(rcvs[i].row > row) break;
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
		else if (rcvs[pos].row > row)
			return 0;
	}
	return 0;
}

void SparseMatrix::resize(int nr, int nc) {
	if (nRow > nr || nCol > nc) {
		for (int pos = 0; pos < rcvs.size(); pos++) {
			if (rcvs[pos].row > nr || rcvs[pos].col > nc) {
				rcvs.erase(rcvs.begin() + pos);
			}
		}
	}
	nCol = nc;
	nRow = nr;
}

bool SparseMatrix::readFromFile(string filename) {
	ifstream infile(filename.c_str());
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

//operator
SparseMatrix SparseMatrix::operator+(SparseMatrix &M) {
	return plus_minus(M, true);
}

SparseMatrix SparseMatrix::operator-(SparseMatrix &M) {
	return plus_minus(M, false);
}

SparseMatrix SparseMatrix::plus_minus(SparseMatrix &M, bool isPlus) {
	SparseMatrix tmp(nRow, nCol);
	int size_a = rcvs.size();
	int size_b = M.rcvs.size();
	for (int a = 0; a < size_a; a++) {
		int &row_a = rcvs[a].row;
		double &val_a = rcvs[a].val;
		int &col_a = rcvs[a].col;
		tmp.setVal(row_a, col_a, val_a);
	}
	for (int b = 0; b < size_b; b++) {
		int &row_b = M.rcvs[b].row;
		int &col_b = M.rcvs[b].col;
		double &val_b = M.rcvs[b].val;
		double new_val = tmp.getValue(row_b, col_b);
		new_val = isPlus ? new_val + val_b : new_val - val_b;
		tmp.setValue(row_b, col_b, new_val);
	}
	return tmp;
}

SparseMatrix SparseMatrix::operator*(SparseMatrix &M) {
	SparseMatrix tmp(nRow, M.nCol);
	int size_a = rcvs.size();
	int size_b = M.rcvs.size();
	vector<int> cp(nCol + 1,0); // cp : col_a = row_b
	for (int a = 0; a < size_a; a++) {
		int &col_a = rcvs[a].col;
		cp[col_a] = 1;
	}
	for (int b = 0; b < size_b; b++) {
		int &row_b = M.rcvs[b].row;
		if(cp[row_b] == 1) cp[row_b] = 2;
	}
	for (int a = 0; a < size_a; a++) {
		int &row_a = rcvs[a].row;
		int &col_a = rcvs[a].col;
		double &val_a = rcvs[a].val;
		if (cp[col_a] > 1) {
			for (int b = 0; b < size_b; b++) {
				int &row_b = M.rcvs[b].row;
				int &col_b = M.rcvs[b].col;
				double &val_b = M.rcvs[b].val;
				if (col_a == row_b) {
					double new_val = tmp.getValue(row_a, col_b) + val_a * val_b;
					tmp.setValue(row_a, col_b, new_val);
				}
				else if(row_b > col_a) break;
			}
		}
	}
	return tmp;
}

bool SparseMatrix::operator==(SparseMatrix &M) {
	for (int i = 0; i < rcvs.size(); i++) {
		int &row = rcvs[i].row;
		int &col = rcvs[i].col;
		double &val = rcvs[i].val;
		if (val != M.getValue(row, col)) return false;
	}
	return true;
}

SparseMatrix SparseMatrix::operator-() {
	SparseMatrix tmp;
	tmp.rcvs = this->rcvs;
	for (int i = 0; i < rcvs.size(); i++) {
		tmp.rcvs[i].val = -tmp.rcvs[i].val;
	}
	return tmp;
}

double SparseMatrix::rowSum(int row) { // calculate the sum of elements in a "row"-th row
	double sum = 0;
	for (int i = 0; i < rcvs.size(); i++) {
		if (rcvs[i].row == row)
			sum += rcvs[i].val;
	}
	return sum;
}
double SparseMatrix::colSum(int col) { // calculate the sum of elements in a "col"-th column
	double sum = 0;
	for (int i = 0; i < rcvs.size(); i++) {
		if (rcvs[i].col == col)
			sum += rcvs[i].val;
	}
	return sum;
}
double SparseMatrix::sum() { // calculate the sum of all elements
	double sum = 0;
	for (int i = 0; i < rcvs.size(); i++) {
		sum += rcvs[i].val;
	}
	return sum;
}
bool SparseMatrix::isAllAbsLessThan(double val) {
	for (int i = 0; i < rcvs.size(); i++) {
		if (rcvs[i].val > val) return false;
	}
	return true;
}
