#include <PNMreader.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <typeinfo>
#include <image.h>
#include <logging.h>
using namespace std;

PNMreader::PNMreader(char *filename){
	this->filename = filename;

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

	if (f == NULL)
	{
		fprintf(stderr, "Unable to open file %s\n", filename);
		return;
	}

	fscanf(f, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
	if (strcmp(magicNum, "P6") != 0)
	{
		fprintf(stderr, "Unable to read file %s, due to format mismatch\n", filename);
		return ;
	}

	Image img (width, height);
	fread(img.GetData(), sizeof(Pixel), width*height, f);
	this->SetOutput(img);
	fclose(f);

//	fprintf(stdout, "Reader %dx%d\n", img.GetWidth(), img.GetHeight());
//	cout << "width is " << this->img.width << endl;
}

