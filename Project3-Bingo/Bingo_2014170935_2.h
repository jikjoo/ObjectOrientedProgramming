/********************************************************
 This is the code you need to modify.
 
 IMPORTANT NOTE
 1. Change "2014170935" in the filename, class name, 
   preprocessing statements to your real student id.
 2. Change "MyName" in the constructor to your real name.
 
 These two changes are very important to grade your submission.
 If you miss the changes, you will have a penalty.
 
**********************************************************/

// change "2014170935" to your real student id
#ifndef _Bingo_2014170935_2_H_
#define _Bingo_2014170935_2_H_
#include <iomanip>

#include "Bingo.h"
#include "setting.h"

// change "2014170935" to your real student id
class Bingo_2014170935_2 : public Bingo { // This is simple strategy only think of me not other
public:
	// change "2014170935" to your real student id
	Bingo_2014170935_2() {
		mName = "Jikjoo_2"; // change "MyName" to your real name in English
		mWeight = NULL;
		next_idx = 0;
		weight = 1;
	}
	// change "2014170935" to your real student id
	~Bingo_2014170935_2() { /* add whatever */
		if (mWeight) delete[] mWeight;
		mWeight = NULL;
		next_idx = 0;
	}

	int myCall(int *itscalls, int *mycalls, int ncalls);

private:
	// declare whatever you want
	int *mWeight; // weight matrix of next indexes
	void weightAdd(int idx);
	void weightInitialize();
	void weightShow();
	int weight;
	int next_idx; // next index
	int myshift;
	int myjump;
};

/********************************************************
  itcalls: a vector of int variables with size of "ncalls"
           showing the opponent's calls for the previous turns
  mycalls: a vector of int variables with size of "ncalls"
           showing my calls for the previous turns
  ncalls: number of previous turns
**********************************************************/
int Bingo_2014170935_2::myCall(int *itscalls, int *mycalls, int ncalls) {
	// implement your strategy
	int mid = mSize / 2;
	if (ncalls == 0) {
		//initial return
		weightInitialize();
		next_idx = mat2vec(mid, mid);
		for (int i = 0; i < mSize * mSize; i++) {
			if (mData[i] == 1) myshift = i;
		}
		myjump = abs(mData[myshift + 1] - mData[myshift]);
		//show();
	} else {
		int idx;
		weightAdd(itscalls[ncalls - 1]);
		weightAdd(mycalls[ncalls - 1]);
		for (int i = 0; i < mSize; i++) {
			for (int j = 0; j < mSize; j++) {
				idx = mat2vec(i, j);
				if (mMark[idx]) continue;
				if (mMark[next_idx]) next_idx = idx;
				if (mWeight[next_idx] < mWeight[idx]) {
					next_idx = idx;
				}
			}
		}
	}
#ifdef DEBUG_WEIGHT
	show();
	weightShow();
#endif
	return mData[next_idx];
}

void Bingo_2014170935_2::weightInitialize() {
	if (!mWeight) mWeight = new int[mSize * mSize];
	for (int i = 0; i < mSize * mSize; i++) {
		mWeight[i] = 0;
	}
}

void Bingo_2014170935_2::weightAdd(int data) {
	int idx;
	for (idx = 0; idx < mSize * mSize; idx++)
		if (mData[idx] == data) break;
	int row = vec2mat1(idx);
	int col = vec2mat2(idx);
	int rowmark = 0;
	int colmark = 0;
	int dimark = 0;
	int rdimark = 0;
	int rowidx, colidx, dindx, rdindx;
	for (int i = 0; i < mSize; i++) {
		//for row
		mWeight[mat2vec(row, i)] += weight;
		if (mMark[mat2vec(row, i)])
			rowmark++;
		else
			rowidx = mat2vec(row, i);
		//for column
		mWeight[mat2vec(i, col)] += weight;
		if (mMark[mat2vec(i, col)])
			colmark++;
		else
			colidx = mat2vec(i, col);
		//for diagonal
		if (row == col) {
			mWeight[mat2vec(i, i)] += weight;
			if (mMark[mat2vec(i, i)])
				dimark++;
			else
				dindx = mat2vec(i, i);
		}

		if (row == mSize - col - 1) {
			mWeight[mat2vec(i, mSize - i - 1)] += weight;
			if (mMark[mat2vec(i, mSize - i - 1)])
				rdimark++;
			else
				rdindx = mat2vec(i, mSize - i - 1);
		}
	}
	if (rowmark == mSize - 1) mWeight[rowidx] += 2 * weight;
	if (colmark == mSize - 1) mWeight[colidx] += 2 * weight;
	if (dimark == mSize - 1) mWeight[dindx] += 2 * weight;
	if (rdimark == mSize - 1) mWeight[rdindx] += 2 * weight;
}

void Bingo_2014170935_2::weightShow() {
	cout << mName << " Weight" << endl;
	for (int i = 0; i < mSize; i++) {
		for (int j = 0; j < mSize; j++) {
			int idx = mat2vec(i, j);
			char mark = mMark[idx] ? '*' : ' ';
			cout << setw(4) << mWeight[idx] << mark << " ";
		}
		cout << endl;
	}
	cout << endl;
}
#endif
