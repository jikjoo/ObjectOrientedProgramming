#include "Shape.h"
#define PIE 3.141592

void Shape::setvalues(double a, double b){
    ma = a, mb= b;
}
void Shape::setvalues(double a){
    ma = a; mb = 0;
}

string Shape::getName(){
    return mname;
}
/* 
void Rectangle::setvalues(int a, int b){
    Shape::setvalues(a,b);
} */

double Rectangle::area(){
    double result;
    result = ma * mb;
    return result;
}

double Square::area(){
    double result;
    result = ma * ma;
    return result;
}

double IsoTriangle::area(){
    double result;
    result = (ma * mb) / 2;
    return result;
}

double Ellipse::area(){
    double result;
    result = (ma * mb) * PIE ;
    return result;
}

double Circle::area(){
    double result;
    result = (ma * ma) * PIE;
    return result;
}