#include <filters.h>
#include <stddef.h>
#include <iostream>
#include <logging.h>

void Filter::Update()
{
	if (img1 != NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: about to update input1", SourceName());
		Logger::LogEvent(msg);
		img1->Update();
		sprintf(msg, "%s: done updating input1", SourceName());
		Logger::LogEvent(msg);
	}
	if (img2 != NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: about to update input2", SourceName());
		Logger::LogEvent(msg);
		img2->Update();
		sprintf(msg, "%s: done updating input2", SourceName());
		Logger::LogEvent(msg);
	}

	char msg[1024];
	sprintf(msg, "%s: about to execute", SourceName());
	Logger::LogEvent(msg);
	Execute();
	sprintf(msg, "%s: done executing", SourceName());
	Logger::LogEvent(msg);
}
