
#ifndef SINK_H
#define SINK_H

#include <image.h>
#include <stdlib.h>
#include <logging.h>

class Sink
{
    public:
	Sink();
	void OneInputCheck();
	void TwoInputCheck();
	void SetInput(Image* in1) {img1 = in1;}
	void SetInput2(Image* in2) {img2 = in2;}
	virtual const char* SinkName() = 0;
	virtual	~Sink();

    protected:
	const Image* img1;
	const Image* img2;
};


#endif
