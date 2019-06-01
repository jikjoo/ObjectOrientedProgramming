#include "SparseMatrix.h"

void SparseMatrix::setValue(int row, int col, double val) {
	if (val == 0 || row > nRow) return;
	rows[row].push_back(pair_cv(col, val));
	nNzero++;
	return;
}

double SparseMatrix::getValue(int row, int col) {
	int size = rows[row].size();
	for (int i = 0; i <= size; i++) {
		if (rows[row][i].first == col)
			return rows[row][i].second;
	}
	return 0;
}

void SparseMatrix::getSetValue(int row, int col, double val, bool isPlus) {
	bool dupl = false;
	for (int cv = 0; cv < rows[row].size(); cv++) {
		if (rows[row][cv].first == col) {
			dupl = true;
			double &mval = rows[row][cv].second;
			val = isPlus ? mval + val : mval - val;
			if (val == 0) {
				rows[row].erase(rows[row].begin() + cv);
				return;
			};
			mval = val;
		}
	}
	if (!dupl) setValue(row, col, val);
	return;
}

void SparseMatrix::resize(int nr, int nc) {
	rows.resize(nr + 1);
	if (nCol > nc) {
		for (int i = 1; i < nr; i++) {
			for (int j = 0; j < rows[i].size(); j++) {
				if (rows[i].at(j).first > nc) {
					rows[i].erase(rows[i].begin() + j);
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
	tmp.rows = rows;
	for (int rb = 1; rb <= M.nRow; rb++) {
		for (int cvb = 0; cvb < M.rows[rb].size(); cvb++) {
			int col_b = M.rows[rb][cvb].first;
			double val_b = M.rows[rb][cvb].second;
			tmp.getSetValue(rb, col_b, val_b, isPlus);
		}
	}
	return tmp;
}

SparseMatrix SparseMatrix::operator*(SparseMatrix &M) {
	SparseMatrix tmp(nRow, M.nCol);
	if (nCol != M.nRow) return tmp;
	for (int ra = 1; ra <= nRow; ra++) {
		for (int cva = 0; cva < rows[ra].size(); cva++) {
			uint32_t col_a = rows[ra][cva].first;
			double val_a = rows[ra][cva].second;
			for (int cvb = 0; cvb < M.rows[col_a].size(); cvb++) {
				uint32_t col_b = M.rows[col_a][cvb].first;
				double val_b = M.rows[col_a][cvb].second;
				double new_val = val_a * val_b;
				tmp.getSetValue(ra, col_b, new_val, 0);
			}
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
		for (int cv = 0; cv < rows[r].size(); cv++) {
			if (rows[r][cv].second != M.rows[r][cv].second)
				return false;
		}
	}
	return true;
}

SparseMatrix SparseMatrix::operator-() {
	SparseMatrix tmp = *this;
	for (int r = 1; r <= nRow; r++) {
		for (int cv = 0; cv < rows[r].size(); cv++) {
			rows[r][cv].second = -rows[r][cv].second;
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
	for (int cv = 0; cv < rows[row].size(); cv++) {
		sum += rows[row][cv].second;
	}
	return sum;
}
double SparseMatrix::colSum(int col) { // calculate the sum of elements in a "col"-th column
	double sum = 0;
	for (int r = 1; r <= nRow; r++) {
		for (int cv = 0; cv < rows[r].size(); cv++) {
			if (rows[r][cv].first == col)
				sum += rows[r][cv].second;
		}
	}
	return sum;
}
double SparseMatrix::sum() { // calculate the sum of all elements
	double sum = 0;
	for (int r = 1; r <= nRow; r++) {
		for (int cv = 0; cv < rows[r].size(); cv++) {
			sum += rows[r][cv].second;
		}
	}
	return sum;
}
bool SparseMatrix::isAllAbsLessThan(double val) {
	for (int r = 1; r <= nRow; r++) {
		for (int cv = 0; cv < rows[r].size(); cv++) {
			if (rows[r][cv].second > val) return false;
		}
	}
	return true;
}

void SparseMatrix::print() {
#ifdef DEBUG
	cout << "  nRow: " << nRow << " nCol: " << nCol << endl;
	for (int i = 1; i <= rows.size(); i++) {
		int size = rows[i].size();
		if (size > 0) cout << "rows: " << i;
		for (int j = 0; j < size; j++) {
			cout << " (col: " << rows[i][j].first
				 << " val: " << rows[i][j].second << ")";
		}
		cout << endl;
	}
#endif
}
