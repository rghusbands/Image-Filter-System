
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <logging.h>
#include <cstring>

DataFlowException::DataFlowException(const char* type, const char* err)
{
	char message[1024];
	sprintf(message, "Throwing exception: (%s): %s ", type, err);
	Logger::LogEvent(message);
}



FILE* Logger::logger = fopen("thelog", "w");

void Logger::LogEvent(const char *ev)
{
	fprintf(logger, "%s\n", ev);
}

void Logger::Finalize()
{
	fclose(logger);
}
