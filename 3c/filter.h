#include <source.h>
#include <sink.h>

class Filter: public Source, public Sink{
public:
	virtual void Execute();
};

class Shrinker : public Filter{
public:
	void Execute();
};

class LRCombine : public Filter{
public:
	void Execute();
};

class TBCombine : public Filter{
public:
	void Execute();
};

class Blender : public Filter{
public:
	double factor;
	void Execute();
	void SetFactor(double factor){this->factor = factor;}
};
