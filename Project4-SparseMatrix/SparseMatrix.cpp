#include "SparseMatrix.h"

void SparseMatrix::sort_row(int left, int right) {
	if (left >= right) return;
	double pivot = (*rows)[right];
	int cnt = left;
	for (int i = left; i <= right; i++) {
		if ((*rows)[i] <= pivot) {
			swap(rows[cnt], rows[i]);
			swap(cols[cnt], cols[i]);
			swap(vals[cnt], vals[i]);
			cnt++;
		}
	}
	sort_row(left, cnt - 2);
	sort_row(cnt, right);
}

void SparseMatrix::sort_col(int left, int right) {
	if (left >= right) return;
	double pivot = (*cols)[right];
	int cnt = left;
	for (int i = left; i <= right; i++) {
		if ((*cols)[i] <= pivot) {
			swap((*cols)[cnt], (*cols)[i]);
			swap((*vals)[cnt], (*vals)[i]);
			cnt++;
		}
	}
	sort_col(left, cnt - 2);
	sort_col(cnt, right);
}

void SparseMatrix::sort() {
	int size = vals->size() - 1;
	sort_row(0, size);
	print();
}
void SparseMatrix::setVal(int row, int col, double val) {
	if (val != 0) {
		if (vals == NULL) {
			vals = new vector<double>(1, val);
			cols = new vector<int>(1, col);
			rows = new vector<int>(1, row);
		} else {
			vals->push_back(val);
			cols->push_back(col);
			rows->push_back(row);
		}
	}
}
void SparseMatrix::setValue(int row, int col, double val) {
	/* for (int i = 0; i < vals->size(); i++) { //check duplicate of position
		if ((*rows)[i] == row && (*cols)[i] == col) {
			vals->erase(vals->begin() + i);
			cols->erase(cols->begin() + i);
			rows->erase(rows->begin() + i);
		}
	} */
	setVal(row, col, val);
	//cout<< "set " ; print();
	sort();
	print();
}

void SparseMatrix::print() {
#ifdef DEBUG
	cout << "row:[";
	for (int i = 0; i < vals->size(); i++) {
		cout << (*rows)[i] << " ";
	}
	cout << "] col:[";
	for (int i = 0; i < vals->size(); i++) {
		cout << (*cols)[i] << " ";
	}
	cout << "] val:[";
	for (int i = 0; i < vals->size(); i++) {
		cout << (*vals)[i] << " ";
	}

	cout << "]" << endl;
#endif
}

double SparseMatrix::getValue(int row, int col) {
	for (int pos = 0; pos < vals->size(); pos++) {
		if ((*rows)[pos] == row && (*cols)[pos] == col)
			return (*vals)[pos];
	}
	return 0;
}

void SparseMatrix::resize(int nr, int nc) {
	for (int pos = 0; pos < vals->size(); pos++) {
		if ((*rows)[pos] > nr || (*cols)[pos] > nc) {
			rows->erase(rows->begin() + pos);
			cols->erase(cols->begin() + pos);
			vals->erase(vals->begin() + pos);
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
		rows->push_back(row);
		cols->push_back(col);
		vals->push_back(val);
	}
	//sort();
	return true;
}

SparseMatrix SparseMatrix::operator+(SparseMatrix &M) {
	print();
	M.print();
	SparseMatrix tmp(nRow, nCol);
	int a = 0;
	int b = 0;
	while (a < rows->size() && b < M.rows->size()) {
		int row_a = (*rows)[a];
		int row_b = (*M.rows)[b];
		int col_a = (*cols)[a];
		int col_b = (*M.cols)[b];
		if (row_a == row_b) {
			if (col_a == col_b) {
				int new_val = (*vals)[a] + (*M.vals)[b];
				tmp.setVal(row_a, col_a, (*vals)[a] + (*M.vals)[b]);
				a += 1;
				b += 1;
			} else if (col_a < col_b) {
				tmp.setVal(row_a, col_a, (*vals)[a]);
				a += 1;
			} else {
				tmp.setVal(row_b, col_b, (*M.vals)[b]);
				b += 1;
			}
		} else if (row_a < row_b) {
			tmp.setVal(row_a, col_a, (*vals)[a]);
			a += 1;
		} else {
			tmp.setVal(row_b, col_b, (*M.vals)[b]);
			b += 1;
		}
	}
	tmp.print();
	return tmp;
}

SparseMatrix SparseMatrix::operator-(SparseMatrix &M) {
	print();
	M.print();
	SparseMatrix tmp(nRow, nCol);
	int a = 0;
	int b = 0;
	while (a < rows->size() && b < M.rows->size()) {
		int row_a = (*rows)[a];
		int row_b = (*M.rows)[b];
		int col_a = (*cols)[a];
		int col_b = (*M.cols)[b];
		if (row_a == row_b) {
			if (col_a == col_b) {
				int new_val = (*vals)[a] - (*M.vals)[b];
				if (new_val != 0)
					tmp.setValue(row_a, col_a, (*vals)[a] + (*M.vals)[b]);
				a += 1;
				b += 1;
			} else if (col_a < col_b) {
				tmp.setValue(row_a, col_a, (*vals)[a]);
				a += 1;
			} else {
				tmp.setValue(row_b, col_b, (*M.vals)[b]);
				b += 1;
			}
		} else if (row_a < row_b) {
			tmp.setValue(row_a, col_a, (*vals)[a]);
			a += 1;
		} else {
			tmp.setValue(row_b, col_b, (*M.vals)[b]);
			b += 1;
		}
	}
	tmp.print();
	return tmp;
}

SparseMatrix SparseMatrix::operator*(SparseMatrix &M) {
	print();
	M.print();
	SparseMatrix tmp;
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