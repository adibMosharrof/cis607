#include "source.h"
#include "sink.h"

class Filter: public Source, public Sink{
public:
	Filter();
	void Update();
};

class Shrinker : public Filter{
protected:
	void Execute();
};

class LRCombine : public Filter{
protected:
	void Execute();
};

class TBCombine : public Filter{
protected:
	void Execute();
};

class Blender : public Filter{
private:
	double factor;

protected:
	void Execute();

public:
	void SetFactor(double factor){this->factor = factor;}
	double GetFactor(){return this->factor;}
};
