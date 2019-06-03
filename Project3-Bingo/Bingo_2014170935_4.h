/********************************************************
 This is the code you need to modify.
 
 IMPORTANT NOTE
 1. Change "2014170935_4" in the filename, class name, 
   preprocessing statements to your real student id.
 2. Change "MyName" in the constructor to your real name.
 
 These two changes are very important to grade your submission.
 If you miss the changes, you will have a penalty.
 
**********************************************************/

// change "2014170935_4" to your real student id
#ifndef _Bingo_2014170935_4_H_
#define _Bingo_2014170935_4_H_
#include <iomanip>

#include "Bingo.h"
#include "setting.h"

// change "2014170935_4" to your real student id
class Bingo_2014170935_4 : public Bingo { // This is simple strategy only think of me not other
public:
	// change "2014170935_4" to your real student id
	Bingo_2014170935_4() {
		mName = "Jikjoo_4"; // change "MyName" to your real name in English5
		mWeight = NULL;
		itsdiff = NULL;
		next_idx = 0;
		weight = 2;
	}
	// change "2014170935_4" to your real student id
	~Bingo_2014170935_4() { /* add whatever */
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
	int most_diff;
	void itsdiffInitialize();
	void weightSub(int data);
	int findIdxbyData(int data);
	int jumpRight(int val, int jump);
	int jumpLeft(int val, int jump);
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
int Bingo_2014170935_4::myCall(int *itscalls, int *mycalls, int ncalls) {
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
	} else {
		int idx;
		int itslastcall = itscalls[ncalls - 1];
		weightAdd(itslastcall);
		weightAdd(mycalls[ncalls - 1]);
		//predict
		// 가정 1. lastcall이랑 그 전 call의 차에는 규칙성이 있다.
		//guessDiff
		int jumpsize = mSize * 2;
		for (int i = 0; i < ncalls - 1; i++) {
			int diff = abs(itslastcall - itscalls[i]);
			if (diff <= jumpsize)
				itsdiff[diff] += 2;
			int diff_with_my = abs(itslastcall - mycalls[i]);
			if (diff_with_my <= jumpsize)
				itsdiff[diff_with_my] += 1;
		} // let's think the most frequent diff + itslastcall will be its next call
		int wall = mSize /2; //mSize; // 규칙성이 있는 diff를 찾기 위한 벽
		for (int i = 1; i <= jumpsize; i++) {
			if (itsdiff[most_diff] + wall < itsdiff[i])
				most_diff = i;
		}
		if (itslastcall + most_diff <= mSize * mSize)
			weightSub(itslastcall + most_diff);
		if (itslastcall - most_diff > 0)
			weightSub(itslastcall - most_diff);
		for (int i = 0; i < mSize; i++) {
			for (int j = 0; j < mSize; j++) {
				idx = mat2vec(i, j);
				if (mMark[idx]) continue;
				if (mMark[next_idx]) next_idx = idx;
				//make confuse
				if (mWeight[next_idx] < mWeight[idx]) {
					next_idx = idx;
				} else if (mWeight[next_idx] == mWeight[idx]) {
					// weight가 같다면 mycalls에 있는것들과 가로로 붙어있는것은 피한다.
					bool next_side = false;
					bool cur_side = false;

					int hist_idx = findIdxbyData(mycalls[ncalls - 1]);
					if (vec2mat1(hist_idx) == vec2mat1(next_idx) &&
						abs(hist_idx - next_idx) == 1) {
						next_side = true;
					}
					if (vec2mat1(hist_idx) == vec2mat1(idx) &&
						abs(hist_idx - idx) == 1) {
						cur_side = true;
					}

					if (next_side && !cur_side) {
						next_idx = idx;
					}
				}
			}
		}
	}
#ifdef DEBUG_WEIGHT
	weightShow();
#endif
	return mData[next_idx];
}

void Bingo_2014170935_4::weightInitialize() {
	if (!mWeight) mWeight = new int[mSize * mSize];
	for (int i = 0; i < mSize * mSize; i++) {
		mWeight[i] = 0;
	}
}

void Bingo_2014170935_4::itsdiffInitialize() {
	int jumpsize = 2 * mSize + 1;
	most_diff = 0;
	if (!itsdiff) itsdiff = new int[jumpsize];
	for (int i = 0; i < jumpsize; i++) {
		itsdiff[i] = 0;
	}
}

void Bingo_2014170935_4::weightAdd(int data) {
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

void Bingo_2014170935_4::weightShow() {
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

void Bingo_2014170935_4::weightSub(int data) {
	int idx = findIdxbyData(data);
	mWeight[idx] -= 1;
}

int Bingo_2014170935_4::findIdxbyData(int data) {
	for (int idx = 0; idx < mSize * mSize; idx++) {
		if (mData[idx] == data) {
			return idx;
		}
	}
}

int Bingo_2014170935_4::jumpRight(int val, int jump) {
	val = val + jump;
	if (val > mSize * mSize) val = val % jump + 1;
	return val;
}

int Bingo_2014170935_4::jumpLeft(int val, int jump) {
	val = val - jump;
	if (val <= 0) {
		val = val - 1;
		while (val <= mSize * mSize) {
			val = val + jump;
		}
		val = val - jump;
	}
}
int Bingo_2014170935_4::jumpUp(int val, int jump) {
	for (int i = 0; i < mSize; i++) {
		val = jumpLeft(val, jump);
	}
}
int Bingo_2014170935_4::jumpDown(int val, int jump) {
	for (int i = 0; i < mSize; i++) {
		val = jumpRight(val, jump);
	}
}
