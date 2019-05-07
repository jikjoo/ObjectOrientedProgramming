#include "Complex.h"

#ifndef __GLIBCXX_IOSTREAM
#include <iostream>
using namespace std;
#endif

int main(int argc, char* argv[]){
    Complex A(1,1);
    Complex B(1,2);
   	cout << A << " + " << B << " = " << A+B << endl;
   	cout << A << " - " << B << " = " << A-B << endl;
   	cout << A << " * " << B << " = " << A*B << endl;
   	cout << A << " / " << B << " = " << A/B << endl;
   	cout << "Conjugate of" << A << " = " << ~A << endl;
    
   	cout <<  "real part of " << B << " = " << B[0] << endl;
   	cout << "imaginary part of" << B << " = " << B[1] << endl;
   	cout << "absolute value of  " << B << " = " << B.abs() << endl;
       
   	cout << A << " and " << B << " are " << (A==B?"equal":"not equal") << endl;
       
   	cout << A << " + " << 1.2 << " = " << A+1.2 << endl;
    
    return 0;
}
