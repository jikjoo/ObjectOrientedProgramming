#include <cmath>
using namespace std;

class Shape{
    public:
        Shape(){};
        ~Shape(){};
        void setValues(double h, double w){height = h; width = w;}
        double get(int hw);
        virtual double area() = 0;
        virtual double perimeter() = 0;
    protected:
        double height, width;
};

class IsoTriangle: public Shape {
    public:
        IsoTriangle(){};
        ~IsoTriangle(){};
        double area();
        double perimeter();
};

class Rectangle : public Shape {
    public:
        Rectangle(){};
        ~Rectangle(){};
        double area();
        double perimeter();
};

class House : public IsoTriangle , public Rectangle {
    public:
        double area();
        double perimeter();
};