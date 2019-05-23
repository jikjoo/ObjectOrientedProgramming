#include "SparseMatrix.h"

void SparseMatrix::sort_row(int left, int right){
	if(left >= right) return;
	double pivot = rows[right];
	int cnt = left;
	for(int i= left; i <= right; i++){
		if(rows[i] <= pivot){
			swap(rows[cnt], rows[i]);
			swap(cols[cnt], cols[i]);
			swap(vals[cnt], vals[i]);
			cnt++;
		}
	}
	sort_row(left,cnt-2);
	sort_row(cnt, right);
}


void SparseMatrix::sort_col(int left, int right){
	if(left >= right) return;
	double pivot = cols[right];
	int cnt = left;
	for(int i= left; i <= right; i++){
		if(cols[i] <= pivot){
			swap(cols[cnt], cols[i]);
			swap(vals[cnt], vals[i]);
			cnt++;
		}
	}
	sort_col(left,cnt-2);
	sort_col(cnt, right);
}

void SparseMatrix::sort(){
	int size = vals.size() - 1;
	sort_row(0, size);
	sort_col(0, size);
}
void SparseMatrix::setValue(int row, int col, double val) {
	vals.push_back(val);
    rows.push_back(row);
    cols.push_back(col);
	print();
	sort();
	print();
}

void SparseMatrix::print(){
	for(int i=0;i<vals.size(); i++){
		cout << "(" << rows[i] << " " << cols[i] << " " << vals[i] << ")";
	}
	cout << endl;
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
	sort();
}

bool SparseMatrix::readFromFile(string filename) {
	return false;
}

SparseMatrix SparseMatrix::operator+(SparseMatrix &M) {
	SparseMatrix tmp;
	for (int pos = 0; pos < vals.size(); pos++) {
        double new_val =vals[pos] + M.vals[pos];
        if(new_val == 0) continue;
        tmp.rows.push_back(rows[pos]);
        tmp.cols.push_back(cols[pos]);
        tmp.vals.push_back(new_val);
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

double SparseMatrix::rowSum(int row) {// calculate the sum of elements in a "row"-th row
	return 0;
} 
double SparseMatrix::colSum(int col) {// calculate the sum of elements in a "col"-th column
	return 0;
} 
double SparseMatrix::sum(){ // calculate the sum of all elements
    return 0;
}
bool SparseMatrix::isAllAbsLessThan(double val){
    return false;
}