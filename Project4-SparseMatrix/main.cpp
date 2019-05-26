#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "SparseMatrix.h"

using namespace std;

bool Agree(SparseMatrix& A,SparseMatrix& A0)
{
	SparseMatrix D = A-A0;
	return( D.isAllAbsLessThan(1E-5) );
}

void test1()
{
	cout << "Test 1: " << endl;
	
	SparseMatrix A(5,5), B(3,3), C;
	A.setValue(3,2,1); A.setValue(1,3,2); A.setValue(5,2,3);
	B.setValue(1,3,-2); B.setValue(3,2,0.3); B.setValue(1,1,5);
	
	cout << "\tAssignment: ";
	if( A.getValue(1,3)==2 && A.getValue(5,2)==3 && A.getValue(1,1)==0 && A.getNumOfNonZeros()==3 ) cout << "pass" << endl;
	else cout << "fail" << endl;
	
	A.resize(3,3);
	cout << "\tResizing: ";
	if( A.getNumRows()==3 && A.getNumCols()==3 && A.getNumOfNonZeros()==2 ) cout << "pass" << endl;
	else cout << "fail" << endl;
	
	C = A+B;
	cout << "\tAddition: ";
	if( C.getValue(3,2)==1.3 && C.getValue(1,1)==5 && C.getNumOfNonZeros()==2 ) cout << "pass" << endl;
	else cout << "fail" << endl;
}

void test2()
{
	cout << "Test 2: ";

	SparseMatrix A, B, C, X;
	A.readFromFile("data2_1.txt");
	B.readFromFile("data2_2.txt");
	C.readFromFile("data2_3.txt");
	A.print();
	B.print();
	X = A*B;
	X.print();
	if( X.getNumRows()==9 && X.getNumCols()==9 && Agree(X,C) ) cout << "pass" << endl;
	else cout << "fail" << endl;
}

void test3()
{
	cout << "Test 3" << endl;

	int N = 100000;
	SparseMatrix A, B, C, D, X;
	A.readFromFile("data3_1.txt"); A.resize(N,N);
	B.readFromFile("data3_2.txt"); B.resize(N,N);
	C.readFromFile("data3_3.txt"); C.resize(N,N);
	D.readFromFile("data3_4.txt"); D.resize(N,N);

	X = A+B;
	cout << "\tAddition: ";
	if( X.getNumRows()==N && X.getNumCols()==N && Agree(X,C) ) cout << "pass" << endl;
	else cout << "fail" << endl;
	X = A*B;
	cout << "\tMultiplication: ";
	if( X.getNumRows()==N && X.getNumCols()==N && Agree(X,D) ) cout << "pass" << endl;
	else cout << "fail" << endl;
}


void test4()
{
	clock_t t1, t2;
	int N = 1000000;
	SparseMatrix A, B, C, D, X;
	double rtime, elapse;
	
	cout << "Test 4 ";

	// refrence time
	double s = 0.0;
	t1 = clock();
	for( int i=0 ; i<100000000 ; i++ ) s += 1.0/(rand()+1);
	t2 = clock();
	rtime = (double)(t2-t1)/CLOCKS_PER_SEC;
	cout << "(reference time = " << rtime << ")" << endl;
	
	// read input files
	A.readFromFile("data4_1.txt"); A.resize(N,N);
	B.readFromFile("data4_2.txt"); B.resize(N,N);
	C.readFromFile("data4_3.txt"); C.resize(N,N);
	D.readFromFile("data4_4.txt"); D.resize(N,N);

	// sum
	t1 = clock(); s = A.sum() + B.sum(); t2 = clock();
	elapse = (double)(t2-t1)/CLOCKS_PER_SEC;
	cout << "\tSummation: " << elapse << " secs (x " << elapse/rtime << "), ";
	if( abs(s-927.7998)<1E-3 ) cout << "pass" << endl;
	else cout << "fail" << endl;
	
	// addition
	t1 = clock(); X = A+B; t2 = clock();
	elapse = (double)(t2-t1)/CLOCKS_PER_SEC;
	cout << "\tAddition: " << elapse << " secs (x " << elapse/rtime << "), ";
	if( C.getNumRows()==N && C.getNumCols()==N && Agree(X,C) ) cout << "pass" << endl;
	else cout << "fail" << endl;

	// subtraction
	t1 = clock(); X = X-A; X = X-B; t2 = clock();
	elapse = (double)(t2-t1)/CLOCKS_PER_SEC;
	cout << "\tSubtraction: " << elapse << " secs (x " << elapse/rtime << "), ";
	if( X.getNumRows()==N && X.getNumCols()==N && X.getNumOfNonZeros()==0 ) cout << "pass" << endl;
	else cout << "fail" << endl;
	
	// multiplication
	t1 = clock(); X = A*B; t2 = clock();
	elapse = (double)(t2-t1)/CLOCKS_PER_SEC;
	cout << "\tMultiplication: " << elapse << " secs (x " << elapse/rtime << "), ";
	if( X.getNumRows()==N && X.getNumCols()==N && Agree(X,D) ) cout << "pass" << endl;
	else cout << "fail" << endl;
	
}

int main(int argc, char* argv[]) 
{
	test1();
	test2();
	//test3();
	//test4();
			
	return 0;
}
