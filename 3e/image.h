#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
using namespace std;

class Source;

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
    Source *source;
//    friend std::ostream& operator<<(std::ostream&, const Image&);
public:
	Image();
//	~Image();
	Image(int width, int height);
	void Delete();
	void DeleteSource();

    void Update();
    void SetSource(Source *src);

    int GetWidth(){return this->width;}
    int GetHeight(){return this->height;}

    void SetData(int index, Pixel p);
    void SetData(Pixel p);

    Pixel GetData(int index);
    Pixel* GetData();

};

#endif
