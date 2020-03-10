#include "filter.h"
#include <typeinfo>
#include <iostream>
using namespace std;

Filter::Filter(){
}

void Filter::Update(){
	Image* img1 = GetInput();
	Image* img2 = GetInput2();
	if (img1){
		img1->Update();
	}
	if (img2){
		img2->Update();
	}
	this->Execute();
	if(img1)
		img1->DeleteSource();
	if(img2)
		img2->DeleteSource();
}

void Shrinker::Execute(){
	Image img = *this->GetInput();
	Image output(img.GetWidth()/2, img.GetHeight()/2);
	output.ResetSize(img.GetWidth()/2, img.GetHeight()/2);
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
	Image leftInput = *this->GetInput();
	Image rightInput = *this->GetInput2();
	Image output(leftInput.GetWidth() + rightInput.GetWidth(), leftInput.GetHeight());
	output.ResetSize(leftInput.GetWidth() + rightInput.GetWidth(), leftInput.GetHeight());
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
			index_output = output.GetWidth() * i + leftInput.GetWidth() + j;
			output.SetData(index_output, rightInput.GetData(index_input));
		}
	}
    this->SetOutput(output);
}

void TBCombine::Execute(){
	Image topInput = *this->GetInput();
	Image bottomInput = *this->GetInput2();
	Image img(topInput.GetWidth() , topInput.GetHeight() + bottomInput.GetHeight());
	img.ResetSize(topInput.GetWidth() , topInput.GetHeight() + bottomInput.GetHeight());
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
}

void Blender::Execute(){
	Image input1 = *this->GetInput();
	Image input2 = *this->GetInput2();
	Image img(input1.GetWidth(), input1.GetHeight());
	img.ResetSize(input1.GetWidth(), input1.GetHeight());
	double factor = this->GetFactor();
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
}

