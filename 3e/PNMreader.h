#include <stdlib.h>
#include "image.h"
#include "source.h"

class PNMreader: public Source{
public:
	char *filename;
	PNMreader(char *filename);
	~PNMreader();
	virtual void Execute();
	virtual void Update();
};
