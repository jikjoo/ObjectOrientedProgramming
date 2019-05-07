
#include "Complex.h"

 Complex::Complex(/* args */ int a, int b){
     r=a; i=b;
 }
Complex::Complex(/* args */ float a, float b){
    r=a; i=b;
}
Complex::~Complex(){}

Complex Complex::operator+(Complex& B){
    Complex tmp(r + B.r, i + B.i);
    return tmp;
}

Complex Complex::operator-(Complex& B){
    Complex tmp(r-B.r, i-B.i);
    return tmp;
}

Complex Complex::operator*(Complex&B){
    Complex tmp(r*B.r - i*B.i, r*B.i+i*B.r );
    return tmp;
}

Complex Complex::operator/(Complex &B){
    float tr = r * B.r + i * B.i;
    float ti = i * B.i - r * B.r;
    float t = B.r* B.r + B.i * B.i;
    Complex tmp(tr / t, ti / t );
    return tmp;
}

Complex Complex::operator~(){
    Complex tmp(r,-i);
    return tmp;
}

float Complex::operator[](int part) const{
    if( part == 0) return r;
    else return i;
}

float Complex::abs(){    
    float t = sqrtf(r* r + i * i);
    return t;
}

bool Complex::operator==(Complex &B){
    if(r == B.r && i == B.i) return true;
    else return false;
}

Complex Complex::operator+(float a){
    Complex tmp( r+ a, i);
    return tmp;
}

ostream& operator << (ostream& out,  const Complex& C){
    if(C[1] > 0 ){
        out << C[0] << "+" << C[1]<< "i" ;
    }
    else if(C[1] == 0){
        out << C[0] ;
    }
    else{
        out << C[0] << "" << C[1]<< "i";
    }
    return out;
}
