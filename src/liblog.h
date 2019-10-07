#ifndef LIBLOG_H
#define LIBLOG_H

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>

void libLog(char logType, char * title, char * message, char checkErrno, char * FILE, int LINE);

#define LIBLOG_LOG_INFO 1 /* stdout */
#define LIBLOG_LOG_DEBUG 2 /* stdout */
#define LIBLOG_LOG_WARNING 3 /* stderr */
#define LIBLOG_LOG_ERROR 4 /* stderr */
#define LIBLOG_LOG_FATALERROR 5 /* stderr */

#define LIBLOG_NO_CHECK_ERRNO 0
#define LIBLOG_CHECK_ERRNO 1

#endif /* LIBLOG_H */
