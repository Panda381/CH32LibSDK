
// ****************************************************************************
//
//                                Sleep
//
// ****************************************************************************

#ifndef _SLEEP_H
#define _SLEEP_H

#ifdef __cplusplus
extern "C" {
#endif

// repaint going to sleep
void RepaintSleep(void);

// repaint wake up
void RepaintWakeup(void);

// watchdog init
void IWDGInit();

// go sleep
void GoSleep(void);

#ifdef __cplusplus
}
#endif

#endif // _SLEEP_H
