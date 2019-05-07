#ifndef _BINGO_H_
#define _BINGO_H_

#include <string>

using namespace std;

class Bingo
{
public:
	Bingo();
	~Bingo();
	
	void genMat(int m);
	bool isBingo();
	void markMine(int call);
	void show();
	const string& name() { return mName; }

	// the function you need to implement
	// returns a number you want to call
	virtual int myCall(int *itscalls,int *mycalls,int ncalls) = 0;

protected:
	int mSize;
	int* mData;
	bool* mMark;
	string mName;
	
	void generate_matrix(int *mat,int size,int jump,int shift);
	int mat2vec(int i,int j) { return(i*mSize+j); }
	int vec2mat1(int idx) { return(idx/mSize); }
	int vec2mat2(int idx) { return(idx%mSize); }
};

#endif

