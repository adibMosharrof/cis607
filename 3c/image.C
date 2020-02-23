#include <image.h>
#include <stdlib.h>

Pixel::Pixel(char red, char green, char blue){
	this->red = red;
	this->green = green;
	this->blue = blue;
}

Image::Image(){

};

Image::Image(int w, int h){
	width = w;
	height = h;
	data = (Pixel*) malloc(width * height * sizeof(Pixel));
};

void Image::SetData(int i, Pixel p){
	this->data[i] = p;
}

Pixel Image::GetData(int i){
	return this->data[i];
}
