#pragma once
#include "FilterBlur.h"
#include "Array.h"

// Copy Constructor
FilterBlur::FilterBlur(const FilterBlur & aFilter) {
	N = aFilter.N;
}

Image FilterBlur::operator<< (const Image & image) {
	//Create the new image object that is going to be returned
	Image newImage = image;

	int N = getN();
	unsigned int width = newImage.getWidth();
	unsigned int height = newImage.getHeight();

	//Create a vector of floats, with N*N elements, each of them set at 1.0/(N*N)
	vector<float> dataTable (N*N, 1.F / (N*N));
	
	//Create an array object with T = float, that contains the dataTable vector (just a container)
	math::Array<float> filterTable(N,N,dataTable);

	//Alter all the components, one by one.
	for (unsigned int currentWidth = 0; currentWidth < width; currentWidth++) {
		for (unsigned int currentHeight = 0; currentHeight < height; currentHeight++) {

			Color sum = Color(0,0,0);
			for (int m = (-1)*N / 2; m < N / 2; m++) {
				if (currentHeight + m >= 0 && currentHeight + m < height) {
					for (int n = (-1)*N / 2; n < N / 2; n++) {
						if (currentWidth + n >= 0 && currentWidth + n < width) {
							sum += image.getComponent(currentWidth + n, currentHeight + m) 
								* filterTable.getComponent(n + N / 2, m + N / 2);
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
