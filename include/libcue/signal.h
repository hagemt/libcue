#ifndef __LIBCUE_SIGNAL_H__
#define __LIBCUE_SIGNAL_H__

#ifdef __cplusplus
extern "C" {
#endif /* if C++ */

extern int
cue_happened(int);

extern int
cue_off(int);

extern int
cue_on(int);

extern int
cue_signal(int);

#ifdef __cplusplus
} /* extern "C" */
#endif /* if C++ */

#endif /* __LIBCUE_SIGNAL_H__ */
