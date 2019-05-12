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
#include <fstream>

#include "Bingo.h"
#include "setting.h"

// change "2014170935" to your real student id
class Bingo_2014170935_1 : public Bingo { // This is simple strategy only think of me not other
public:
	// change "2014170935" to your real student id
	Bingo_2014170935_1() {
		mName = "Jikjoo_1"; // change "MyName" to your real name in English5
		mWeight = NULL;
		itsjump = NULL;
		next_idx = 0;
		weight = 2;
		diffs.open("diffs.txt");
	}
	// change "2014170935" to your real student id
	~Bingo_2014170935_1() { /* add whatever */
		if (mWeight) delete[] mWeight;
		mWeight = NULL;
		if (itsjump) delete[] itsjump;
		itsjump = NULL;
		next_idx = 0;
		diffs.close();
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
	ofstream diffs;
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
		diffs << endl << "myjump = " <<  myjump << endl;
	} 
	else if(ncalls == BINGO_SIZE * 4 / 3 ){
		for(int i=1; i<ncalls; i++){
			diffs << itscalls[i] - itscalls[i-1] << " ";
		}
		diffs << endl;
		for(int i=1; i<ncalls; i++){
			diffs << mycalls[i] - mycalls[i-1] << " ";
		}
	}
	else {
		int idx;
		int itslastcall = itscalls[ncalls - 1];
		weightAdd(itslastcall);
		weightAdd(mycalls[ncalls - 1]);
		//predict
		// 가정 1. 첫 표시는 가운데거나 모서리
		// 가정 2. 두번째 표시는 첫 표시와 빙고되는 선으로 연결됨
		// 가정 3. 합차에 패턴이 존재한다.
			
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

void Bingo_2014170935_1::itsjumpInitialize() {
	int jumpsize = 2 * mSize + 1;
	if (!itsjump) itsjump = new bool[jumpsize];
	for (int i = 0; i < jumpsize; i++) {
		itsjump[i] = false;
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

void Bingo_2014170935_1::guessJump(int a, int b) {

	for (int j = 1; j <= 2 * mSize; j++) {
		// 첫 표시가 가운데
		int val = a;
		// row
		for (int i = 0; i < mSize / 2; i++) {
			val = jumpRight(val, j);
		}
	}
}