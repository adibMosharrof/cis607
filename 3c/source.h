#ifndef SOURCE_H
#define SOURCE_H
#include <image.h>

class Source{
public:
	Source();
	virtual ~Source();
	Image img;
	virtual void Execute() = 0;
	Image* GetOutput();

	void SetImage(Image img){this->img = img;}
};

#endif
