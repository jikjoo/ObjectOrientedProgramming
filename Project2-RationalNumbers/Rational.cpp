#include "Rational.h"

Rational::Rational(/* args */ int numerator, int denominator) {
  mnumer = numerator;
  mdenom = denominator;
  // abbreviation();
  digit = 8;
  plusminus();
}
Rational::Rational(float f) {
  digit = 8;
  float tempf = f;
  for (int i = 0; i < digit; i++) {
    if (tempf == (int)tempf || i == digit-1) {
      int decimal = pow(10, i);
      int int_tempf = (int) tempf;
      Rational T(int_tempf, decimal);
      T.abbreviation();
      mnumer = T[0];
      mdenom = T[1];
      break;
    } else {
      tempf *= 10;
    }
  }
}
Rational::~Rational() {}
void Rational::abbreviation() {  //약분
  if (mnumer == 0) {
    mdenom = 1;
    return;
  } else if (mnumer == mdenom) {
    mdenom = 1;
    mnumer = 1;
    return;
  } else if(abs(mnumer) > 1 && abs(mdenom) > 1) {
    int small = (abs(mnumer) < abs(mdenom)) ? abs(mnumer) : abs(mdenom);
    for (int i = 2; i <= small; i++) {
      if (mnumer % i == 0 && mdenom % i == 0) {
        mnumer = mnumer / i;
        mdenom = mdenom / i;
        abbreviation();
        return;
      }
    }
  }
  return;
}
void Rational::plusminus() {
  if (mnumer > 0 && mdenom < 0) {
    mnumer = mnumer * -1;
    mdenom = mdenom * -1;
  } else if (mnumer < 0 && mdenom < 0) {
    mnumer = mnumer * -1;
    mdenom = mdenom * -1;
  }
}

Rational Rational::operator+(Rational& B) {
  int numer = mnumer * B[1] + mdenom * B[0];
  int denom = mdenom * B[1];
  Rational T(numer, denom);
  T.abbreviation();
  //cout << T[0] << "/" << T[1];
  return T;
}
Rational Rational::operator-(Rational& B) {
  int numer = mnumer * B[1] - mdenom * B[0];
  int denom = mdenom * B[1];
  Rational temp(numer, denom);
  temp.abbreviation();
  return temp;
}
Rational Rational::operator*(Rational& B) {
  int numer = mnumer * B[0];
  int denom = mdenom * B[1];
  Rational temp(numer, denom);
  temp.abbreviation();
  return temp;
}
Rational Rational::operator/(Rational& B) {
  int numer = mnumer * B[1];
  int denom = mdenom * B[0];
  Rational temp(numer, denom);
  temp.abbreviation();
  return temp;
}
bool Rational::operator>(const Rational& B) {
  return (floating() > B.floating()) ? true : false;
}
bool Rational::operator<(const Rational& B) {
  return (floating() < B.floating()) ? true : false;
}
bool Rational::operator==(Rational& B) {
  return (floating() == B.floating()) ? true : false;
}
Rational Rational::operator-() {
  Rational T(mnumer * -1, mdenom);
  return T;
}

int Rational::operator[](int i) const {
  if (i > 0)
    return mdenom;
  else
    return mnumer;
}
float Rational::floating() const {
  float f = (float) mnumer / (float) mdenom;
  return f;
}

Rational Rational::operator+(float c) {
  Rational T(c);
  T = operator+(T);
  T.abbreviation();
  return T;
}
Rational Rational::operator-(float c) {
  Rational T(c);
  T = operator-(T);
  T.abbreviation();
  return T;
}
Rational Rational::operator*(float c) {
  Rational T(c);
  T = operator*(T);
  T.abbreviation();
  return T;
}
Rational Rational::operator/(float c) {
  Rational T(c);
  T = operator/(T);
  T.abbreviation();
  return T;
}
bool Rational::operator==(float c) { return (floating() == c) ? true : false; }

ostream& operator << (ostream& out, const Rational& C) {
  if (C[1] == 1) {
    out << "" << C[0];
  } else
    out << "" << C[0] << "/" << C[1]; 
  return out;
}
/* ostream& operator << (ostream& out, Rational& C) {
  if (C[1] == 1) {
    out << "" << C[0];
  } else
    out << "" << C[0] << "/" << C[1]; 
  return out;
} */