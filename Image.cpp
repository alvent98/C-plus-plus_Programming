#include "ppm/ppm.h"
#include "Image.h"
#include <iostream>
#include <string>

using namespace std;

namespace imaging {
	
	bool Image::load(const std::string & filename, const std::string & format) {
		string nonConstFormat = "   ";
		
		//Set format chars to lowercase
		for (unsigned int i = 0; i < format.length(); i++) {
			nonConstFormat[i] = tolower(format[i]);
		}

		//Checks whether filename format is ".ppm" 
		size_t pos = filename.find(".");
		pos++;
		if (nonConstFormat != filename.substr(pos)) {
			cerr << "The image format is not .ppm!" << endl;
			return false;
		}

		// Wiping out image contents
		width = 0;
		height = 0;
		buffer.clear();
		
		// Calls ReadPPM function
		unsigned int * ptrToWidth = &width;
		unsigned int * ptrToHeight = &height;
		const char * charFilename = filename.c_str();
		float * data = ReadPPM(charFilename, (int *)ptrToWidth, (int*)ptrToHeight);

		cout << "Image dimentions are: " << width << " X " << height << endl;

		//Initialization of buffer
		buffer.resize(width*height, Color());
		int bufferPosition = 0;
		for (unsigned int i = 0; i < width*height * 3; i += 3) {
			buffer[bufferPosition] = Color(data[i], data[i + 1], data[i + 2]);
			bufferPosition++;
		}

		return true;
	}

	bool Image::save(const std::string & filename, const std::string & format) {
		if (buffer.empty() || width == 0 || height == 0) {
			cerr << "Image object was uninitialized!" << endl;
			if (buffer.empty()) cerr << "buffer was empty!" << endl;
			if (width == 0) cerr << "width was 0!" << endl;
			if (height == 0) cerr << "height was 0" << endl;
			return false;
		}
		string nonConstFormat = "   ";
		//Set format chars to lowercase
		for (unsigned int i = 0; i < format.length(); i++) {
			nonConstFormat[i] = tolower(format[i]);
		}

		//Checks whether filename format is ".ppm" 
		size_t pos = filename.find(".");
		pos++;
		if (nonConstFormat != filename.substr(pos)) {
			cerr << "The image format is not .ppm!" << endl;
			return false;
		}

		const char * charFilename = filename.c_str();
		float * data = new float[width*height * 3];

		//Initialization of data;
		int bufferPosition = 0;
		for (unsigned int i = 0; i < width*height * 3; i += 3) {
			data[i] = buffer[bufferPosition].r;
			data[i + 1] = buffer[bufferPosition].g;
			data[i + 2] = buffer[bufferPosition].b;
			bufferPosition++;
		}

		bool result = WritePPM(data, width, height, charFilename);

		return result;
	}
}

