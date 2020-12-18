#pragma once
#include "Filter.h"

class FilterBlur : public Filter {
private:
	int N;
public:
	// Setter & Getter of N
	void setN(int newN) { N = newN; }
	int getN() { return N; }

	// Constractor with initalization list
	FilterBlur(int newN) : Filter(), N(newN) {}
	// Copy Constractor
	FilterBlur(const FilterBlur & aFilter);

	// The overrided operator
	Image operator << (const Image & image);
};
