#ifndef SINK_H
#define SINK_H
#include "image.h"

class Sink{
private:
	const Image* img1;
	const Image* img2;
public:
	Sink();
	~Sink();

	void SetInput(Image* img);
	void SetInput2(Image* img);
	Image* GetInput();
	Image* GetInput2();

	virtual const char *SinkName()=0;

	void CheckNullInput();
	void CheckNullInput2();
};

#endif
