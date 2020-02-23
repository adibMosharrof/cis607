#ifndef SOURCE_H
#define SOURCE_H
#include <image.h>

class Source{
private:
	Image img;

public:
	Source();
	virtual ~Source();
	virtual void Execute() = 0;
	Image* GetOutput();
	void SetOutput(Image img){this->img = img;}
};

#endif
