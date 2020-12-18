#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace math {
	template <typename T>
	class Array
	{
	protected:
		vector<T> buffer;                              //! Holds the image data.

		unsigned int width, 						 //! The width of the image (in Components)
			height;		                 //! The height of the image (in Components)

	public:
		//Getters of the array's properties
		unsigned int getWidth() { return width; }
		unsigned int getHeight() { return height; }

		vector<T> getBigVector() { return buffer; }

		// Getter of single component
		T getComponent(unsigned int x, unsigned int y) const {
			if (x >= 0 && y >= 0 && x < width && y < height) {
				return buffer[y*width + x];
			}
			else {
				cerr << "getComponent::Orizontical or vertical index out of bounds! Actually, it's (x,y): (" << x << "," << y << ")" << endl;
			}
		}

		// Setter of single component
		void setComponent(unsigned int x, unsigned int y, T & value) {
			if (x >= 0 && y >= 0 && x < width && y < height) {
				if (value.r >= 0 && value.r <= 1) {
					if (value.g >= 0 && value.g <= 1) {
						if (value.b >= 0 && value.b <= 1) {
							buffer[y*width + x] = value;
						}
						else {
							cerr << "Blue Color depth range out of bounds!" << endl;
						}
					}
					else {
						cerr << "Green Color depth range out of bounds!" << endl;
					}
				}
				else {
					cerr << "Red Color depth range out of bounds! Actually, it is: " << value.r << endl;
				}
			}
			else {
				cerr << "setComponent::Orizontical or vertical index out of bounds!" << endl;
			}
		}

		// Setter of the whole buffer
		void setData(const vector<T> & data_ptr) {
			if (data_ptr.empty() || buffer.empty() || width == 0 || height == 0) {
				cerr << "buffers were null or width/height was 0." << endl;
			}
			else {
				for (unsigned int i = 0; i < width*height; i++) {
					buffer[i] = data_ptr[i];
				}
			}
		}

		//Default Constructor
		Array() {
			width = 0;
			height = 0;
			buffer.clear();
		}

		//Constructor with 2 args
		Array(unsigned int width, unsigned int height) {
			this->width = width;
			this->height = height;
		}

		//Constructor with 3 args
		Array(unsigned int width, unsigned int height, const vector<T> data_ptr) {
			this->width = width;
			this->height = height;
			buffer = data_ptr;
			if (buffer.empty()) {
				cout << "Array 3-parameters Constructor::buffer is empty. " << endl;
			}
			if (data_ptr.empty()) {
				cout << "Array 3-parameters Constructor::Dataptr is empty. " << endl;
			}
		}

		// Copy Constractor
		Array(const T &src) {
			Array(src.width, src.height, src.buffer);
		}

		// Destructor
		~Array() {
			buffer.clear();
		}

		//Assignment operator
		Array & operator = (const Array & right) {
			width = right.width;
			height = right.height;
			buffer = right.buffer;
			return *this;
		}

		//Operator of access of a specific component - actually a getter
		T & operator()  (int row, int column) {
			return buffer[width*row + column];
		}
	};
}