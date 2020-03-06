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
};

class Shrinker : public Filter{
protected:
	void Execute();
	const char *FilterName(){ return typeid(this).name();};
};

class LRCombine : public Filter{
protected:
	void Execute();
	const char *FilterName(){ return typeid(this).name();};
};

class TBCombine : public Filter{
protected:
	void Execute();
	const char *FilterName(){ return typeid(this).name();};
};

class Blender : public Filter{
private:
	double factor;

protected:
	void Execute();
	const char *FilterName(){ return typeid(this).name();};

public:
	void SetFactor(double factor){this->factor = factor;}
	double GetFactor(){return this->factor;}
};
