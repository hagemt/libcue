#ifndef __LIBCUE_SIGNAL_H__
#define __LIBCUE_SIGNAL_H__

#ifdef __cplusplus
extern "C" {
#endif /* if C++ */

extern int
cue_default(int);

extern int
cue_happened(void);

extern int
cue_ignore(int);

extern int
cue_on(int);

extern int
cue_raise(int);

extern int
cue_reset(void);

#ifdef __cplusplus
} /* extern "C" */
#endif /* if C++ */

#endif /* __LIBCUE_SIGNAL_H__ */
