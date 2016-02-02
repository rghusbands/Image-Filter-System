#include <image.h>
#include <source.h>
#include <logging.h>

Source::Source()
{
	img.setSource(this);
}

void Source::Update()
{
	char msg[1024];
	sprintf(msg, "%s: about to execute", SourceName());
	Logger::LogEvent(msg);
	Execute();
	sprintf(msg, "%s: done executing", SourceName());
	Logger::LogEvent(msg);

}

Image* Source::GetOutput()
{
	return &img;
}

Source::~Source()
{

}
