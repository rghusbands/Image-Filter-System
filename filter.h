

#ifndef FILTER_H
#define FILTER_H

#include <source.h>
#include <sink.h>

class Filter: public Source, public Sink

{
    public:
	virtual void Update();
	const char* SourceName() {return FilterName();}
	const char* SinkName() {return FilterName();}
	virtual const char* FilterName() = 0;
};

#endif
