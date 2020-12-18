#pragma once
#include "Image.h"
#include <iostream>
#include <string>

using namespace imaging;

//Pure virtual class
class Filter {
public:
	// The overrided operator
	virtual Image operator<< (const Image & image) = 0;
};