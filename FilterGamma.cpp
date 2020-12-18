#include "FilterGamma.h"

// Copy Constructor
FilterGamma::FilterGamma(const FilterGamma & aFilter) {
	gamma = aFilter.gamma;
}

Image FilterGamma::operator<< (const Image & image) {
	//Create the new image object that is going to be returned
	Image newImage = image;

	float gamma = getGamma();

	//Alter all the components, one by one.
	for (unsigned int width = 0; width< newImage.getWidth(); width++) {
		for (unsigned int height = 0; height < newImage.getHeight(); height++) {
			Color aColor = image.getComponent(width,height);
			for (int i = 0; i < 3; i++) aColor[i] = pow(aColor[i], gamma);
			aColor = aColor.clampToLowerBound(0);
			aColor = aColor.clampToUpperBound(1);
			newImage.setComponent(width, height, aColor);
		}
		
	}
	return newImage;
}