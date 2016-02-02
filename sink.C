#include <sink.h>
#include <iostream>

Sink::Sink()
{
	img1 = NULL;
	img2 = NULL;
}

void Sink::OneInputCheck()
{
	if (img1 == NULL)
	{
		char msg[1024];
		sprintf(msg, "No img1 was passed");
		throw DataFlowException (SinkName(), msg);
	}
}

void Sink::TwoInputCheck()
{
	if (img1 == NULL)
	{
		char msg[1024];
		sprintf(msg, "No img1 was passed");
		throw DataFlowException (SinkName(), msg);
	}
	if (img2 == NULL)
	{
		char msg[1024];
		sprintf(msg, "No img2 was passed");
		throw DataFlowException (SinkName(), msg);
	}

}

Sink::~Sink()
{

}
