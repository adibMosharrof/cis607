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
private:
	double factor;
public:
	void Execute();
	void SetFactor(double factor){this->factor = factor;}
	double GetFactor(){return this->factor;}
};
