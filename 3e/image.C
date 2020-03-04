#include <image.h>
#include <stdlib.h>
#include <source.h>
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
//	cout << "setting img source " << typeid(*src).name() << endl;
	this->source = src;
}
