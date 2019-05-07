#ifndef Rational_H
#define Rational_H

#include <iostream>
#include <cmath>
using namespace std;

class Rational {
 private:
  /* data */
  int mnumer, mdenom;
  int digit;

 public:
  Rational(/* args */ int numerator, int denominator);
  Rational(float f);
  ~Rational();
  void abbreviation();
  void plusminus();
  Rational operator+(Rational& B);
  Rational operator-(Rational& B);
  Rational operator*(Rational& B);
  Rational operator/(Rational& B);
  bool operator>(const Rational& B);
  bool operator<(const Rational& B);
  bool operator==(Rational& B);
  Rational operator-();
  int operator[](int i) const;
  float floating() const;

  Rational operator+(float c);
  Rational operator-(float c);
  Rational operator*(float c);
  Rational operator/(float c);
  bool operator==(float c);
};
ostream& operator<<(ostream& out, const Rational& C);
//ostream& operator<<(ostream& out, Rational& C);

#endif