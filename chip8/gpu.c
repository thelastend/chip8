#include <stdio.h>
#include "emChip8Types.h"
#include "gpu.h"
#include "memory.h"
#include "driver.h"
#include "systemSettings.h"

uint8 display[FRAME_Y][FRAME_X];

bool drawScreen = true;

void GpuClearDisplay()
{
    uint8 y, x;
    
    for(y = 0; y < FRAME_Y; y++)
    {
        for(x = 0; x < FRAME_X; x++)
        {
            display[y][x] = 0;
        }
    }
    drawScreen = true;
}

uint8 GpuSetPixel(uint8 y, uint8 x, uint16 address, uint8 nBytes)
{
    uint8 vf = 0;
    uint8 i, setY, setX;

    x = x % FRAME_X;
    y = y % FRAME_Y;

    for(i = 0; i < nBytes; i++)
    {
        setY = y+i;
        uint8 buffer = GetData(address+i);

        for(setX = 0; setX < 0x8; setX++)
        {
            uint8 pixel = (buffer >> (7-setX)) & 1;
            if(pixel)
            {
                if(display[setY][setX+x] == 1)
                    vf = 1;
                display[setY][setX+x] ^= pixel;
            }
        }
    }
    drawScreen = true;
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
    if(drawScreen)
    {
        DrawWindwoHW(display);
        drawScreen = false;
    }
}
