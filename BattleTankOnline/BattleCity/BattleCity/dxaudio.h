// Beginning Game Programming
// Chapter 9
// dxaudio.h - DirectSound framework header file


#ifndef _DXAUDIO_H
#define _DXAUDIO_H

#include "dsutil.h"

//primary DirectSound object



extern CSoundManager *dsound;
//function prototypes
int InitDirectXSound(HWND);
CSound *LoadSound(LPTSTR);
void PlaySound(CSound *);
void LoopSound(CSound *);
void StopSound(CSound *);

#endif

