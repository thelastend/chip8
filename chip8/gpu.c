#include <stdio.h>
#include "emChip8Types.h"
#include "gpu.h"
#include "memory.h"

#define SDL_MAIN_HANDLED
#include "../external/SDL2/include/SDL.h"

SDL_Event event;
SDL_Renderer *renderer;
SDL_Window *window;

volatile uint8 display[FRAME_Y][FRAME_X];

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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GpuInitScreen(void)
{
   	SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HIGHT, 0, &window, &renderer); 
}

void GpuDrawScreen(void)
{
    uint16 y, x, setY, setX;
    uint8 pixelR, pixelG, pixelB;

    setY = 0;

    SDL_RenderClear(renderer);
    for (y = 0; y < (WINDOW_HIGHT ); y++)
    {
        if(((y % SCAL) == 0x00) && (setY < (FRAME_Y-1)))
            setY++;
        setX = 0;
        for (x = 0; x < (WINDOW_WIDTH); x++)
        {

            if(((x % SCAL) == 0x00) && (setX < (FRAME_X-1)))
                setX++;

            if(display[setY][setX] == 1)
            {
                pixelR = 0xFF; 
                pixelG = 0xFF; 
                pixelB = 0xFF;
            }
            else
            {
                pixelR = 0x0; 
                pixelG = 0x0; 
                pixelB = 0x0;                
            }

            SDL_SetRenderDrawColor(renderer, pixelR, pixelG, pixelB, SDL_ALPHA_OPAQUE);

            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    SDL_RenderPresent(renderer);

}

uint8 UpdatedKeyPresses()
{
	uint8_t open = 1;
	uint8_t press;
	uint8_t keyIndex;

    while( SDL_PollEvent( &event ) )
    {

        if (event.type == SDL_QUIT)
        {
            open = 0;
            break;
        }

    }
	return open;
}
