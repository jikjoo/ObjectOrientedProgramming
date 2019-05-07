#include "House.h"

double Shape::get(int hw) {
	if (hw == 0)
		return height;
	else
		return width;
}
double IsoTriangle::area() {
	double it_area;
	it_area = (height * width) / (double)2;
	return it_area;
}

double IsoTriangle::perimeter() {
	double it_perim;
	it_perim = width + (double)sqrtf(width * width + (double)4 * height * height);
	return it_perim;
}

double Rectangle::area() {
	double r_area;
	r_area = width * height;
	return r_area;
}

double Rectangle::perimeter() {
	double r_perim;
	r_perim = (double)2 * (width + height);
	return r_perim;
}
double House::area() {
	double h_area;
	h_area = IsoTriangle::area() + Rectangle::area();
	return h_area;
}

double House::perimeter() {
    double it_width = IsoTriangle::get(1);
    double r_width = Rectangle::get(1);
    double short_width = (it_width < r_width )? it_width : r_width;
	double h_perim = IsoTriangle::perimeter() + Rectangle::perimeter() - 2* short_width;
	return h_perim;
}