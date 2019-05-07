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
	void weightAdd(int data);
	void weightInitialize();
	void weightShow();
	int weight;
	int next_idx; // next index
	int myshift;
	int myjump;
	bool *itsjump;
	void itsjumpInitialize();
	void guessJump(int a, int b);
	void weightGuessAdd(int data);
	int findIdxbyData(int data);
	int jumpLeft(int val, int jump);
	int jumpRight(int val, int jump);
	int jumpUp(int val, int jump);
	int jumpDown(int val, int jump);
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
		if (ncalls > 2) {
			guessJump(itscalls[ncalls - 1], itscalls[ncalls - 2]);
			weightGuessAdd(itscalls[ncalls - 1]);
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
	if (!itsjump) itsjump = new bool[jumpsize];
	for (int i = 0; i < jumpsize; i++) {
		itsjump[i] = false;
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
			val_a = jumpRight(val_a, jump);
			val_b = jumpRight(val_b, jump);
			if (val_a == b || val_b == a) {
				found = true;
				break;
			}
		}
		// for column
		val_a = a;
		val_b = b;
		for (int i = 0; i < mSize; i++) {
			val_a = jumpDown(val_a, jump);
			val_b = jumpDown(val_b, jump);
			if (val_a == b || val_b == a || found) {
				found = true;
				break;
			}
		}
		// for diagonal 1
		val_a = a;
		val_b = b;
		for (int i = 0; i < mSize; i++) {
			val_a = jumpDown(val_a, jump);
			val_a = jumpRight(val_a, jump);
			val_b = jumpDown(val_b, jump);
			val_b = jumpRight(val_b, jump);
			if (val_a == b || val_b == a || found) {
				found = true;
				break;
			}
		}
		// for diagonal 2
		val_a = a;
		val_b = b;
		for (int i = 0; i < mSize; i++) {
			val_a = jumpLeft(val_a, jump);
			val_a = jumpDown(val_a, jump);
			val_b = jumpLeft(val_b, jump);
			val_b = jumpDown(val_b, jump);
			if (val_a == b || val_b == a || found) {
				found = true;
				break;
			}
		}

		if (found) {
			itsjump[jump] = true;
		}
	}
}

void Bingo_2014170935_1::weightGuessAdd(int data) {
	for (int j = 1; j <= 2 * mSize; j++) {
		if (!itsjump[j]) {
			//find neighbor of data, if not itsjump
			// right
			int idx;
			int val;
			val = jumpRight(data, j);
			idx = findIdxbyData(val);
			mWeight[idx] += weight / 2;
			// left
			val = jumpLeft(data, j);
			idx = findIdxbyData(val);
			mWeight[idx] += weight / 2;
			// up
			val = jumpUp(data, j);
			idx = findIdxbyData(val);
			mWeight[idx] += weight / 2;
			// down
			val = jumpDown(data, j);
			idx = findIdxbyData(val);
			mWeight[idx] += weight / 2;
		}
	}
}

int Bingo_2014170935_1::findIdxbyData(int data) {
	for (int idx = 0; idx < mSize * mSize; idx++) {
		if (mData[idx] == data) {
			return idx;
		}
	}
}

int Bingo_2014170935_1::jumpRight(int val, int jump) {
	val = val + jump;
	if (val > mSize * mSize) val = val % jump + 1;
	return val;
}

int Bingo_2014170935_1::jumpLeft(int val, int jump) {
	val = val - jump;
	if (val <= 0) {
		val = val - 1;
		while (val <= mSize * mSize) {
			val = val + jump;
		}
		val = val - jump;
	}
}
int Bingo_2014170935_1::jumpUp(int val, int jump) {
	for (int i = 0; i < mSize; i++) {
		val = jumpLeft(val, jump);
	}
}
int Bingo_2014170935_1::jumpDown(int val, int jump) {
	for (int i = 0; i < mSize; i++) {
		val = jumpRight(val, jump);
	}
}
