#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <iostream>
#include <cmath>
using namespace std;

class Complex
{
private:
    /* data */
    float r, i;
public:
    Complex(/* args */ int a, int b);
    Complex(/* args */ float a, float b);
    ~Complex();
    Complex operator + (Complex& B );
    Complex operator - (Complex& B);
    Complex operator * (Complex& B);
    Complex operator / (Complex& B);
    Complex operator ~ ();
    float operator [](int part) const;
    float abs();
    bool operator == (Complex& B);
    Complex operator + (float a);
};

ostream& operator<< (ostream& out, const Complex& C);
#endif
