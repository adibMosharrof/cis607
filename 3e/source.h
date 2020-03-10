#ifndef SOURCE_H
#define SOURCE_H
#include "image.h"
#include <iostream>
using namespace std;

class Source{
private:

protected:
	virtual void Execute() = 0;

public:
	Image img;
	Source();
	virtual ~Source();
	Image* GetOutput(){ return &this->img; }
	void SetOutput(Image img){this->img = img;}

	virtual void Update()=0;
	void Delete(){ img.Delete();}
};

#endif
