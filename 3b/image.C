#include <image.h>
#include <stdlib.h>

Image::Image(){

};

Image::Image(int w, int h){
	width = w;
	height = h;
	data = (Pixel*) malloc(width * height * sizeof(Pixel));
};


Pixel::Pixel(){

}
