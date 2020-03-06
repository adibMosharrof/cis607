#include "PNMwriter.h"
#include <stdio.h>
#include <typeinfo>
#include <iostream>
using namespace std;


void PNMwriter::Write(char *filename){
    FILE *f = fopen(filename, "wb");
    if (f == NULL)
    {
        printf ("Unable to open '%s' for writing!\n", filename);
        return;
    }
    CheckNullInput();
    Image img1 = *this->GetInput();

    fprintf (f, "P6\n");
    fprintf (f, "%d %d\n", img1.GetWidth(), img1.GetHeight());
    fprintf (f, "%d\n", 255);

    fwrite(img1.GetData(), sizeof(Pixel), img1.GetWidth() * img1.GetHeight(), f);
    fclose(f);
}

const char *PNMwriter::SinkName(){
	return "PNMwriter";
}
