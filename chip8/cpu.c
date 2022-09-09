#include "emChip8Types.h"
#include "cpu.h"
#include "gpu.h"
#include "memory.h"

volatile static uint16 stack[STACK_SIZE];
volatile static uint8 reg[MAX_REGISTER];
volatile static uint16 indexReg;
volatile static uint16 pc;



void InitCpu(void)
{
    uint8 i;
    pc = MEMORY_START;
    indexReg = 0;

    for(i = 0; i < MAX_REGISTER; i++)
        reg[i] = 0;

    for(i = 0; i < STACK_SIZE; i++)
        stack[i] = 0;
}

void execution( void )
{
    uint16 opcode = (GetData(pc) << 8 | GetData(pc+1));
    pc += 2;
    uint8 code = (opcode >> 12);

    if(opcode == 0x00E0)
    {
        GpuClearDisplay();        
    }
    else 
    {
        switch(code)
        {
            case(0x1):
                pc = opcode & 0xFFF;
                break;
            case(0x6):
            {
                uint8 i = (opcode >> 8) & 0xF;
                reg[i] = opcode & 0xFF;
                break;
            }
            case(0x7):
            {
                uint8 i = (opcode >> 8) & 0xF;
                reg[i] = reg[i] + (opcode & 0xFF);
                break;                
            }
            case(0xA):
            {
                indexReg = opcode & 0xFFF;
                break;
            }
            case(0xD):
            {
                uint8 x = (opcode >> 0x8) & 0xF;
                uint8 y = (opcode >> 0x4) & 0xF;
                uint8 n = (opcode) & 0xF;
                reg[0xF] = GpuSetPixel(reg[y], reg[x], indexReg, n);
                break;
            }
        }
    }

}