
// ****************************************************************************
//
//                               Repaint
//
// ****************************************************************************

#ifndef _REPAIN_H
#define _REPAINT_H

#ifdef __cplusplus
extern "C" {
#endif

// repaint one game state
void RepaintState1(int inx, int x, int y);

// repaint game state (does not update screen)
void RepaintState(void);

// repaint one menu
void RepaintMenu1(int inx, int x, int y);

// repaint menu
void RepaintMenu(void);

// repaint game screen
void RepaintScreen(void);

#ifdef __cplusplus
}
#endif

#endif // _REPAINT_H
