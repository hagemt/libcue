#ifndef __LIBCUE_MACRO_H__
#define __LIBCUE_MACRO_H__

#include "cue.h"

#define CUE_FOREVER for (;;) {

#define CUE_DO(WHAT, ...) CUE_FOREVER WHAT(__VA_ARGS__)

#define CUE_UNTIL_SIGNAL_THEN(WHAT, ...) \
	if(cue_happened()) { WHAT(__VA_ARGS__); break; } \
}

#endif /* __LIBCUE_MACRO_H__ */
