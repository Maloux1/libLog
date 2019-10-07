#include "liblog.h"

void libLog(char logType, char * title, char * message, char checkErrno, char * FILE, int LINE){
	
	int trueErrno = errno;
	time_t logTimeValue = time(NULL);
	char logErrorType[16], openColor[10];
	int outFile = fileno(stderr);

	switch (logType){
		case LIBLOG_LOG_INFO:
			strncpy(logErrorType, "INFO", 16);
			strncpy(openColor, "\x1b[36m", 9);
			outFile = fileno(stdout);
			break;
		case LIBLOG_LOG_DEBUG:
			strncpy(logErrorType, "DEBUG", 16);
			strncpy(openColor, "\x1b[35m", 9);
			outFile = fileno(stdout);
			break;
		case LIBLOG_LOG_WARNING:
			strncpy(logErrorType, "WARNING", 16);
			strncpy(openColor, "\x1b[33m", 9);
			break;
		case LIBLOG_LOG_ERROR:
			strncpy(logErrorType, "ERROR", 16);
			strncpy(openColor, "\x1b[31m", 9);
			break;
		case LIBLOG_LOG_FATALERROR:
			strncpy(logErrorType, "FATAL_ERROR", 16);
			strncpy(openColor, "\x1b[1;31m", 9);
			break;
		default:
			strncpy(logErrorType, "???", 16);
			strncpy(openColor, "\x1b[36m", 9);
			break;
	}
	
	if (isatty(outFile)){
		dprintf(outFile, "\x1b[1m%.24s\x1b[0m [%s] %s%-11s\x1b[0m \x1b[4m%s:%d\x1b[0m => %s\n", ctime(&logTimeValue), title, openColor, logErrorType, FILE, LINE, message);
	}
	else {
		dprintf(outFile, "%.24s [%s] %-11s %s:%d => %s\n", ctime(&logTimeValue), title, logErrorType, FILE, LINE, message);

	}
	if (checkErrno && errno != 0){
		dprintf(outFile, "> errno is %d\n> %s\n" , trueErrno, strerror(trueErrno));
	}
	dprintf(outFile, "\n");
}
