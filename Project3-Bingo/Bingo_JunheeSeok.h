#ifndef _BINGO_JUNHEESEOK_H_
#define _BINGO_JUNHEESEOK_H_

#include "Bingo.h"

using namespace std;

class Bingo_JunheeSeok : public Bingo
{
public:
	Bingo_JunheeSeok() {
		mName = "Junhee Seok";
	}
	~Bingo_JunheeSeok() { }
	
	int myCall(int *itscalls,int *mycalls,int ncalls);
	
private:
};

int Bingo_JunheeSeok::myCall(int *itscalls,int *mycalls,int ncalls)
{
	for( int i=0 ; i<mSize*mSize ; i++ ) {
		if( !mMark[i] ) return mData[i];
	}
	return mData[mSize*mSize-1];
}

#endif
