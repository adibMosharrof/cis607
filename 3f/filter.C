#include "filter.h"
#include "logging.h"
#include <typeinfo>
#include <stdio.h>
#include <iostream>
using namespace std;

Filter::Filter(){
}

void Filter::MatchHeight(Image img1, Image img2){
	if (img1.GetHeight() != img2.GetHeight()){
		char msg[128];
	    sprintf(msg, "%s: heights must match: %d, %d", SourceName(), img1.GetHeight(), img2.GetHeight());
	    DataFlowException e(SourceName(), msg);
	    throw e;
	}
}

void Filter::MatchWidth(Image img1, Image img2){
	if (img1.GetWidth() != img2.GetWidth()){
	    char msg[128];
	    sprintf(msg, "%s: widths must match: %d, %d", SourceName(), img1.GetWidth(), img2.GetWidth());
	    DataFlowException e(SourceName(), msg);
	    throw e;
	}
}

void Filter::MatchDimensions(Image img1, Image img2){
	MatchWidth(img1, img2);
	MatchHeight(img1, img2);
}

void Filter::Update(){
	Image* img1 = GetInput();
	Image* img2 = GetInput2();
	char msg[128];
	if (img1){
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);

        img1->Update();

        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);
	}
	if (img2){
		sprintf(msg, "%s: about to update input2", SourceName());
		Logger::LogEvent(msg);
		img2->Update();
		sprintf(msg, "%s: done updating input2", SourceName());
		Logger::LogEvent(msg);
	}
	sprintf(msg, "%s: about to execute", SourceName());
	Logger::LogEvent(msg);
	this->Execute();
	sprintf(msg, "%s: done executing", SourceName());
	Logger::LogEvent(msg);
}

void Shrinker::Execute(){
	CheckNullInput();
	Image img = *this->GetInput();
	Image output(img.GetWidth()/2, img.GetHeight()/2);
    int i, j;
    int index_output;
    int index_input;
    for (i = 0; i < output.GetHeight(); i++)
    {
        for (j=0; j < output.GetWidth(); j++)
        {
        	index_input= img.GetWidth ()* i*2 + j*2;
        	index_output= output.GetWidth() * i + j;
        	output.SetData(index_output, img.GetData(index_input));
        }
    }
    this->SetOutput(output);
//	fprintf(stdout, "Shrinker input height %d width %d output height %d width %d\n", img.height, img.width, output.height, output.width);
}

void LRCombine::Execute(){
	CheckNullInput();
	CheckNullInput2();
	Image leftInput = *this->GetInput();
	Image rightInput = *this->GetInput2();
	MatchHeight(leftInput, rightInput);

	Image output(leftInput.GetWidth() + rightInput.GetWidth(), leftInput.GetHeight());
	int i, j;
	int index, index_input, index_output;
	for (i = 0; i < leftInput.GetHeight(); i++)
	{
		for (j=0; j < leftInput.GetWidth(); j++)
		{
			index_input = leftInput.GetWidth() * i + j;
			index_output= output.GetWidth() * i + j;
			output.SetData(index_output, leftInput.GetData(index_input));
		}
	}

	for (i = 0; i < rightInput.GetHeight(); i++)
	{
		for (j=0; j < rightInput.GetWidth(); j++)
		{
			index_input= rightInput.GetWidth() * i + j;
			index_output = output.GetWidth() * i + rightInput.GetWidth() + j;
			output.SetData(index_output, rightInput.GetData(index_input));
		}
	}
    this->SetOutput(output);
//	fprintf(stdout, "LR Combine input1 %d x %d input2 %d x %d output %d x %d\n", leftInput.height, leftInput.width, rightInput.height, rightInput.width, img.height, img.width);
}

