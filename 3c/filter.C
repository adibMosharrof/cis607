#include <filter.h>
#include <iostream>
using namespace std;

void Filter::Execute(){

}

void Shrinker::Execute(){
	Image img = *this->img1;
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
//        	output.data[index_output].red= img.data[index_input].red;
//        	output.data[index_output].green= img.data[index_input].green;
//        	output.data[index_output].blue= img.data[index_input].blue;
        }
    }
    this->SetImage(output);
//	fprintf(stdout, "Shrinker input height %d width %d output height %d width %d\n", img.height, img.width, output.height, output.width);
}

void LRCombine::Execute(){
	Image leftInput = *this->img1;
	Image rightInput = *this->img2;
	Image output(leftInput.GetWidth() + rightInput.GetWidth(), leftInput.GetHeight());
	int i, j;
	int index, index_input, index_output;
	for (i = 0; i < leftInput.GetHeight(); i++)
	{
		for (j=0; j < leftInput.GetWidth(); j++)
		{
			index_input = leftInput.GetWidth() * i + j;
			index_output= output.GetWidth() * i + j;
			output.SetData(index_output, img.GetData(index_input));
//			output.data[index_output].red=leftInput.data[index_input].red;
//			output.data[index_output].green=leftInput.data[index_input].green;
//			output.data[index_output].blue=leftInput.data[index_input].blue;
		}
	}

	for (i = 0; i < rightInput.GetHeight(); i++)
	{
		for (j=0; j < rightInput.GetWidth(); j++)
		{
			index_input= rightInput.GetWidth() * i + j;
			index_output = output.GetWidth() * i + rightInput.GetWidth() + j;
			output.SetData(index_output, img.GetData(index_input));
//			output.data[index_output].red=rightInput.data[index_input].red;
//			output.data[index_output].green=rightInput.data[index_input].green;
//			output.data[index_output].blue=rightInput.data[index_input].blue;
		}
	}
//	this->img = output;
    this->SetImage(output);
//	fprintf(stdout, "LR Combine input1 %d x %d input2 %d x %d output %d x %d\n", leftInput.height, leftInput.width, rightInput.height, rightInput.width, img.height, img.width);
}

void TBCombine::Execute(){
	Image topInput = *this->img1;
	Image bottomInput = *this->img2;
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
//            img.data[index_output].red=topInput.data[index_input].red;
//            img.data[index_output].green=topInput.data[index_input].green;
//            img.data[index_output].blue=topInput.data[index_input].blue;
        }
    }
	for (i = 0; i < bottomInput.GetHeight(); i++)
    {
        for (j=0; j < bottomInput.GetWidth(); j++)
		{
        	index_input = bottomInput.GetWidth() * i + j;
        	index_output= img.GetWidth() * (i+topInput.GetHeight()) +  j;
        	img.SetData(index_output, bottomInput.GetData(index_input));
//			img.data[index_output].red=bottomInput.data[index_input].red;
//			img.data[index_output].green=bottomInput.data[index_input].green;
//			img.data[index_output].blue=bottomInput.data[index_input].blue;
		}
	}
//	this->img = img;
    this->SetImage(img);
//	fprintf(stdout, "TB Combine input1 %d x %d input2 %d x %d output %d x %d\n", topInput.height, topInput.width, bottomInput.height, bottomInput.width, img.height, img.width);
}

void Blender::Execute(){
	Image input1 = *this->img1;
	Image input2 = *this->img2;
	Image img(input1.GetWidth(), input1.GetHeight());
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
//            img.data[index_output].red= factor * input1.data[index_input].red + (1-factor)*input2.data[index_input].red;
//            img.data[index_output].green= factor * input1.data[index_input].green + (1-factor)*input2.data[index_input].green;
//            img.data[index_output].blue= factor * input1.data[index_input].blue + (1-factor)*input2.data[index_input].blue;
        }
    }
//	this->img = img;
    this->SetImage(img);
//	fprintf(stdout, "Blender input1 %d x %d input2 %d x %d output %d x %d\n", input1.height, input1.width, input2.height, input2.width, img.height, img.width);
}

