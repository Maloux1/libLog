#ifndef RECORD_H
#define RECORD_H

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>

int record_enabled [5] = {1, 1, 1, 1, 1};
void enable_record(int info, int debug, int warning, int error, int fatalerror);
void enable_record_all(int boolean);
void record(char logType, char * title, char * message, char checkErrno, char * FILE, int LINE);

#define RECORD_LOG_INFO 0 /* stdout */
#define RECORD_LOG_DEBUG 1 /* stdout */
#define RECORD_LOG_WARNING 2 /* stderr */
#define RECORD_LOG_ERROR 3 /* stderr */
#define RECORD_LOG_FATALERROR 4 /* stderr */

#define RECORD_NO_CHECK_ERRNO 0
#define RECORD_CHECK_ERRNO 1

#endif /* RECORD_H */
