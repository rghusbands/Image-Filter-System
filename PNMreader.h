
#ifndef PNMREADERCPP_H
#define PNMREADERCPP_H

#include <logging.h>
#include <source.h>
#include <string>

class PNMreader : public Source
{
    public:
	
	PNMreader(char*);
	void Execute();
	const char* SourceName() {return name;}
	~PNMreader();

    protected:
	char* file;
	const char* name;
};


#endif
