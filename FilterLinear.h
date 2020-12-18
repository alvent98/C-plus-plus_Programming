#pragma once
#include "Filter.h"
#include "Vec3.h"

class FilterLinear : public Filter {
	typedef math::Vec3<float> coefficient;
private:
	 coefficient a,c;
public:
	// Setters of the coefficients
	void setA(coefficient newA) { a = newA; }
	void setC(coefficient newC) { c = newC; }

	// Getters of the coefficients
	coefficient getA() { return a; }
	coefficient getC() { return c; }

	// Constractor with initalization list
	FilterLinear(coefficient newA, coefficient newC) : Filter(), a(newA), c(newC) {}
	// Copy Constractor
	FilterLinear(const FilterLinear & aFilter);
	
	// The overrided operator
	Image operator << (const Image & image);
};
