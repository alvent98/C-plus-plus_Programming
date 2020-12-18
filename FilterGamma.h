#pragma once
#include "Filter.h"

class FilterGamma : public Filter {
private:
	float gamma;
public:
	// Setter & Getter of gamma
	void setGamma(float newGamma) { gamma = newGamma; }
	float getGamma() { return gamma; }

	// Constractor with initalization list
	FilterGamma(float newGamma) : Filter(),gamma(newGamma) {}
	// Copy Constractor
	FilterGamma(const FilterGamma & aFilter);

	// The overrided operator
	Image operator << (const Image & image);
};
