#include <iostream>
//#include "Shape.h"
#include "House.h"


int main(int argc, char const *argv[]) {
	/* Shape *pS[5];
  pS[0] = new Rectangle("Rectangle");
  pS[1] = new IsoTriangle("IsoTriangle");
  pS[2] = new Ellipse("Ellipse");
  pS[3] = new Square("Square");
  pS[4] = new Circle("Circle");
  

  for( int i=0; i < 5; i++){
      if(i<3) pS[i] -> setvalues(3,4);
      else pS[i] -> setvalues(3);
  }
  for(int i=0;i<5;i++){
      cout << "Area of " << pS[i]->getName();
      cout << " : " << pS[i]->area() << endl;
  } */

	House H;
	H.IsoTriangle::setValues(3, 5);
    H.Rectangle::setValues(4,8);
    cout << "Area = " << H.area() << endl;
    cout << "Perimeter = " << H.perimeter() << endl;
	return 0;
}
