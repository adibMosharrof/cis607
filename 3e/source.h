#ifndef SOURCE_H
#define SOURCE_H
#include "image.h"
#include <iostream>
using namespace std;

class Source{
private:
	Image img;

protected:
	virtual void Execute() = 0;

public:
	Source();
	virtual ~Source();
	Image* GetOutput(){ return &this->img; }
	void SetOutput(Image img){this->img = img;}

	virtual void Update()=0;
};

#endif
