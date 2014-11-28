#include "libcue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void
after(int signum)
{
	(void) printf("[CUE] reports that a signal was caught (%d: %s)\n",
			signum, strsignal(signum));
}

static void
perform(FILE *fp, int signum)
{
	(void) fprintf(fp, "[CUE] waiting for signal? (%d: %s)\r",
			signum, strsignal(signum));
}

#define SIGNUM (15)

int
main(void)
{
	(void) cue_on(SIGNUM);

	CUE_FOREVER {
		perform(stderr, SIGNUM);
	} CUE_UNTIL_SIGNAL_THEN(after, SIGNUM);

	(void) cue_reset();

	CUE_DO(perform, stderr, SIGNUM);
	CUE_UNTIL_SIGNAL_THEN(after, SIGNUM);

	return EXIT_SUCCESS;
}