void TBCombine::Execute(){
	CheckNullInput();
	CheckNullInput2();
	Image topInput = *this->GetInput();
	Image bottomInput = *this->GetInput2();
	MatchWidth(topInput, bottomInput);

	Image img(topInput.GetWidth() , topInput.GetHeight() + bottomInput.GetHeight());
	int i, j;
	int index, index_input, index_output;
	for (i = 0; i < topInput.GetHeight(); i++)
    {
        for (j=0; j < topInput.GetWidth(); j++)
        {
        	index_output= img.GetWidth() * i + j;
        	index_input = topInput.GetWidth() * i + j;
        	img.SetData(index_output, topInput.GetData(index_input));
        }
    }
	for (i = 0; i < bottomInput.GetHeight(); i++)
    {
        for (j=0; j < bottomInput.GetWidth(); j++)
		{
        	index_input = bottomInput.GetWidth() * i + j;
        	index_output= img.GetWidth() * (i+topInput.GetHeight()) +  j;
        	img.SetData(index_output, bottomInput.GetData(index_input));
		}
	}
    this->SetOutput(img);
//	fprintf(stdout, "TB Combine input1 %d x %d input2 %d x %d output %d x %d\n", topInput.height, topInput.width, bottomInput.height, bottomInput.width, img.height, img.width);
}

void Blender::Execute(){
	CheckNullInput();
	CheckNullInput2();
	Image input1 = *this->GetInput();
	Image input2 = *this->GetInput2();
	MatchDimensions(input1, input2);

	Image img(input1.GetWidth(), input1.GetHeight());
	double factor = this->GetFactor();
	if (factor > 1.0){
		char msg[128];
		sprintf(msg, "Invalid factor for Blender: %.6lf", factor);
		DataFlowException e(SourceName(), msg);
		throw e;
	}

	int i,j;
	int index_input, index_output;
	for (i = 0; i < input1.GetHeight(); i++)
    {
        for (j=0; j < input1.GetWidth(); j++)
        {
        	index_output= img.GetWidth() * i + j;
        	index_input = input1.GetWidth() * i + j;

        	Pixel p1 = input1.GetData(index_input);
        	Pixel p2 = input2.GetData(index_output);
        	Pixel out(factor * p1.red + (1-factor)*p2.red, factor * p1.green + (1-factor)*p2.green,factor * p1.blue + (1-factor)*p2.blue);

        	img.SetData(index_output, out);
        }
    }
    this->SetOutput(img);
//	fprintf(stdout, "Blender input1 %d x %d input2 %d x %d output %d x %d\n", input1.height, input1.width, input2.height, input2.width, img.height, img.width);
}

Pixel Subtract::SubtractPixel(Pixel p1, Pixel p2){
	char r = (p1.red >= p2.red) ? p1.red - p2.red : 0;
	char g = (p1.green >= p2.green) ? p1.green - p2.green : 0;
	char b = (p1.blue >= p2.blue) ? p1.blue - p2.blue : 0;
	Pixel out(r, g, b);
	return out;
}

void Subtract::Execute(){
	CheckNullInput();
	CheckNullInput2();
	Image input1 = *this->GetInput();
	Image input2 = *this->GetInput2();
	MatchDimensions(input1, input2);

	Image img(input1.GetWidth(), input1.GetHeight());
	int i,j;
	int index_input, index_output;
	for (i = 0; i < input1.GetHeight(); i++)
    {
        for (j=0; j < input1.GetWidth(); j++)
        {
        	index_output= img.GetWidth() * i + j;
        	index_input = input1.GetWidth() * i + j;

        	Pixel p1 = input1.GetData(index_input);
        	Pixel p2 = input2.GetData(index_output);

        	img.SetData(index_output, SubtractPixel(p1,p2));
        }
    }
    this->SetOutput(img);
}

void Grayscale::Execute(){
	CheckNullInput();
	Image input1 = *this->GetInput();

	Image img(input1.GetWidth(), input1.GetHeight());
	int i,j;
	int index_input, index_output;
	for (i = 0; i < input1.GetHeight(); i++)
    {
        for (j=0; j < input1.GetWidth(); j++)
        {
        	index_output= img.GetWidth() * i + j;
        	index_input = input1.GetWidth() * i + j;

        	Pixel p1 = input1.GetData(index_input);
        	int value = p1.red/5 + p1.green/2 + p1.blue/4;
        	Pixel out(value, value, value);
        	img.SetData(index_output, out);
        }
    }
    this->SetOutput(img);
}

