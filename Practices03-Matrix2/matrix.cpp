#include <iostream>
#include <cstdlib>
#include "matrix.h"
#include <cmath>

using namespace std;

Matrix::Matrix(int nr,int nc)
{
	mNrow = nr;
	mNcol = nc;
	mData = new double[nr * nc];
}

Matrix::~Matrix()
{
	delete[] mData;
}

int Matrix::getNrow()
{
	return mNrow;
} 

int Matrix::getNcol()
{
	return mNcol;
} 

void Matrix::fillRandInt(int start,int end)
{
  	for( int i=0 ; i<mNrow*mNcol ; i++ ) {
		mData[i] = rand()%(end-start+1)+start ;
	}
}

bool Matrix::add(Matrix &M)
{
	if(mNrow==M.getNrow() && mNcol==M.getNcol()){
		for(int i=0; i<mNrow*mNcol; i++){
			mData[i] = mData[i]+M.getData(i);
		}
	return true;
	}
	else return false;
}

bool Matrix::multiply(Matrix &M)
{
	if(mNcol == M.getNrow()){	
		int size = mNrow * M.getNcol();
		double *data = new double[mNrow * mNcol] ;	
		for(int i=0; i<mNrow * mNcol; i++){
			data[i] = mData[i];
		}
		delete [] mData;
		
		mData = new double[size];
		
		for(int i = 0; i < mNrow; i++){
			for(int j=0; j<M.getNcol(); j++){
				int temp = 0;
				for(int k =0; k< mNcol; k++){
					int index1 = i * mNcol + k;
					int index2 = k * M.getNcol() + j;
					temp += data[index1]*M.getData(index2);
				}
				int index3 = i*mNrow+j;
				mData[index3] = temp;
			}
		}
		
		mNcol = M.getNcol();
		return true;
	}
	else return false;
}

bool Matrix::transpose()
{
	double * tempData = new double [mNcol * mNrow];
	for(int t=0; t < mNrow * mNcol ; t++){
		tempData[t] = mData[t];
	}
	int c=0;
	for(int i=0; i<mNrow;i+=1){
		for(int j=0; j<mNcol;j+=1){
			int index1 = j*mNrow + i;
			int index2 = i*mNcol+j;
			mData[index1] = tempData[index2];
		}
	}
	int temp = mNcol;
	mNcol = mNrow;
	mNrow = temp;
	delete [] tempData;
	return true;
}

void Matrix::show()
{
	for(int i=0; i<mNrow * mNcol ; i++){
		cout << mData[i] << "	";
		if(i%mNcol == mNcol - 1) cout << endl;
	}
}

double Matrix::det()
{
	if(mNrow != mNcol) return 0.0;
	else if(mNrow == 1) return sqrt(2);
		else if(mNrow == 2){
			double d = mData[0] * mData[3] - mData[1] * mData[2];
			return d;
		}
		else {
			double d=0.0;
			int n = mNrow - 1; // dimension of sub
			for(int i=0; i<mNrow; i++){ // first row of Matrix
				Matrix sub(n, n);
				int k=0;
				for(int j=0; j< mNrow * mNrow ; j++){
					if(j / mNrow == 0 ) continue;
					if(j%mNrow == i) continue;
					sub.fillData(k++,mData[j]);
				}
				d += mData[i] * sub.det() * pow(-1,i) ;

				//sub.show();
				//cout << endl;
			}
			return d;
		}
}


int Matrix::getData(int i){
	return mData[i];
}
void Matrix::fillData(int i, int val){
	mData[i] = val;
}
