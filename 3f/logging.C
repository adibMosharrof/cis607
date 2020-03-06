#include "logging.h"
#include <stdio.h>

FILE* Logger::logger;

void Logger::LogEvent(const char *event){
	if (logger == NULL){
		logger = fopen("logger","w");
	}
	fprintf(logger, "%s\n", event);
}

void Logger::Finalize(){
	if (!logger)
		return;
	fflush(logger);
	fclose(logger);
	logger = NULL;
}

DataFlowException::DataFlowException(const char *type, const char *error){
	sprintf(msg, "Throwing exception: (%s): %s", type, error);
	Logger::LogEvent(msg);
}
