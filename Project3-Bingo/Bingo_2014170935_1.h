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
		mName = "Jikjoo_1"; // change "MyName" to your real name in English5
		mWeight = NULL;
		itsdiff = NULL;
		next_idx = 0;
		weight = 2;
	}
	// change "2014170935" to your real student id
	~Bingo_2014170935_1() { /* add whatever */
		if (mWeight) delete[] mWeight;
		mWeight = NULL;
		if (itsdiff) delete[] itsdiff;
		itsdiff = NULL;
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
	int *itsdiff;
	void itsdiffInitialize();
	void guessDiff(int a, int b);
	void weightSub(int data);
	int findIdxbyData(int data);
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
		itsdiffInitialize();
		next_idx = mat2vec(mid, mid);
		for (int i = 0; i < mSize * mSize; i++) {
			if (mData[i] == 1) myshift = i;
		}
		myjump = abs(mData[myshift + 1] - mData[myshift]);
	}
	else {
		int idx;
		int itslastcall = itscalls[ncalls - 1];
		weightAdd(itslastcall);
		weightAdd(mycalls[ncalls - 1]);
		//predict
		// 가정 1. lastcall이랑 그 전 call의 차에는 규칙성이 있다.
		//guessDiff
		int jumpsize = mSize * 2;
		int diff = abs(itslastcall - itscalls[ncalls - 2]);
		if (diff <= jumpsize) {
				itsdiff[diff] += 1;
		}
		// let's think the most frequent diff + itslastcall will be its next call
		int most_diff = 0;
		int wall = ncalls / mSize * 2; // 규칙성이 있는 diff를 찾기 위한 벽
		for (int i = 1; i <= jumpsize; i++) {
			if (itsdiff[most_diff] + wall < itsdiff[i])
				most_diff = i;
		}
		if(itslastcall + most_diff <= mSize * mSize)
			weightSub(itslastcall + most_diff);
		if(itslastcall - most_diff > 0)
			weightSub(itslastcall - most_diff);	
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

void Bingo_2014170935_1::itsdiffInitialize() {
	int jumpsize = 2 * mSize + 1;
	if (!itsdiff) itsdiff = new int[jumpsize];
	for (int i = 0; i < jumpsize; i++) {
		itsdiff[i] = 0;
	}
}

void Bingo_2014170935_1::weightAdd(int data) {
	int idx = findIdxbyData(data);
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
			cout << setw(2) << mData[idx] << "(" << mWeight[idx] << ")" << mark << " ";
		}
		cout << endl;
	}
	cout << endl;
}
#endif

void Bingo_2014170935_1::weightSub(int data) {
	int idx = findIdxbyData(data);
	mWeight[idx] -= 1;
}

int Bingo_2014170935_1::findIdxbyData(int data) {
	for (int idx = 0; idx < mSize * mSize; idx++) {
		if (mData[idx] == data) {
			return idx;
		}
	}
}