#include "libcue.h"

#include <assert.h>
#include <signal.h>
#include <unistd.h>

static volatile sig_atomic_t
__canary__ = 0;

static void
__handle__(int signum)
{
	assert(signum);
	(void) sleep(1);
	__canary__ = 1;
}

static int
__signal__(int, void (*)(int));

/***/

int
cue_on(int signum)
{
	assert(0 < signum && signum < NSIG);
	return __signal__(signum, &__handle__);
}

int
cue_happened(int signum)
{
	assert(0 < signum && signum < NSIG);
	return (__canary__) ? signum : 0;
}

int
cue_signal(int signum)
{
	assert(0 < signum && signum < NSIG);
	return raise(signum);
}

int
cue_off(int signum)
{
	assert(0 < signum && signum < NSIG);
	return __signal__(signum, SIG_DFL);
}

/***/

#include <string.h>

static /* volatile */ struct sigaction __action__;

static int
__signal__(int signum, void (*handler)(int))
{
	assert(0 < signum && signum < NSIG);
	assert(handler || handler == SIG_DFL || handler == SIG_IGN);
	(void) memset(&__action__, 0x00, sizeof(struct sigaction));
	__action__.sa_handler = handler;
	return sigaction(signum, &__action__, NULL);
}
