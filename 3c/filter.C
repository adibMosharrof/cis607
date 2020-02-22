#include <filter.h>
#include <iostream>
using namespace std;

void Filter::Execute(){

}

void Shrinker::Execute(){
	Image img = *this->img1;
	Image output(img.width/2, img.height/2);
    int i, j;
    int index_output;
    int index_input;
    for (i = 0; i < output.height; i++)
    {
        for (j=0; j < output.width; j++)
        {
        	index_input= img.width * i*2 + j*2;
        	index_output= output.width * i + j;
        	output.data[index_output].red= img.data[index_input].red;
        	output.data[index_output].green= img.data[index_input].green;
        	output.data[index_output].blue= img.data[index_input].blue;
        }
    }
    this-> img = output;
	fprintf(stdout, "Shrinker input height %d width %d output height %d width %d\n", img.height, img.width, output.height, output.width);
}

void LRCombine::Execute(){
	Image leftInput = *this->img1;
	Image rightInput = *this->img2;
	Image output(leftInput.width + rightInput.width, leftInput.height);
	int i, j;
	int index, index_input, index_output;
	for (i = 0; i < leftInput.height; i++)
	{
		for (j=0; j < leftInput.width; j++)
		{
			index_input = leftInput.width * i + j;
			index_output= output.width * i + j;
			output.data[index_output].red=leftInput.data[index_input].red;
			output.data[index_output].green=leftInput.data[index_input].green;
			output.data[index_output].blue=leftInput.data[index_input].blue;
		}
	}

	for (i = 0; i < rightInput.height; i++)
	{
		for (j=0; j < rightInput.width; j++)
		{
			index_input= rightInput.width * i + j;
			index_output = output.width * i + leftInput.width + j;
			output.data[index_output].red=leftInput.data[index_input].red;
			output.data[index_output].green=leftInput.data[index_input].green;
			output.data[index_output].blue=leftInput.data[index_input].blue;
		}
	}
	this->img = output;
	fprintf(stdout, "LR Combine input1 %d x %d input2 %d x %d output %d x %d\n", leftInput.height, leftInput.width, rightInput.height, rightInput.width, img.height, img.width);
}

void TBCombine::Execute(){
	Image topInput = *this->img1;
	Image bottomInput = *this->img2;
	Image img(topInput.width + bottomInput.width, topInput.height + bottomInput.height);
	int i, j;
	int index, index_input, index_output;
	for (i = 0; i < topInput.height; i++)
    {
        for (j=0; j < topInput.width; j++)
        {
        	index_output= img.width * i + j;
        	index_input = topInput.width * i + j;
            img.data[index_output].red=topInput.data[index_input].red;
            img.data[index_output].green=topInput.data[index_input].green;
            img.data[index_output].blue=topInput.data[index_input].blue;
        }
    }
	for (i = 0; i < bottomInput.height; i++)
    {
        for (j=0; j < bottomInput.width; j++)
		{
        	index_output= img.width * (i+topInput.height) +  topInput.width+ j;
        	index_input = bottomInput.width * i + j;
			img.data[index_output].red=bottomInput.data[index_input].red;
			img.data[index_output].green=bottomInput.data[index_input].green;
			img.data[index_output].blue=bottomInput.data[index_input].blue;
		}
	}
	this->img = img;
	fprintf(stdout, "TB Combine input1 %d x %d input2 %d x %d output %d x %d\n", topInput.height, topInput.width, bottomInput.height, bottomInput.width, img.height, img.width);
}

void Blender::Execute(){
	Image input1 = *this->img1;
	Image input2 = *this->img2;
	Image img(input1.width, input1.height);
	double factor = this->factor;
	int i,j;
	fprintf(stdout, "Blender input1 %d x %d input2 %d x %d output %d x %d\n", input1.height, input1.width, input2.height, input2.width, img.height, img.width);
	return ;
	int index_input, index_output;
	for (i = 0; i < input1.height; i++)
    {
        for (j=0; j < input1.width; j++)
        {
        	index_output= img.width * i + j;
        	index_input = input1.width * i + j;
            img.data[index_output].red= factor * input1.data[index_input].red + (1-factor)*input2.data[index_input].red;
            img.data[index_output].green= factor * input1.data[index_input].green + (1-factor)*input2.data[index_input].green;
            img.data[index_output].blue= factor * input1.data[index_input].blue + (1-factor)*input2.data[index_input].blue;
        }
    }
	this->img = img;
}
