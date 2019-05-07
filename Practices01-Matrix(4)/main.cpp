#include <iostream>
#include "matrix.h"

using namespace std;

int main(int argc, char** argv) 
{
	Matrix A, B;
	
	matrix_init(A,2,3);
	matrix_fill_randint(A);
	cout << "A" << endl; matrix_show(A); cout << endl;
	
	matrix_init(B,2,3);
	matrix_fill_randint(B);
	cout << "B" << endl; matrix_show(B); cout << endl;

	matrix_add(A,B);
	cout << "A <- A+B" << endl; matrix_show(A); cout << endl;

	matrix_transpose(A);
	cout << "A <- t(A)" << endl; matrix_show(A); cout << endl;

	Matrix C;
	matrix_init(C,2,4);
	matrix_fill_randint(C);
	cout << "C" << endl; matrix_show(C); cout << endl;

	matrix_multiply(A,C);
	cout << "A <- A*C" << endl; matrix_show(A); cout << endl;

	if( !matrix_add(A,B) ) cout << "A+B fails" << endl;
	if( !matrix_multiply(A,B) ) cout << "A*B fails" << endl;

	matrix_clear(A);
	matrix_clear(B);
	matrix_clear(C);
	
	return 0;
}





