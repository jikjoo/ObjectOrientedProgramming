#include "SparseMatrix.h"

void SparseMatrix::setValue(int row, int col, double val) {
	if (val == 0 || row > nRow) return;
	rows[row].emplace_back(col, val);
	return;
}

double SparseMatrix::getValue(int row, int col) {
	for (auto &cv : rows[row]) {
		if (cv.first == col) return cv.second;
	}
	return 0;
}

void SparseMatrix::resize(int nr, int nc) {
	rows.resize(nr + 1);
	if (nCol > nc) {
		for (int r = 1; r < nr; r++) {
			for (auto icv = rows[r].begin(); icv != rows[r].end(); ++icv) {
				if (icv->first > nc) {
					rows[r].erase(icv);
				}
			}
		}
	}
	nCol = nc;
	nRow = nr;
}
bool SparseMatrix::readFromFile(string filename) {
	uint32_t row;
	uint32_t col;
	double val;
	int maxcol = 0;
	ifstream infile(filename.c_str());
	while (infile >> row >> col >> val) {
		if (nRow < row) resize(row, nCol);
		if (maxcol < col) maxcol = col;
		setValue(row, col, val);
	}
	resize(nRow, maxcol);
#ifdef DEBUG
	cout << filename << " file loaded" << endl;
#endif
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
	if (nRow != M.nRow || nCol != M.nCol) return tmp;
	for (int r = 1; r <= nRow; r++) {
		unordered_map<int,double> tmp_cols;
		for (auto &cva : rows[r]) {
			int col_a = cva.first;
			double val_a = cva.second;
			tmp_cols[col_a] = val_a;
		}
		for (auto &cvb : M.rows[r]) {
			int col_b = cvb.first;
			double val_b = cvb.second;
			tmp_cols[col_b] = isPlus? tmp_cols[col_b] + val_b : tmp_cols[col_b] - val_b;
		}
		for(auto &tmpc : tmp_cols){
			tmp.setValue(r,tmpc.first,tmpc.second);
		}
	}
	return tmp;
}

SparseMatrix SparseMatrix::operator*(SparseMatrix &M) {
	SparseMatrix tmp(nRow, M.nCol);
	if (nCol != M.nRow) return tmp;
	for (int ra = 1; ra <= nRow; ra++) {
		unordered_map<int,double> tmp_cols;
		for (auto &cva : rows[ra]) {
			int col_a = cva.first;
			double val_a = cva.second;
			for (auto &cvb : M.rows[col_a]) {
				int col_b = cvb.first;
				double val_b = cvb.second;
				double new_val = val_a * val_b;
				tmp_cols[col_b] += new_val;
			}
		}
		for(auto &tmpc : tmp_cols){
			tmp.setValue(ra,tmpc.first,tmpc.second);
		}
	}
	return tmp;
}

bool SparseMatrix::operator==(SparseMatrix &M) {
	if (nRow != M.nRow || nCol != M.nCol)
		return false;
	if (getNumOfNonZeros() != M.getNumOfNonZeros()) {
		return false;
	}
	for (int r = 1; r <= nRow; r++) {
		for (auto &cv : rows[r]) {
			if (cv.second != cv.second)
				return false;
		}
	}
	return true;
}

SparseMatrix SparseMatrix::operator-() {
	SparseMatrix tmp = *this;
	for (int r = 1; r <= nRow; r++) {
		for (auto &cv : rows[r]) {
			cv.second = -cv.second;
		}
	}
	return tmp;
}

int SparseMatrix::getNumOfNonZeros() {
	int nNzero = 0;
	for (int r = 1; r <= nRow; r++) {
		nNzero += rows[r].size();
	}
	return nNzero;
}

double SparseMatrix::rowSum(int row) { // calculate the sum of elements in a "row"-th row
	double sum = 0;
	for (auto &cv : rows[row]) {
		sum += cv.second;
	}
	return sum;
}
double SparseMatrix::colSum(int col) { // calculate the sum of elements in a "col"-th column
	double sum = 0;
	for (int r = 1; r <= nRow; r++) {
		for (auto &cv : rows[r]) {
			if (cv.first == col)
				sum += cv.second;
		}
	}
	return sum;
}
double SparseMatrix::sum() { // calculate the sum of all elements
	double sum = 0;
	for (int r = 1; r <= nRow; r++) {
		for (auto &cv : rows[r]) {
			sum += cv.second;
		}
	}
	return sum;
}
bool SparseMatrix::isAllAbsLessThan(double val) {
	for (int r = 1; r <= nRow; r++) {
		for (auto &cv : rows[r]) {
			if (cv.second > val) {
				cout << "false at (" << r << "," << cv.first << "," << cv.second << ")" << endl;
				return false;
			}
		}
	}
	return true;
}

void SparseMatrix::print() {
#ifdef DEBUG
	cout << "  nRow: " << nRow << " nCol: " << nCol << endl;
	for (int r = 1; r <= nRow; r++) {
		if (!rows[r].empty()) cout << "rows: " << r;
		for (auto &cv : rows[r]) {
			cout << " (col: " << cv.first
				 << " val: " << cv.second << ")";
		}
		cout << endl;
	}
#endif
}