void Color::Execute(){
	Image img(width, height);
	int i,j;
	int index_input, index_output;
	for (i = 0; i < height; i++)
    {
        for (j=0; j < width; j++)
        {
        	index_output= img.GetWidth() * i + j;
        	Pixel out(red, green, blue);
        	img.SetData(index_output, out);
        }
    }
    this->SetOutput(img);
}

void Mirror::Execute(){
	CheckNullInput();
	Image img = *this->GetInput();
	Image output(img.GetWidth(), img.GetHeight());
	int width = img.GetWidth();
	int height = img.GetHeight();
    int i, j;
    int index_output;
    int index_input;
    for (i = 0; i < height; i++)
    {
        for (j=0; j < width; j++)
        {
        	index_input= width * i + j;
        	index_output= width * i + width -j-1;
        	output.SetData(index_output, img.GetData(index_input));
        }
    }
    this->SetOutput(output);
}

void Rotate::Execute(){
	CheckNullInput();
	Image img = *this->GetInput();
	int width = img.GetWidth();
	int height = img.GetHeight();
	Image output(height, width);
    int i, j;
    int index_output;
    int index_input;
    for (i = 0; i < height; i++)
    {
        for (j=0; j < width; j++)
        {
        	index_input= width * i + j;
        	index_output= height * j + height - i -1;
        	output.SetData(index_output, img.GetData(index_input));
        }
    }
    this->SetOutput(output);
}

void Blur::Execute(){
	CheckNullInput();
	Image input1 = *this->GetInput();
	int width = input1.GetWidth();
	int height = input1.GetHeight();

	Image img(input1.GetWidth(), input1.GetHeight());
	int i,j;
	int index;
	for (i = 0; i < height; i++)
    {
        for (j=0; j < width; j++)
        {
        	index= width * i + j;
        	if(j ==0 || i ==0 || j ==width -1 || i == height -1){
        		img.SetData(index, input1.GetData(index));
        	}else{
        		Pixel input_pixel = input1.GetData(index);
        		Pixel p1 = input1.GetData(index-1);
        		Pixel p2 = input1.GetData(index+1);
        		Pixel p3 = input1.GetData(index -width -1);
        		Pixel p4 = input1.GetData(index-width);
        		Pixel p5 = input1.GetData(index-width+1);
        		Pixel p6 = input1.GetData(index+width-1);
        		Pixel p7 = input1.GetData(index+width);
        		Pixel p8 = input1.GetData(index+width+1);

        		input_pixel.red = p1.red/8+p2.red/8+p3.red/8+p4.red/8+p5.red/8+p6.red/8+p7.red/8+p8.red/8;
        		input_pixel.green = p1.green/8+p2.green/8+p3.green/8+p4.green/8+p5.green/8+p6.green/8+p7.green/8+p8.green/8;
        		input_pixel.blue = p1.blue/8+p2.blue/8+p3.blue/8+p4.blue/8+p5.blue/8+p6.blue/8+p7.blue/8+p8.blue/8;
        		img.SetData(index, input_pixel);
        	}
        }
    }
    this->SetOutput(img);
}

void CheckSum::OutputCheckSum(const char* filename){
	CheckNullInput();
	Image img = *this->GetInput();
	unsigned char r=0, g =0, b=0;
	for (int i=0; i < img.GetHeight()* img.GetWidth(); i++){
		Pixel p1 = img.GetData(i);
		r+= p1.red;
		g+= p1.green;
		b+= p1.blue;
	}
	FILE *file = fopen(filename, "w");
	fprintf(file, "CHECKSUM: %d, %d, %d\n", r, g, b);
	fclose(file);
}
