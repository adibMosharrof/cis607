#ifndef IMAGE_H
#define IMAGE_H

class Pixel{
public:
    unsigned char red, green, blue;
    Pixel();
    Pixel(char red, char green, char blue);
};

class Image{
private:
    int width, height;
    Pixel *data;
public:
	Image();
	Image(int width, int height);

    int GetWidth(){return this->width;}
    int GetHeight(){return this->height;}
    void SetData(int index, Pixel p);
    void SetData(Pixel p);
    Pixel GetData(int index);
    Pixel* GetData();
};

#endif
