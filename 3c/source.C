#include <source.h>
#include <iostream>
using namespace std;

Image* Source::GetOutput(){
//	cout << "width  " << this->img.width << endl;
	return &this->img;
}

Source::Source(){

}
Source::~Source(){

}

void Source::Execute(){

}
