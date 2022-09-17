#include "driver.h"
#include "systemSettings.h"
#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include "./SDL2/include/SDL.h"

SDL_Event event;
SDL_Renderer *pRenderer;
SDL_Window *pWindow;
SDL_Texture* pTexture;
SDL_TimerID timerId;

uint8 *pDTimer;
uint8 *pSTimer;


uint16 *pFps;
uint8 counter = 0;

static uint32 SetTimer(uint32 interval, void *param);

void InitWindowHW(uint16 width, uint16 hight)
{
   	SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, hight, 0, &pWindow, &pRenderer); 

    pTexture =  SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STATIC, WINDOW_WIDTH, WINDOW_HIGHT);
}

void CloseWindwoHW()
{
    SDL_DestroyTexture(pTexture);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();    
}


void DrawWindwoHW(uint8 display[FRAME_Y][FRAME_X])
{
    uint16 y, x, setY, setX;
    uint8 pixelR, pixelG, pixelB;
    uint32 screen[WINDOW_HIGHT * WINDOW_WIDTH];
    setY = 0;

    for (y = 0; y < (WINDOW_HIGHT ); y++)
    {
        if(((y % SCAL) == 0x00) && (setY < (FRAME_Y-1)) && (y > 0))
            setY++;
        setX = 0;
        for (x = 0; x < (WINDOW_WIDTH); x++)
        {

            if(((x % SCAL) == 0x00) && (setX < (FRAME_X-1)) && (x > 0))
                setX++;

            if(display[setY][setX] == 1)
            {
                screen[(y*WINDOW_WIDTH)+x] = 0xFFFFFFFF;
            }
            else
            {
                screen[(y*WINDOW_WIDTH)+x] = 0xFF000000;               
            }
        }
    }
    SDL_UpdateTexture(pTexture, NULL, screen,
                      WINDOW_WIDTH * sizeof(uint32_t));
    SDL_RenderCopy(pRenderer, pTexture, NULL, NULL);
    SDL_RenderPresent(pRenderer);
}

uint16 GetKeyStateHW(void)
{
    uint16 status;
    const uint8_t* state = SDL_GetKeyboardState(NULL);
    status = ((state[SDL_SCANCODE_0] & 0x1) |
              ((state[SDL_SCANCODE_1] & 0x1) << 1) |
              ((state[SDL_SCANCODE_2] & 0x1) << 2) |
              ((state[SDL_SCANCODE_3] & 0x1) << 3) |
              ((state[SDL_SCANCODE_4] & 0x1) << 4) |
              ((state[SDL_SCANCODE_5] & 0x1) << 5) |
              ((state[SDL_SCANCODE_6] & 0x1) << 6) |
              ((state[SDL_SCANCODE_7] & 0x1) << 7) |
              ((state[SDL_SCANCODE_8] & 0x1) << 8) |
              ((state[SDL_SCANCODE_9] & 0x1) << 9) |
              ((state[SDL_SCANCODE_A] & 0x1) << 10) |
              ((state[SDL_SCANCODE_B] & 0x1) << 11) |
              ((state[SDL_SCANCODE_C] & 0x1) << 12) |
              ((state[SDL_SCANCODE_D] & 0x1) << 13) |
              ((state[SDL_SCANCODE_E] & 0x1) << 14) |
              ((state[SDL_SCANCODE_F] & 0x1) << 15) );

    return status;
}

bool IsQuitHW(void)
{
    bool quit = false;
    while( SDL_PollEvent( &event ) )
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
            break;
        }
    }

    return quit;
}

void InitTimerHW(uint8 *pDelayTimer, uint8 *pSoundTimer, uint16 *pCounterCalls)
{
    pDTimer = pDelayTimer;
    pSTimer = pSoundTimer;
    pFps = pCounterCalls;
    SDL_Init(SDL_INIT_TIMER);
    timerId = SDL_AddTimer(10,SetTimer,NULL);
}

void CloseTimerHW(void)
{
    SDL_RemoveTimer(timerId);
}


static uint32 SetTimer(uint32 interval, void *param)
{
    uint8 delay = *pDTimer;
    uint8 sound = *pSTimer;
    if(delay > 0)
    {
        delay--;
        *pDTimer = delay;
    }

    if(sound > 0)
    {
        sound--;
        *pSTimer = sound;
    }
    else
    {

    }
    counter++;
    if(counter == 60)
    {
        counter = 0;
    }
    *pFps = 1;

    return interval;
}
