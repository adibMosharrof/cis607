#ifndef FILTER_H
#define FILTER_H

#include "source.h"
#include "sink.h"
#include <typeinfo>

class Filter: public Source, public Sink{
public:
	Filter();
	void Update();
	virtual const char *FilterName()=0;
	const char *SourceName(){ return FilterName();};
	const char *SinkName(){ return FilterName();};

	void MatchHeight(Image img1, Image img2);
	void MatchWidth(Image img1, Image img2);
	void MatchDimensions(Image img1, Image img2);

};

class Shrinker : public Filter{
protected:
	void Execute();
	const char *FilterName(){ return "Shrinker";};
};

class LRCombine : public Filter{
protected:
	void Execute();
	const char *FilterName(){ return "LRCombine";};
};

class TBCombine : public Filter{
protected:
	void Execute();
	const char *FilterName(){ return "TBCombine";};
};

class Blender : public Filter{
private:
	double factor;

protected:
	void Execute();
	const char *FilterName(){ return "Blender";};

public:
	void SetFactor(double factor){this->factor = factor;}
	double GetFactor(){return this->factor;}
};

class Mirror : public Filter{
protected:
	void Execute();
	const char *FilterName(){ return "Mirror";};
};

class Rotate: public Filter{
protected:
	void Execute();
	const char *FilterName(){ return "Rotate";};
};

class Subtract : public Filter{
	Pixel SubtractPixel(Pixel p1, Pixel p2);
protected:
	void Execute();
	const char *FilterName(){ return "Subtract";};
};

class Grayscale : public Filter{
protected:
	void Execute();
	const char *FilterName(){ return "Grayscale";};
};

class Blur : public Filter{
protected:
	void Execute();
	const char *FilterName(){ return "Blur";};
};

class Color : public Filter{
public:
	int width, height, red, green, blue;
	Color(int w, int h, int r, int g, int b): width(w), height(h), red(r), green(g), blue(b){}
protected:
	void Execute();
	const char *FilterName(){ return "Color";};
};

class CheckSum: public Sink{
public:
	const char* SinkName() { return "CheckSum";}
	void OutputCheckSum(const char* filename);
};

#endif
