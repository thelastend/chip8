#ifndef EM_TIMER_CHIP8
#define EM_TIMER_CHIP8
#include "emChip8Types.h"

void InitTimer(uint16 *pCounterCalls);
void CloseTimer(void);
void UpdateTimers(void);


uint8 GetDelayTimer(void);
uint8 GetSoundTimer(void);
void SetDelayTimer(uint8 time);

void SetSoundTimer(uint8 time);
#endif /* EM_TIMER_CHIP8 */