#include <image.h>
#include <stdlib.h>

Image::Image(){

};

Image::Image(int w, int h){
	this->width = w;
	this->height = h;
	this->data = (Pixel*) malloc(width * height * sizeof(Pixel));
};

void Image::ResetSize(int width, int height){
	this->width = width;
	this->height = height;
	this->data = (Pixel*) malloc(width * height * sizeof(Pixel));
}


Pixel::Pixel(){

}
