#include <stdlib.h>
#include "image.h"
#include "source.h"

class PNMreader: public Source{
public:
	char *filename;
	PNMreader(char *path);
	~PNMreader();
	virtual void Execute();
	const char* SourceName() { return "PNMreader"; }
	virtual void Update();
};
