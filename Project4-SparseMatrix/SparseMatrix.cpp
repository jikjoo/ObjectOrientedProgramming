#include "SparseMatrix.h"
void SparseMatrix::sort() {
	std::sort(rcvs.begin(), rcvs.end(), this->compRowCol);
	// set IA
	int cnt = 0;
	for (int i = 0; i < rcvs.size(); i++) {
		int row = rcvs[i].row;
		int next_row = (i == rcvs.size() - 1) ? nRow + 1 : rcvs[i + 1].row;
		cnt++;
		if (row != next_row) {
			for (int j = row; j < next_row; j++)
				IA[j] = cnt;
		}
	}
	return;
}

void SparseMatrix::setVal(uint32_t row, uint32_t col, double val) {
	if (val == 0) return;
	rcv _rcv = {row, col, val};
	rcvs.push_back(_rcv);
	return;
}
void SparseMatrix::setValue(int row, int col, double val) {
	if (val == 0 || row > nRow || col > nCol) return;
	rcv _rcv = {row, col, val};
	int pos = IA[row];
	rcvs.insert(rcvs.begin() + pos, _rcv);
	for (int i = row; i < IA.size(); i++) {
		IA[i]++;
	}
	return;
}

double SparseMatrix::getValue(int row, int col) {
	for (int pos = IA[row - 1]; pos < IA[row]; pos++) {
		if (rcvs[pos].row == row && rcvs[pos].col == col)
			return rcvs[pos].val;
	}
	return 0;
}

void SparseMatrix::getSetValue(int row, int col, double val, int func) {
	bool dupl = false;
	for (int pos = IA[row - 1]; pos < IA[row]; pos++) {
		if (rcvs[pos].row == row && rcvs[pos].col == col) {
			double mval = rcvs[pos].val;
			val = func == 0 ? mval + val : mval - val;
			dupl = true;
			if (val == 0) {
				rcvs.erase(rcvs.begin() + pos);
				for (int i = row; i < IA.size(); i++)
					--IA[i];
			} else
				rcvs[pos].val = val;
			break;
		}
	}
	if (!dupl) setValue(row, col, val);
	return;
}

void SparseMatrix::resize(int nr, int nc) {
	if (nRow > nr || nCol > nc) {
		for (int pos = 0; pos < rcvs.size(); pos++) {
			if (rcvs[pos].row > nr || rcvs[pos].col > nc) {
				rcvs.erase(rcvs.begin() + pos);
				for (int i = rcvs[pos].row; i < IA.size(); i++) {
					--IA[i];
				}
			}
		}
	}
	IA.resize(nr + 1);
	if (nRow < nr) {
		for (int i = nRow + 1; i < IA.size(); i++) {
			IA[i] = rcvs.size();
		}
	}
	nCol = nc;
	nRow = nr;
}
bool SparseMatrix::readFromFile(string filename) {
	uint32_t row;
	uint32_t col;
	double val;
	int maxrow = 0;
	int maxcol = 0;
	ifstream infile(filename.c_str());
	while (infile >> row >> col >> val) {
		if (maxrow < row) maxrow = row;
		if (maxcol < col) maxcol = col;
		setVal(row, col, val);
	}
	resize(maxrow, maxcol);
	sort();
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
	int size_b = M.rcvs.size();
	tmp.rcvs = rcvs;
	tmp.IA = IA;
	for (int b = 0; b < size_b; b++) {
		uint32_t row_b = M.rcvs[b].row;
		uint32_t col_b = M.rcvs[b].col;
		double val_b = M.rcvs[b].val;
		int func = isPlus ? 0 : 1;
		tmp.getSetValue(row_b, col_b, val_b, func);
	}
	return tmp;
}

SparseMatrix SparseMatrix::operator*(SparseMatrix &M) {
	SparseMatrix tmp(nRow, M.nCol);
	if (nCol != M.nRow) return tmp;
	int size_a = rcvs.size();
	int size_b = M.rcvs.size();
	for (int a = 0; a < size_a; a++) {
		uint32_t row_a = rcvs[a].row;
		uint32_t col_a = rcvs[a].col;
		double val_a = rcvs[a].val;
		for (int b = M.IA[col_a - 1]; b < M.IA[col_a]; b++) {
			uint32_t row_b = M.rcvs[b].row;
			uint32_t col_b = M.rcvs[b].col;
			double val_b = M.rcvs[b].val;
			if (col_a == row_b) {
				double new_val = val_a * val_b;
				tmp.getSetValue(row_a, col_b, new_val, 0);
			}
		}
	}
	return tmp;
}

bool SparseMatrix::operator==(SparseMatrix &M) {
	for (int i = 0; i < rcvs.size(); i++) {
		uint32_t row = rcvs[i].row;
		uint32_t col = rcvs[i].col;
		double val = rcvs[i].val;
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

	for (int i = 0; i < IA.size(); i++) {
		cout << IA[i] << " ";
	}
	cout << "  row : " << nRow << " col : " << nCol << endl;
#endif
}
