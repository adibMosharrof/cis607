#ifndef IMAGE_H
#define IMAGE_H

class Pixel{
public:
    unsigned char red, green, blue;
    Pixel();
};

class Image{
public:
	Image();
	Image(int width, int height);
    int width, height;
    Pixel *data;
};

#endif
