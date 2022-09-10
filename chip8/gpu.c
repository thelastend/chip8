#include <stdio.h>
#include "emChip8Types.h"
#include "gpu.h"
#include "memory.h"
#include "driver.h"
#include "systemSettings.h"

uint8 display[FRAME_Y][FRAME_X];

void GpuClearDisplay()
{
    uint8 y, x;
    
    for(y = 0; y < FRAME_Y; y++)
    {
        for(x = 0; x < FRAME_Y; x++)
        {
            display[y][x] = 0;
        }
    }
}

uint8 GpuSetPixel(uint8 y, uint8 x, uint16 address, uint8 nBytes)
{
    uint8 vf = 0;
    uint8 buffer;
    uint8 i, setY, setX;
    uint8 oldPixel;

    x = x % FRAME_X;
    y = y % FRAME_Y;

    for(i = 0; i < nBytes; i++)
    {
        setY = y+i;
        buffer = GetData(address+i);

        for(setX = 0; setX < 0x8; setX++)
        {
            if((setX+x) >= FRAME_X)
                break;
            oldPixel = display[setY][setX+x];
            display[setY][setX+x] ^= ((buffer >> (7-setX)) & 1);
            if((oldPixel == 1) && (display[setY][setX+x] == 0))
                vf = 1;
        }
    }
    return vf;
}

void GpuCloseScreen()
{
    CloseWindwoHW();
}

void GpuInitScreen(void)
{
   	InitWindowHW(WINDOW_WIDTH, WINDOW_HIGHT);
}

void GpuDrawScreen(void)
{
    DrawWindwoHW(display);
}
