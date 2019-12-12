#include "record.h"
#include "config.h"

extern int record_enabled[5];
void enable_record(int info, int debug, int warning, int error, int fatalerror){
	if (info){
		record_enabled[RECORD_LOG_INFO] = 1;
	}
	else {
		record_enabled[RECORD_LOG_INFO] = 0;
	}
	if (debug){
		record_enabled[RECORD_LOG_DEBUG] = 1;
	}
	else {
		record_enabled[RECORD_LOG_DEBUG] = 0;
	}
	if (warning){
		record_enabled[RECORD_LOG_WARNING] = 1;
	}
	else {
		record_enabled[RECORD_LOG_WARNING] = 0;
	}
	if (error){
		record_enabled[RECORD_LOG_ERROR] = 1;
	}
	else {
		record_enabled[RECORD_LOG_ERROR] = 0;
	}
	if (fatalerror){
		record_enabled[RECORD_LOG_FATALERROR] = 1;
	}
	else {
		record_enabled[RECORD_LOG_FATALERROR] = 0;
	}
	return;
}
void enable_record_all(int boolean){
	if (boolean){
		record_enabled[0] = 1;
		record_enabled[1] = 1;
		record_enabled[2] = 1;
		record_enabled[3] = 1;
		record_enabled[4] = 1;
		return;
	}
	record_enabled[0] = 0;
	record_enabled[1] = 0;
	record_enabled[2] = 0;
	record_enabled[3] = 0;
	record_enabled[4] = 0;
	return;
}

void record(char logType, char * title, char * message, char checkErrno, char * FILE, int LINE){
	if (logType < 0 || logType > 4){
		return;
	}
	if (record_enabled[logType] == 0){
		return;
	}
	int trueErrno = errno;
	time_t logTimeValue = time(NULL);
	char logErrorType[16], openColor[10];
	int outFile = fileno(stderr);

	switch (logType){
		case RECORD_LOG_INFO:
			strncpy(logErrorType, "INFO", 16);
			strncpy(openColor, "\x1b[36m", 9);
			outFile = fileno(stdout);
			break;
		case RECORD_LOG_DEBUG:
			strncpy(logErrorType, "DEBUG", 16);
			strncpy(openColor, "\x1b[35m", 9);
			outFile = fileno(stdout);
			break;
		case RECORD_LOG_WARNING:
			strncpy(logErrorType, "WARNING", 16);
			strncpy(openColor, "\x1b[33m", 9);
			break;
		case RECORD_LOG_ERROR:
			strncpy(logErrorType, "ERROR", 16);
			strncpy(openColor, "\x1b[31m", 9);
			break;
		case RECORD_LOG_FATALERROR:
			strncpy(logErrorType, "FATAL_ERROR", 16);
			strncpy(openColor, "\x1b[1;31m", 9);
			break;
		default:
			strncpy(logErrorType, "???", 16);
			strncpy(openColor, "\x1b[36m", 9);
			break;
	}
	
	if (isatty(outFile)){
		dprintf(outFile, "\x1b[1m%.24s\x1b[0m [%s] %s%-11s\x1b[0m \x1b[4m%s:%d\x1b[0m %s\n", ctime(&logTimeValue), title, openColor, logErrorType, FILE, LINE, message);
	}
	else {
		dprintf(outFile, "%.24s [%s] %-11s %s:%d %s\n", ctime(&logTimeValue), title, logErrorType, FILE, LINE, message);

	}
	if (checkErrno && trueErrno != 0){
		dprintf(outFile, "\t> errno is %d\n\t> %s\n" , trueErrno, strerror(trueErrno));
	}
	fflush(stdout);
	fflush(stderr);
	errno = trueErrno;
}
