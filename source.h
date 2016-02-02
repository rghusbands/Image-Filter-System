
#ifndef SOURCE_H
#define SOURCE_H

#include <image.h>

class Source
{
    public:

	Source();
	virtual void Execute() = 0;
	virtual void Update();
	virtual const char* SourceName() = 0;
	Image* GetOutput();
	void setSource();
	
	~Source();

    protected:
	Image img;
};


#endif
