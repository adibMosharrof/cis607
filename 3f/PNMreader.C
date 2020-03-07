#include "PNMreader.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <typeinfo>
#include "image.h"
#include "logging.h"
using namespace std;

PNMreader::PNMreader(char *path){
	this->filename = new char[strlen(path)+1];
	strcpy(this->filename, path);

}
PNMreader::~PNMreader(){
	delete this->filename;
}

void PNMreader::Update(){
	char msg[128];
	sprintf(msg, "%s: about to execute", SourceName());
	Logger::LogEvent(msg);
	this->Execute();
	sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}

void PNMreader::Execute(){
	FILE *f = fopen(this->filename, "r");
	char magicNum[128];
	int  width, height, maxval;

	char msg[128];
	if (f == NULL)
	{
		sprintf(msg, "Unable to open file %s\n", filename) ;
		DataFlowException e(SourceName(), msg);
		throw e;
	}

	fscanf(f, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
	if (strcmp(magicNum, "P6") != 0)
	{
		sprintf(msg, "Unable to read file %s, due to format mismatch\n", filename);
		DataFlowException e(SourceName(), msg);
		throw e;
	}

	Image img (width, height);
	fread(img.GetData(), sizeof(Pixel), width*height, f);
	this->SetOutput(img);
	fclose(f);

//	fprintf(stdout, "Reader %dx%d\n", img.GetWidth(), img.GetHeight());
//	cout << "width is " << this->img.width << endl;
}

