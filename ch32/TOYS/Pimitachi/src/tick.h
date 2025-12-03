
// ****************************************************************************
//
//                                Game Tick
//
// ****************************************************************************

#ifndef _TICK_H
#define _TICK_H

#ifdef __cplusplus
extern "C" {
#endif

// shift pet state by one tick (1 tick = 8.2 seconds, total about 10450 ticks per day)
// sleep ... pet is sleeping (True=called from IWDG reset, False=called from main loop)
// - Before calling from the main loop, call IWDG_Reload() to prevent RAM data inconsistency.
void PetTick(Bool sleep);

#ifdef __cplusplus
}
#endif

#endif // _TICK_H
