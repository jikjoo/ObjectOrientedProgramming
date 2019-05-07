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
#ifndef _Bingo_2014170935_1_H_
#define _Bingo_2014170935_1_H_
#include <iomanip>

#include "Bingo.h"
#include "setting.h"

// change "2014170935" to your real student id
class Bingo_2014170935_1 : public Bingo { // This is simple strategy only think of me not other
public:
	// change "2014170935" to your real student id
	Bingo_2014170935_1() {
		mName = "Jikjoo_1"; // change "MyName" to your real name in English
		mWeight = NULL;
		itsjump = NULL;
		next_idx = 0;
		weight = 2;
	}
	// change "2014170935" to your real student id
	~Bingo_2014170935_1() { /* add whatever */
		if (mWeight) delete[] mWeight;
		mWeight = NULL;
		if (itsjump) delete[] itsjump;
		itsjump = NULL;
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
	int *itsjump;
	void itsjumpInitialize();
	void guessJump(int a, int b);
};

/********************************************************
  itcalls: a vector of int variables with size of "ncalls"
           showing the opponent's calls for the previous turns
  mycalls: a vector of int variables with size of "ncalls"
           showing my calls for the previous turns
  ncalls: number of previous turns
**********************************************************/
int Bingo_2014170935_1::myCall(int *itscalls, int *mycalls, int ncalls) {
	// implement your strategy
	int mid = mSize / 2;
	if (ncalls == 0) {
		//initial return
		weightInitialize();
		itsjumpInitialize();
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
		//predict
		if (ncalls > 1) {
			/* int itsjump = abs(itscalls[ncalls - 1] - itscalls[ncalls - 2]);
			int its_next_idx[4];
			its_next_idx[0] = itscalls[ncalls - 1] + itsjump;
			its_next_idx[1] = itscalls[ncalls - 1] - itsjump;
			its_next_idx[2] = itscalls[ncalls - 2] + itsjump;
			its_next_idx[3] = itscalls[ncalls - 3] - itsjump;
			for (int i = 0; i < 4; i++) {
				if (its_next_idx[i] < 0)
					its_next_idx[i] += mSize * mSize;
				else if (its_next_idx[i] > mSize * mSize) {
					its_next_idx[i] -= mSize * mSize;
				}
				for (idx = 0; idx < mSize * mSize; idx++)
					if (mData[idx] == its_next_idx[i]) {
						mWeight[idx] -= weight;
						break;
					}
			} */
			guessJump(itscalls[ncalls - 1], itscalls[ncalls - 2]);
		}
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

void Bingo_2014170935_1::weightInitialize() {
	if (!mWeight) mWeight = new int[mSize * mSize];
	for (int i = 0; i < mSize * mSize; i++) {
		mWeight[i] = 0;
	}
}

void Bingo_2014170935_1::itsjumpInitialize() {
	int jumpsize = 2 * mSize + 1;
	if (!itsjump) itsjump = new int[jumpsize];
	for (int i = 0; i < jumpsize; i++) {
		itsjump[i] = 0;
	}
}

void Bingo_2014170935_1::weightAdd(int data) {
	int idx;
	for (idx = 0; idx < mSize * mSize; idx++)
		if (mData[idx] == data) break;
	int row = vec2mat1(idx);
	int col = vec2mat2(idx);
	for (int i = 0; i < mSize; i++) {
		mWeight[mat2vec(row, i)] += weight;
		mWeight[mat2vec(i, col)] += weight;
		if (row == col) mWeight[mat2vec(i, i)] += weight;
		if (row == mSize - col - 1) mWeight[mat2vec(i, mSize - i - 1)] += weight;
	}
}

void Bingo_2014170935_1::weightShow() {
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

void Bingo_2014170935_1::guessJump(int a, int b) {
	for (int jump = 1; jump <= 2 * mSize; jump++) {
		// for row
		int val_a = a;
		int val_b = b;
		bool found = false;
		for (int i = 0; i < mSize; i++) {
			val_a += jump;
			val_b += jump;
			if (val_a > mSize * mSize) val_a = val_a % jump + 1;
			if (val_b > mSize * mSize) val_b = val_b % jump + 1;
			if (val_a == b || val_b == a) {
				found = true;
				break;
			}
		}
		// for column
		val_a = a;
		val_b = b;
		for (int i = 0; i < mSize; i++) {
			for (int j = 0; j < mSize; j++) {
				val_a += jump;
				val_b += jump;
				if (val_a > mSize * mSize) val_a = val_a % jump + 1;
				if (val_b > mSize * mSize) val_b = val_b % jump + 1;
			}
			if (val_a == b || val_b == a || found) {
				found = true;
				break;
			}
		}
		// for diagonal 1
		val_a = a;
		val_b = b;
		for (int i = 0; i < mSize; i++) {
			for (int j = 0; j < mSize + 1; j++) {
				val_a += jump;
				val_b += jump;
				if (val_a > mSize * mSize) val_a = val_a % jump + 1;
				if (val_b > mSize * mSize) val_b = val_b % jump + 1;
			}
			if (val_a == b || val_b == a || found) {
				found = true;
				break;
			}
		}
		// for diagonal 2
		val_a = a;
		val_b = b;
		for (int i = 0; i < mSize; i++) {
			for (int j = 0; j < mSize - 1; j++) {
				val_a += jump;
				val_b += jump;
				if (val_a > mSize * mSize) val_a = val_a % jump + 1;
				if (val_b > mSize * mSize) val_b = val_b % jump + 1;
			}
			if (val_a == b || val_b == a || found) {
				found = true;
				break;
			}
		}

		if (found) {
			itsjump[jump] += 1;
		}
	}
}

/* void Bingo_2014170935_1::weightAdd(int data) {
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
	if (rowmark == mSize - 1) mWeight[rowidx] += weight;
	if (colmark == mSize - 1) mWeight[colidx] += weight;
	if (dimark == mSize - 1) mWeight[dindx] += weight;
	if (rdimark == mSize - 1) mWeight[rdindx] += weight;
} */