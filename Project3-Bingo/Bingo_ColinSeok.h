#ifndef _BINGO_COLINSEOK_H_
#define _BINGO_COLINSEOK_H_

#include "Bingo.h"

using namespace std;

class Bingo_ColinSeok : public Bingo
{
public:
	Bingo_ColinSeok() {
		mName = "Colin Seok";
	}
	~Bingo_ColinSeok() { }
	
	int myCall(int *itscalls,int *mycalls,int ncalls);
	
private:
};

int Bingo_ColinSeok::myCall(int *itscalls,int *mycalls,int ncalls)
{
	int tmp[mSize*mSize], tmpsize = 0;
	for( int i=0; i<mSize*mSize ; i++ ) {
		if( !mMark[i] ) tmp[tmpsize++] = mData[i];
	}
	if( tmpsize>0 ) return tmp[rand()%tmpsize];
	return mData[0];
}

#endif
