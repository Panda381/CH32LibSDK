
// ****************************************************************************
//
//                                 Pimitachi
//
// ****************************************************************************

#ifndef _MAIN_H
#define _MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

// wait [ms] with IWDT (must be less than 8 seconds)
void WaitMsIWDT(int ms);

// loop idle (returns True if was sleeping)
Bool LoopIdle(void);

#ifdef __cplusplus
}
#endif

#endif // _MAIN_H
