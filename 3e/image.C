#include "image.h"
#include <stdlib.h>
#include "source.h"
#include <typeinfo>
#include <iostream>
using namespace std;

Pixel::Pixel(char red, char green, char blue){
	this->red = red;
	this->green = green;
	this->blue = blue;
}

Pixel::Pixel(){

}
Image::Image(){
	source = NULL;
}

//Image::~Image(){
//}

void Image::Delete(){
	if(!data)
		return;
	delete [] data;
	data = NULL;
};

void Image::DeleteSource(){
	if(source)
		source->Delete();
}

void Image::ResetSize(int w, int h){
	Delete();
	width = w;
	height = h;
	data = new Pixel[width*height];
//	data = (Pixel*) malloc(width * height * sizeof(Pixel));
}

void Image::SetData(int i, Pixel p){
	this->data[i] = p;
}

Pixel Image::GetData(int i){
	return this->data[i];
}

Pixel* Image::GetData(){
	return this->data;
}

void Image::SetData(Pixel p){
	this->data = &p;
}

void Image::Update(){
	if(this->source){
		this->source->Update();
	}
}

void Image::SetSource(Source *src){
	this->source = src;
	this->data = 0;
}


//std::ostream& operator<<(std::ostream &strm, const Image &a) {
//  return strm << "Image height " << a.height << " width " << a.width << endl;
//}
