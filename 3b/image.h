#ifndef IMAGE_H
#define IMAGE_H

struct Pixel{
    unsigned char red, green, blue;
    Pixel();
};

struct Image{
	Image();
	Image(int width, int height);
    int width, height;
    Pixel *data;
};

#endif
