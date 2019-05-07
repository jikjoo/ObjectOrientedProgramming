#include <iostream>
#include <cstdlib>
#include "matrix.h"

using namespace std;

int main(int argc, char *argvp[])
{
	// test codes in the previous C program
	
	Matrix A(2,3);	
	A.fillRandInt();
	cout << "A" << endl; A.show(); cout << endl;
	
	Matrix B(2,3);	
	B.fillRandInt();
	cout << "B" << endl; B.show(); cout << endl;	

	A.add(B);
	cout << "A <- A+B" << endl; A.show(); cout << endl; 
	
	A.transpose();
	cout << "A <- t(A)" << endl; A.show(); cout << endl;

	Matrix C(2,3);
	C.fillRandInt();
	cout << "C" << endl; C.show(); cout << endl;

	A.multiply(C);
	cout << "A <- A*C" << endl; A.show(); cout << endl;

	// new test codes
	cout << "size of A is " << A.getNrow() << " x " << A.getNcol() << endl;
	cout << "det(A) = " << A.det() << endl;
	cout << "det(C) = " << C.det() << endl;
	cout << endl;
	
	// you can stop here, if you have more time, try the below
	
	srand(1000);
	Matrix D(3,3);
	D.fillRandInt();
	cout << "D" << endl; D.show(); cout << endl;
	cout << "det(D) = " << D.det() << endl; // it should be -132
	cout << endl;
	
	srand(1001);
	Matrix E(5,5);
	E.fillRandInt();
	cout << "E" << endl; E.show(); cout << endl;
	cout << "det(E) = " << E.det() << endl; // it should be -841
	
	return 0;
}
