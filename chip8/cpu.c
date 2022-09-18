#include "emChip8Types.h"
#include "cpu.h"
#include "gpu.h"
#include "memory.h"
#include "keypad.h"
#include "timer.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GET_DATA(d,s,m) ((d >> s) & m)
#define BIT_4_MASK      (0xF)
#define BIT_8_MASK      (0xFF)
#define BIT_12_MASK     (0xFFF)

#define SHIFT_0_BITS    (0x0)
#define SHIFT_4_BITS    (0x4)
#define SHIFT_8_BITS    (0x8)
#define SHIFT_12_BITS   (0xC)

static uint16 stack[STACK_SIZE];
static uint8 reg[MAX_REGISTER];
static uint16 indexReg;
static uint16 pc;
static uint8 sp;

static const uint8 charAddr[16] = { ADDRESS_CHAR_0, ADDRESS_CHAR_1, ADDRESS_CHAR_2, ADDRESS_CHAR_3,
                                    ADDRESS_CHAR_4, ADDRESS_CHAR_5, ADDRESS_CHAR_6, ADDRESS_CHAR_7,
                                    ADDRESS_CHAR_8, ADDRESS_CHAR_9, ADDRESS_CHAR_A, ADDRESS_CHAR_B,
                                    ADDRESS_CHAR_C, ADDRESS_CHAR_D, ADDRESS_CHAR_E, ADDRESS_CHAR_F };



void InitCpu(void)
{
    time_t t;
    pc = MEMORY_START;
    indexReg = 0;
    sp = 0;
    memset(reg,0, MAX_REGISTER);
    memset(stack,0, sizeof(stack));

    /* init rng*/
    srand((unsigned) time(&t));
}


static void Jump(uint16 opCode)
{
    pc = GET_DATA(opCode,SHIFT_0_BITS,BIT_12_MASK);  
}

static void CompareSkip(uint16 first, uint16 second, bool isEquel)
{
    if(isEquel == true)
    {
        if(first == second)
            pc += 2;
    }
    else
    {
        if(first != second)
            pc += 2;
    }
}

static void Set(uint16 opCode)
{
    uint8 x = GET_DATA(opCode,SHIFT_8_BITS,BIT_4_MASK);
    uint8 y = GET_DATA(opCode,SHIFT_4_BITS,BIT_4_MASK);
    uint8 i = GET_DATA(opCode,SHIFT_0_BITS,BIT_4_MASK);

    switch(i)
    {
        case(0x0):
        {
            reg[x] = reg[y];
            break;
        }
        case(0x1):
        {
            reg[x] |= reg[y];
            break;
        }
        case(0x2):
        {
            reg[x] &= reg[y];
            break;
        }
        case(0x3):
        {
            reg[x] ^= reg[y];
            break;
        }
        case(0x4):
        {
            uint16 result = reg[x] + reg[y];
            if(result > 255)
                reg[0xF] = 1;
            else
                reg[0xF] = 0;
            reg[x] = result & 0xFF;
            break;
        }
        case(0x5):
        {
            if(reg[x] > reg[y])
                reg[0xF] = 1;
            else
                reg[0xF] = 0;
            reg[x] = reg[x] - reg[y];
            break;
        }
        case(0x6):
        {
            if((reg[x] & 0x1) == 0x1)
                reg[0xf] = 1;
            else
                reg[0xf] = 0;
            reg[x] = reg[x] >> 1;
            break;
        }
        case(0x7):
        {
            if(reg[y] > reg[x])
                reg[0xF] = 1;
            else
                reg[0xF] = 0;
            reg[x] = reg[y] - reg[x];
            break;
        }
        case(0xE):
        {
            if((reg[x] & 0x80) == 0x80)
                reg[0xf] = 1;
            else
                reg[0xf] = 0;
            reg[x] = reg[x] << 1;
            break;
        }
        default:
            break;
    }

}


