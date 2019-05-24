#include "SparseMatrix.h"

void SparseMatrix::sort_row(int left, int right) {
	if (left >= right) return;
	double pivot = rows[right];
	int cnt = left;
	for (int i = left; i <= right; i++) {
		if (rows[i] <= pivot) {
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
	double pivot = cols[right];
	int cnt = left;
	for (int i = left; i <= right; i++) {
		if (cols[i] <= pivot) {
			swap(cols[cnt], cols[i]);
			swap(vals[cnt], vals[i]);
			cnt++;
		}
	}
	sort_col(left, cnt - 2);
	sort_col(cnt, right);
}

void SparseMatrix::sort() {
	int size = vals.size() - 1;
	sort_row(0, size);
	vector<int>::iterator iter;
	int start = 0;
	for (int i = 0; i < rows.size(); i++) {
		if (rows[start] != rows[i]) {
			sort_col(start, i - 1);
			start = i;
		}
	}
}
void SparseMatrix::setValue(int row, int col, double val) {
	vals.push_back(val);
	rows.push_back(row);
	cols.push_back(col);
	//cout<< "set " ; print();
	sort();
	cout << "sort ";
	IA[row] += 1;
	print();
}

void SparseMatrix::print() {
	cout << "row:[";
	for (int i = 0; i < vals.size(); i++) {
		cout  << rows[i] << " " ;
	}
	cout << "] col:[";
	for (int i = 0; i < vals.size(); i++) {
		cout << cols[i] << " ";
	}
	cout << "] val:[";
	for (int i = 0; i < vals.size(); i++) {
		cout << vals[i] << " ";
	}
	cout <<  "] IA:[";
	for (int i = 0; i < IA.size(); i++) {
		cout <<  IA[i] << " " ;
	}
	cout << "]" << endl;
}

double SparseMatrix::getValue(int row, int col) {
	for (int pos = 0; pos < vals.size(); pos++) {
		if (rows[pos] == row && cols[pos] == col)
			return vals[pos];
	}
	return 0;
}

void SparseMatrix::resize(int nr, int nc) {
	for (int pos = 0; pos < vals.size(); pos++) {
		if (rows[pos] > nr || cols[pos] > nc) {
			rows.erase(rows.begin() + pos);
			cols.erase(cols.begin() + pos);
			vals.erase(vals.begin() + pos);
		}
	}
	nCol = nc;
	nRow = nr;
	IA.resize(nr+1, 0);
	sort();
}

bool SparseMatrix::readFromFile(string filename) {
	return false;
}

SparseMatrix SparseMatrix::operator+(SparseMatrix &M) {
	SparseMatrix tmp;
	int a=0,b=0;
	for (int pos = 0; pos < vals.size() + M.vals.size(); pos++) {
		int row_a = rows[a];
		int row_b = M.rows[b];
		if (row_a == row_b) {

		} else if (row_a < row_b) {

		} else {
		}
	}
	return tmp;
}

SparseMatrix SparseMatrix::operator-(SparseMatrix &M) {
	SparseMatrix tmp;
	return tmp;
}

SparseMatrix SparseMatrix::operator*(SparseMatrix &M) {
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