#include <iostream>
#include "Rational.h"

int main(int argc, char* argv[]) 
{
	//Rational A(1,2);
	//Rational B(2,3);
	Rational A(21,9);
	Rational B(3,5);
	
	cout << A << " + " << B << " = "  << A+B << " or " << Rational(A+B).floating() << endl;
	cout << A << " - " << B << " = "  << A-B  << " or " << Rational(A-B).floating() << endl;
	cout << A << " * " << B << " = "  << A*B  << " or " << Rational(A*B).floating() << endl;	
	cout << A << " / " << B << " = " << A/B << " or " << Rational(A/B).floating() << endl;
	cout << A << " < " << B << " is " << ((A<B)?"true":"false") << endl;
	cout << A << " > " << -B << " is " << ((A>-B)?"true":"false") << endl;
	cout << A << " == " << B << " is " << ((A==B)?"true":"false") << endl;
	cout << A << "'s numerator is " << A[0] << endl;
	cout << A << "'s demoninator is " << A[1] << endl;
	cout << endl;
	
	Rational C(0.5), D(3);	
	cout << A << " + " << 1.2 << " = " << A+1.2 << " or " << Rational(A+1.2).floating() << endl;
	cout << B << " * " << 1.2 << " = " << B*1.2 << " or " << Rational(B*1.2).floating() << endl;
	cout << A << " == " << 0.5 << " is " << ((A==0.5)?"true":"false") << endl;
	cout << C << " == " << 0.5 << " is " << ((C==0.5)?"true":"false") << endl;
	cout << D << " / " << C << " = " << D/C << " or " << Rational(D/C).floating() << endl;
	
	return 0;
}



