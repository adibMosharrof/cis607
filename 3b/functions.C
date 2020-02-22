#include <image.h>
#include <functions.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

void ReadImage(char *filename, Image &output){
    FILE *f = fopen(filename, "r");
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
    output = img;
    fclose(f);
}

void HalfSize(Image &input, Image &output){
	Image img(input.width/2, input.height/2);

    int i, j;
    int index_output;
    int index_input;
    for (i = 0; i < img.height; i++)
    {
        for (j=0; j < img.width; j++)
        {
        	index_input= input.width * i*2 + j*2;
        	index_output= img.width * i + j;
            img.data[index_output].red=input.data[index_input].red;
            img.data[index_output].green=input.data[index_input].green;
            img.data[index_output].blue=input.data[index_input].blue;
        }
    }
    output = img;
}

void LeftRightCombine(Image &leftInput, Image &rightInput, Image &output){
	Image img(leftInput.width + rightInput.width, leftInput.height);
	int i, j;
	int index, index_input, index_output;
	for (i = 0; i < leftInput.height; i++)
    {
        for (j=0; j < leftInput.width; j++)
        {
        	index_output= img.width * i + j;
        	index_input = leftInput.width * i + j;
            img.data[index_output].red=leftInput.data[index_input].red;
            img.data[index_output].green=leftInput.data[index_input].green;
            img.data[index_output].blue=leftInput.data[index_input].blue;
        }
    }

	for (i = 0; i < rightInput.height; i++)
	{
		for (j=0; j < rightInput.width; j++)
		{
			index_input= rightInput.width * i + j;
			index_output = img.width * i + leftInput.width + j;
			img.data[index_output].red=leftInput.data[index_input].red;
			img.data[index_output].green=leftInput.data[index_input].green;
			img.data[index_output].blue=leftInput.data[index_input].blue;
		}
	}
	output = img;
}

void TopBottomCombine(Image &topInput, Image &bottomInput, Image &output){
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
	output = img;
}

void Blend(Image &input1, Image &input2, double factor, Image &output){
	Image img(input1.width, input1.height);
	int i,j;
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

//            img.data[index_output].red= factor * input2.data[index_input].red ;
//            img.data[index_output].green= factor * input2.data[index_input].green;
//            img.data[index_output].blue= factor * input2.data[index_input].blue ;
        }
    }
	output = img;
}


void WriteImage(char *filename, Image &img){
    FILE *f = fopen(filename, "wb");

    if (f == NULL)
    {
        printf ("Unable to open '%s' for writing!\n", filename);
        return;
    }

    fprintf (f, "P6\n");
    fprintf (f, "%d %d\n", img.width, img.height);
    fprintf (f, "%d\n", 255);

    fwrite(img.data, sizeof(Pixel), img.width * img.height, f);
    fclose(f);
}
