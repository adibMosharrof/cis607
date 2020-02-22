#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <image.h>
using namespace std;

PNMreader::PNMreader(char *filename){
	this->filename = filename;
}
PNMreader::~PNMreader(){
	delete this->filename;
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

	fread(img.data, sizeof(Pixel), width*height, f);
	this->img = img;
	fclose(f);

//	cout << "width is " << this->img.width << endl;
}

