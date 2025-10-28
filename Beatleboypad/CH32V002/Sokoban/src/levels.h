
// ****************************************************************************
//
//                                 Game levels
//
// ****************************************************************************

#ifndef _LEVELS_H
#define _LEVELS_H

#ifdef __cplusplus
extern "C" {
#endif

// selected level
extern int Level;		// current level 0..
extern const char* LevDef;	// current level definition
extern const char* LevSolve;	// current level solve

extern const char* const Levels[];

// number of levels
extern const int LevNum;

#ifdef __cplusplus
}
#endif

#endif // _LEVELS_H
