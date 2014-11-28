#include "libcue.h"

#define QUOTE(X) #X
#define STRING(X) QUOTE(X)
#define WHERE ("failed" " @ " __FILE__ ":" STRING(__LINE__))
#define SIGTEST (15)
#define SIGTIME (500)
#define SIGSYMB "/-\\|"

#define _POSIX_C_SOURCE 201411L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, cstring argv[])
{
	int signum, e, i = 0;

	if ((e = cue_on(SIGTEST))) {
		(void) fprintf(stderr, "[%s] %s(%d) = %d %s (%d: %s)\n", "FATAL",
				"cue_on", SIGTEST, e, WHERE, errno, strerror(errno));
		return EXIT_FAILURE;
	}

	for (;;) {
		if ((signum = cue_happened(SIGTEST))) {
			(void) fprintf(stdout, "[INFO] caught signal %d (%s)\n",
					signum, strsignal(signum));
			break;
		} else {
			(void) fprintf(stderr, "%c [TRACE] sleeping (%08dx%dms)\r",
					SIGSYMB[(i / SIGTIME) % (sizeof(SIGSYMB) - 1)], i, SIGTIME);
		}
		(void) usleep((useconds_t) SIGTIME);
		if (!i++ && (e = cue_signal(SIGTEST))) {
			(void) fprintf(stderr, "[%s] %s(%d) = %d %s (%d: %s)\n", "WARNING",
					"cue_signal", SIGTEST, e, WHERE, errno, strerror(errno));
		}
	}

	if ((e = cue_off(SIGTEST))) {
		(void) fprintf(stderr, "[%s] %s(%d) = %d %s (%d: %s)\n", "ERROR",
				"cue_off", SIGTEST, e, WHERE, errno, strerror(errno));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
