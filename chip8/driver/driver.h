#ifndef EM_DRIVER_CHIP8
#define EM_DRIVER_CHIP8

#include "emChip8Types.h"
#include "systemSettings.h"
#include <stdbool.h>

void InitWindowHW(uint16 width, uint16 hight);

void CloseWindwoHW();

void DrawWindwoHW(uint8 display[FRAME_Y][FRAME_X]);

uint16 GetKeyStateHW(void);
bool IsQuitHW(void);

void InitTimerHW(uint8 *pDelayTimer, uint8 *pSoundTimer,uint16 *pCounterCalls);
void CloseTimerHW(void);

#endif /* EM_DRIVER_CHIP8 */