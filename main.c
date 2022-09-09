#include "emChip8Types.h"
#include "cpu.h"
#include "gpu.h"
#include "memory.h"


void  main(void)
{
    uint8 run = 1;
    InitCpu();
    GpuInitScreen();
    LoadRom("IBM_Logo.ch8");

    while(run)
    {
       execution();

       GpuDrawScreen();

        run = UpdatedKeyPresses();
    }


    GpuCloseScreen();
}