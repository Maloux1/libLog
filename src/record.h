#ifndef RECORD_H
#define RECORD_H

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>

void record(char logType, char * title, char * message, char checkErrno, char * FILE, int LINE);

#define RECORD_LOG_INFO 1 /* stdout */
#define RECORD_LOG_DEBUG 2 /* stdout */
#define RECORD_LOG_WARNING 3 /* stderr */
#define RECORD_LOG_ERROR 4 /* stderr */
#define RECORD_LOG_FATALERROR 5 /* stderr */

#define RECORD_NO_CHECK_ERRNO 0
#define RECORD_CHECK_ERRNO 1

#endif /* RECORD_H */
