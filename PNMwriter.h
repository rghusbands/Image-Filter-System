
#ifndef PNMWRITERCPP_H
#define PNMWRITERCPP_H

#include <sink.h>

class PNMwriter : public Sink
{
    public:

	PNMwriter();
	void Write(const char*);
	const char* SinkName() {return name;}
	~PNMwriter();

    private:
	const char* name;

};

#endif
