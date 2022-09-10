#include "timer.h"
#include "driver.h"

uint8 delayTimer = 0;
uint8 soundTimer = 0;

void InitTimer(uint16 *pCounterCalls)
{
    InitTimerHW(&delayTimer, &soundTimer, pCounterCalls); 
}

void SetDelayTimer(uint8 time)
{
    delayTimer = time;
}

void SetSoundTimer(uint8 time)
{
    soundTimer = time;
}


uint8 GetDelayTimer()
{
    return delayTimer;
}

uint8 GetSoundTimer()
{
    return soundTimer;
}

void CloseTimer()
{
    CloseTimerHW();
}