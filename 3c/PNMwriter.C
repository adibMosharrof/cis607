#include <PNMwriter.h>
#include <stdio.h>
#include <iostream>
using namespace std;


void PNMwriter::Write(char *filename){
    FILE *f = fopen(filename, "wb");
    if (f == NULL)
    {
        printf ("Unable to open '%s' for writing!\n", filename);
        return;
    }
    Image img1 = *this->img1;
	fprintf(stdout, "writer input height %d width %d\n", img1.height, img1.width);
    fprintf (f, "P6\n");
    fprintf (f, "%d %d\n", img1.width, img1.height);
    fprintf (f, "%d\n", 255);

    fwrite(img1.data, sizeof(Pixel), img1.width * img1.height, f);
    fclose(f);
}