static void Fx(uint16 opCode)
{
    uint8 x = GET_DATA(opCode,SHIFT_8_BITS,BIT_4_MASK);
    uint8 code = GET_DATA(opCode,SHIFT_0_BITS,BIT_8_MASK);

    switch(code)
    {
        case(0x7):
        {
            reg[x] = GetDelayTimer();
            break;
        }
        case(0xA):
        {
            uint8 i;
            bool pressed = false;
            for(i = 0; i < KEY_MAX;i++)
            {
                if(KeyPadPressed(i) == true)
                {
                    reg[x] = i;
                    pressed = true;
                    break;
                }
            }
            if(false == pressed)
                pc -= 2;
            break;
        }
        case(0x15):
        {
            SetDelayTimer(reg[x]);
            break;
        }
        case(0x18):
        {
            SetSoundTimer(reg[x]);
            break;
        }
        case(0x1E):
        {
            indexReg = indexReg + reg[x];
            break;
        }
        case(0x29):
        {
            indexReg = charAddr[reg[x]];
            break;
        }
        case(0x33):
        {
            SetData(indexReg, reg[x]/100);
            SetData(indexReg+1, ((reg[x]/10)%10));
            SetData(indexReg+2, reg[x]%10);
            break;
        }
        case(0x55): // LD [I], Vx
        {// new index behavior index will not be changed
            uint8 i;
            for(i = 0; i < (x+1); i++)
            {
               SetData(indexReg +i, reg[i]); 
            }
            break;
        }
        case(0x65): // LD Vx, [I]
        {// new index behavior index will not be changed
            uint8 i;
            for(i = 0; i < (x+1); i++)
            {
               reg[i] = GetData(indexReg +i);
            }
            break;
        }
        default:
            break;        
    }
}


void Execution( void )
{
    uint16 opCode = (GetData(pc) << SHIFT_8_BITS | GetData(pc+1));
    pc += 2;
    uint8 code = (opCode >> SHIFT_12_BITS);
    uint8 x, y;
    x = GET_DATA(opCode,SHIFT_8_BITS,BIT_4_MASK);
    y = GET_DATA(opCode,SHIFT_4_BITS,BIT_4_MASK);
    if(opCode == 0x00E0) //clear dispaly
    {
        GpuClearDisplay();        
    }
    else if(opCode == 0x00EE) // return subroutine
    {
        pc = stack[sp];
        sp--;
    }
    else 
    {
        switch(code)
        {
            case(0x1): //jp addr
            {
                Jump(opCode);
                break;
            }
            case(0x2):  //call addr
            {
                sp++;
                stack[sp] = pc;
                Jump(opCode);
                break;
            }
            case(0x3):  //cmp vx, byte skip
            {
                CompareSkip(reg[x], GET_DATA(opCode,SHIFT_0_BITS,BIT_8_MASK), true);
                break;
            }
            case(0x4):  //if not cmp vx, byte skip
            {
                CompareSkip(reg[x], GET_DATA(opCode,SHIFT_0_BITS,BIT_8_MASK), false);
                break;
            }
            case(0x5):  //if cmp vx, vy skip
                CompareSkip(reg[x], reg[y], true);
                break;
            case(0x6):  // ld vx, byte
            {
                reg[x] = GET_DATA(opCode,SHIFT_0_BITS,BIT_8_MASK);
                break;
            }
            case(0x7):  // add vx, byte
            {
                reg[x] = reg[x] + GET_DATA(opCode,SHIFT_0_BITS,BIT_8_MASK);
                break;                
            }
            case(0x8):  // set, add, sub, shift r and l
            {
                Set(opCode);
                break;                
            }
            case(0x9):  // if not cmp vx, vy skip
            {
                CompareSkip(reg[x], reg[y], false);
                break;                
            }
            case(0xA):  // ld i, addr
            {
                indexReg = GET_DATA(opCode,SHIFT_0_BITS,BIT_12_MASK);
                break;
            }
            case(0xB):  // jp v0, addr
            {
                pc = GET_DATA(opCode,SHIFT_0_BITS,BIT_12_MASK) + reg[0];
                break;
            }
            case(0xC):  // RND Vx, byte
            {
                reg[x] = (rand() % 256) + GET_DATA(opCode,SHIFT_0_BITS,BIT_8_MASK);;
                break;
            }
            case(0xD):
            {
                uint8 n = GET_DATA(opCode,SHIFT_0_BITS,BIT_4_MASK);
                reg[0xF] = GpuSetPixel(reg[y], reg[x], indexReg, n);
                break;
            }
            case(0xE):  //skip if key is press or not press
            {
                uint8 type = GET_DATA(opCode,SHIFT_0_BITS,BIT_8_MASK);
                if(((KeyPadPressed(reg[x]) == true) && (type == 0x9E)) ||  //key is pressed
                   ((KeyPadPressed(reg[x]) == false) && (type == 0xA1)))   //key is not pressed
                {
                    pc += 2;
                }
                break;
            }
            case(0xF):  //LD, ADD
            {
                Fx(opCode);
                break;
            }

        }
    }

}