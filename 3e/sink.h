#ifndef SINK_H
#define SINK_H
#include "image.h"

class Sink{
private:
	Image* img1;
	Image* img2;
public:
	Sink();

	void SetInput(Image* img);
	void SetInput2(Image* img);
	Image* GetInput();
	Image* GetInput2();
};

#endif
