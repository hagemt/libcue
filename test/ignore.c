#include "libcue.h"

#include <signal.h>

int
main(void)
{
	(void) cue_ignore(SIGTERM);
	for (;;);
	return 0;
}
