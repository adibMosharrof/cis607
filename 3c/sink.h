#ifndef SINK_H
#define SINK_H
#include <image.h>

class Sink{
public:
	Image* img1;
	Image* img2;
	Sink();
	~Sink();

	void SetInput(Image* img);

	void SetInput2(Image* img);
};

#endif
