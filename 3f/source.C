#include "source.h"
#include "logging.h"
#include <iostream>
using namespace std;


Source::Source(){
	img.SetSource(this);
}
Source::~Source(){

}

//void Source::Update(){
//	char msg[128];
//	sprintf(msg, "%s: about to execute", SourceName());
//	Logger::LogEvent(msg);
//	this->Execute();
//	sprintf(msg, "%s: done executing", SourceName());
//	Logger::LogEvent(msg);
//}
void Source::Update(){

}
