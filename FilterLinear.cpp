#include "FilterLinear.h"

// Copy Constructor
FilterLinear::FilterLinear(const FilterLinear & aFilter) {
	a = aFilter.a;
	c = aFilter.c;
}

Image FilterLinear::operator<< (const Image & image) {
	//Create the new image object that is going to be returned
	Image newImage = image;

	//Coefficient is just a typedef of  math::Vec3<float> 
	coefficient a = getA();
	coefficient c = getC();

	//Alter all the components, one by one.
	for (unsigned int width = 0; width < newImage.getWidth(); width++) {
		for (unsigned int height = 0; height < newImage.getHeight(); height++) {
			Color aColor = image.getComponent(width, height);
			aColor = aColor * a + c;
			aColor = aColor.clampToLowerBound(0);
			aColor = aColor.clampToUpperBound(1);
			newImage.setComponent(width, height, aColor);
		}

	}
	return newImage;
}