#include "Image.h"
#include "FilterGamma.h"
#include "FilterLinear.h"
#include "FilterBlur.h"
#include "FilterLaplace.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace imaging;
using namespace std;

//Checks whether the char * is actually a number
bool isNumeric(const char * param)
{
	char* p;
	strtod(param, &p); //string to double
	return *p == 0;
}

int main(int argc, char* argv[]) {
	using namespace imaging;
	typedef math::Vec3<float> coefficient;
	Image sourceImage, newImage;

	string imageName = "";
	size_t pos;
	string argToString[2];
	string changedImageName, format;

	//If there are no arguments, just terminate the program.
	if (argc == 1) {
		cout << "no parameters!" << endl;
		system("pause");
		return 0;
	}
	else {
		//filter -f gamma 2.0 -f linear -1 -1 -1 1 1 1 image01.ppm
		float linearParam[6];
		bool error = false;
		bool isAlreadyFiltered = false;

		imageName = argv[argc - 1];
		
		// Filtering format and filename
		pos = imageName.find(".");
		format = imageName.substr(pos + 1);
		
		// Loading the data from file
		bool loadResult = sourceImage.load(imageName, format);

		//Check if the parameters from cmd are valid, if so execute the filters mentioned there.
		for (int i = 0; i < argc; i++) {
			argToString[0] = argv[i];
			if (argToString[0] == "-f") {
				argToString[1] = argv[i+1];
				if (argToString[1] == "gamma") {
					if (isNumeric(argv[i + 2])) {
						FilterGamma aGammaFilter(stof(argv[i + 2]));
						if (isAlreadyFiltered) {
							newImage = (aGammaFilter << newImage);
						}
						else {
							newImage = (aGammaFilter << sourceImage);
							isAlreadyFiltered = true;
						}					
						//cout << "Applied a gamma filter." << endl;
					}
					else {
						error = true;
					}
				}
				else if (argToString[1] == "linear") {
					for (int j = 0; j < 6; j++) {
						if (isNumeric(argv[i + (j + 2)])) {
							linearParam[j] = stof(argv[i + (j + 2)]);
						}
						else {
							error = true;
						}
					}
					if (!error) {
						coefficient a(linearParam[0], linearParam[1], linearParam[2]);
						coefficient c(linearParam[3], linearParam[4], linearParam[5]);
						FilterLinear aLinearFilter(a, c);
						if (isAlreadyFiltered) {
							newImage = (aLinearFilter << newImage);
						}
						else {
							newImage = (aLinearFilter << sourceImage);
							isAlreadyFiltered = true;
						}
						//cout << "Applied a linear filter." << endl;
					}
				}
				else if (argToString[1] == "blur") {
					if (isNumeric(argv[i + 2])) {
						FilterBlur aBlurFilter(stoi(argv[i + 2]));
						if (isAlreadyFiltered) {
							newImage = (aBlurFilter << newImage);
						}
						else {
							newImage = (aBlurFilter << sourceImage);
							isAlreadyFiltered = true;
						}
						//cout << "Applied a blur filter." << endl;
					}
					else {
						error = true;
					}
				}
				else if (argToString[1] == "laplace") {
					FilterLaplace aLaplaceFilter = FilterLaplace();
					if (isAlreadyFiltered) {
						newImage = (aLaplaceFilter << newImage);
					}
					else {
						newImage = (aLaplaceFilter << sourceImage);
						isAlreadyFiltered = true;
					}
					//cout << "Aplied a laplace filter." << endl;
				}
				else {
					error = true;
				}
			}
		}
		if (error) {
			cout << "Wrong filter determinant!" << endl;
			system("pause");
			return 0;
		}
		
	}

	changedImageName = "filtered_";
	changedImageName = changedImageName.append(imageName);

	// Writing the data in the new file
	bool saveResult = newImage.save(changedImageName, format);

	system("pause");
	return 0;
}