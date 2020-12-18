#pragma once
#include "FilterLaplace.h"

Image FilterLaplace::operator<< (const Image & image) {
	//Create the new image object that is going to be returned
	Image newImage = image;

	int N = getN();
	unsigned int width = newImage.getWidth();
	unsigned int height = newImage.getHeight();

	//Create a vector of floats, with the properties and data of the float array theFloats
	float theFloats[] = { 0,1,0,1,-4,1,0,1,0 };
	std::vector<float> dataTable(theFloats, theFloats + sizeof(theFloats) / sizeof(float));

	//Create an array object with T = float, that contains the dataTable vector (just a container)
	math::Array<float> filterTable(N,N, dataTable);

	//Alter all the components, one by one.
	for (unsigned int currentWidth = 0; currentWidth < width; currentWidth++) {
		for (unsigned int currentHeight = 0; currentHeight < height; currentHeight++) {

			Color sum = Color(0, 0, 0);
			for (int m = -1; m <= 1; m++) {
				if (currentHeight + m >= 0 && currentHeight + m < height) {
					for (int n = -1; n <= 1; n++) {
						if (currentWidth + n >= 0 && currentWidth + n < width) {
							sum += image.getComponent(currentWidth + n, currentHeight + m)
								* filterTable.getComponent(n + 1, m + 1);
						}
					}
				}
			}
			sum = sum.clampToLowerBound(0);
			sum = sum.clampToUpperBound(1);
			newImage.setComponent(currentWidth, currentHeight, sum);
		}

	}
	return newImage;
}