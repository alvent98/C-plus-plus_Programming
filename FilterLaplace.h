#pragma once
#pragma once
#include "FilterBlur.h"

class FilterLaplace : public FilterBlur {
public:
	// Constractor with initalization list
	FilterLaplace() : FilterBlur(3) {}

	// The overrided operator
	Image operator << (const Image & image);
};
