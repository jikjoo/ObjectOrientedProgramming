#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include "setting.h"
#include "Bingo.h"

using namespace std;

Bingo::Bingo()
{
	mSize = 0;
	mData = NULL;
	mMark = NULL;
}

Bingo::~Bingo()
{
	if( mData ) delete[] mData;
	if( mMark )	delete[] mMark;
	mSize = 0;
	mData = NULL;
	mMark = NULL;
}

void Bingo::genMat(int m)
{
	if( m <= 3 ) m = 3;
	mSize = m;
	if( !mData ) mData = new int[mSize*mSize];
	if( !mMark ) mMark = new bool[mSize*mSize];
	for( int i=0 ; i<mSize*mSize ; i++ ) mMark[i] = false;

	// randomly generate bingo matrix
	int jump = rand()%(2*mSize)+1;
	int shift = rand()%(mSize*mSize);
#ifdef DEBUG_HIDDEN
	cout << mName << " jump : " << jump << " shift : " << shift << endl;
#endif
	generate_matrix(mData,mSize*mSize,jump,shift);
}

bool Bingo::isBingo()
{
	int bingo_cnt = 0;
	bool complete;
	
	// for row
	for( int i=0 ; i<mSize ; i++ ) {
		complete = true;
		for( int j=0 ; j<mSize ; j++ ) {
			if( mMark[mat2vec(i,j)] == false ) {
				complete = false;
				break;
			}
		}
		if( complete ) bingo_cnt++;
	}
	// for column
	for( int i=0 ; i<mSize ; i++ ) {
		complete = true;
		for( int j=0 ; j<mSize ; j++ ) {
			if( mMark[mat2vec(j,i)] == false ) {
				complete = false;
				break;
			}
		}
		if( complete ) bingo_cnt++;
	}
	// for diagonal
	complete = true;
	for( int i=0 ; i<mSize ; i++ ) {
		if( mMark[mat2vec(i,i)] == false ) {
			complete = false;
			break;
		}		
	}
	if( complete ) bingo_cnt++;
	complete = true;
	for( int i=0 ; i<mSize ; i++ ) {
		if( mMark[mat2vec(i,mSize-i-1)] == false ) {
			complete = false;
			break;
		}		
	}
	if( complete ) bingo_cnt++;
	
	if( bingo_cnt >= BINGO_CNT ) return true;
	return false;
}

void Bingo::markMine(int call)
{
	for( int i=0 ; i<mSize*mSize ; i++ ) {
		if( mData[i] == call ) {
			mMark[i] = true;
			return;
		}
	}
}

void Bingo::show()
{
	cout << mName << endl;
	for( int i=0 ; i<mSize ; i++ ) {
		for( int j=0 ; j<mSize ; j++ ) {
			int idx = mat2vec(i,j);
			char mark = mMark[idx]?'*':' ';
			cout << setw(4) << mData[idx] << mark << " "; 
		}
		cout << endl;
	}
}

void Bingo::generate_matrix(int *mat,int size,int jump,int shift)
{
	int val = 1;
	for( int i=shift ; i<size ; i++ ) {
		mat[i] = val;
		val += jump;
		if( val > size ) val = val%jump+1;
	}
	for( int i=0 ; i<shift ; i++ ) {
		mat[i] = val;
		val += jump;
		if( val > size ) val = val%jump+1;
	}
}
