#include "emChip8Types.h"
#include "cpu.h"
#include "gpu.h"
#include "memory.h"
#include "keypad.h"
#include "timer.h"
#include <stdbool.h>

uint16 counterCalls = 0;

int  main(int argc, char ** agrv)
{
    int error = INVALID_PARAM;
    uint8 run = 1;

    if(argc > 1)
    {
        InitCpu();
        InitMemory();
        GpuInitScreen();
        InitTimer(&counterCalls);
        error = LoadRom(agrv[1]);
        if(error == SUCCESS)
        {
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
    }

    return error;
}