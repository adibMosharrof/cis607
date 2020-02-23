#include <sink.h>

void Sink::SetInput(Image* img){
	this->img1 = img;
}

void Sink::SetInput2(Image* img){
	this->img2 = img;
}

Image Sink::GetInput(){
	return *this->img1;
}

Image Sink::GetInput2(){
	return *this->img2;
}
Sink::Sink(){

}

Sink::~Sink(){

}
