#include "emChip8Types.h"
#include "cpu.h"
#include "gpu.h"
#include "memory.h"
#include "keypad.h"
#include "timer.h"
#include <stdbool.h>

uint16 counterCalls = 0;

void  main(void)
{
    uint8 run = 1;
    InitCpu();
    InitMemory();
    GpuInitScreen();
    InitTimer(&counterCalls);
    //LoadRom("IBM_Logo.ch8");
    LoadRom("Blitz.ch8");

    while(run)
    {
        if(counterCalls > 0)
        {
            Execution();
            GpuDrawScreen();
            counterCalls = 0;
        }

        if(UpdatedQuitState() == true)
            run = 0;
    }

    CloseTimer();
    GpuCloseScreen();
}