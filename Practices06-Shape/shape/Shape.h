#include <string>

using namespace std;

class Shape
{
protected:
    /* data */
    string mname;
    double ma, mb;
public:
    Shape(/* args */ string name) { mname = name; };
    ~Shape();
    string getName();
    virtual void setvalues(double a, double b);
    virtual void setvalues(double a);
    virtual double area() = 0;
};

class Rectangle: public Shape
{
private:
    /* data */
public:
    Rectangle(/* args */ string rname):Shape(rname){};
    ~Rectangle();
    //void setvalues(int a, int b);
    double area();
};

class Square: public Shape
{
private:
    /* data */
public:
    Square(/* args */string sname):Shape(sname){};
    ~Square();
    double area();
};

class IsoTriangle: public Shape
{
private:
    /* data */
public:
    IsoTriangle(/* args */ string iname):Shape(iname){};
    ~IsoTriangle();
    double area();
};

class Ellipse: public Shape
{
private:
    /* data */
public:
    Ellipse(/* args */ string ename):Shape(ename){};
    ~Ellipse();
    double area();
};

class Circle: public Shape
{
private:
    /* data */
public:
    Circle(/* args */ string cname):Shape(cname){};
    ~Circle();
    double area();
};
