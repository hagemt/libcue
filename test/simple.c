#include "libcue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIGNUM (15)

int
main(int argc, cstring argv[])
{
	(void) cue_on(SIGNUM);
	for (;;) {
		(void) fprintf(stderr, "\r[CUE] is waiting for a signal... ");
		if (cue_happened()) {
			(void) printf("\n[CUE] reports that a signal was caught (%d: %s)\n",
					SIGNUM, strsignal(SIGNUM));
			break;
		}
	}
	(void) fflush(stdout);
	return EXIT_SUCCESS;
}
