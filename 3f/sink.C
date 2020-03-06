#include <sink.h>
#include <logging.h>
#include <typeinfo>
#include <iostream>
using namespace std;

void Sink::SetInput(Image* img){
	this->img1 = img;
}

void Sink::SetInput2(Image* img){
	this->img2 = img;
}

Image* Sink::GetInput(){
	return this->img1;
}

Image* Sink::GetInput2(){
	return this->img2;
}
Sink::Sink(){
	this->img1 = NULL;
	this->img2 = NULL;
}

Sink::~Sink(){

}

void Sink::CheckNullInput(){
	if(!this->GetInput()){
			char msg[128];
			sprintf(msg, "%s: input1 has not been provided", SinkName());
			DataFlowException e(SinkName(), msg);
			throw e;
	}
}

void Sink::CheckNullInput2(){
	if(!this->GetInput2()){
			char msg[128];
			sprintf(msg, "%s: input2 has not been provided", SinkName());
			DataFlowException e(SinkName(), msg);
			throw e;
	}
}
