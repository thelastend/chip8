#include <stdio.h>
#include <string.h>
#include "emChip8Types.h"
#include "memory.h"

static uint8 memory[MEOMRY_SIZE];

uint8 character[CHAR_ELEMENTS] = {0xF0,0x90,0x90,0x90,0xF0,  //0
                                  0x20,0x60,0x20,0x20,0x70,  //1
                                  0xF0,0x10,0xF0,0x80,0xF0,  //2
                                  0xF0,0x10,0xF0,0x10,0xF0,  //3
                                  0x90,0x90,0xF0,0x10,0x10,  //4
                                  0xF0,0x80,0xF0,0x10,0xF0,  //5
                                  0xF0,0x80,0xF0,0x90,0xF0,  //6
                                  0xF0,0x10,0x20,0x40,0x40,  //7
                                  0xF0,0x90,0xF0,0x90,0xF0,  //8
                                  0xF0,0x90,0xF0,0x10,0xF0,  //9
                                  0xF0,0x90,0xF0,0x90,0x90,  //A
                                  0xE0,0x90,0xE0,0x90,0xE0,  //B
                                  0xF0,0x80,0x80,0x80,0xF0,  //C
                                  0xE0,0x90,0x90,0x90,0xE0,  //D
                                  0xF0,0x80,0xF0,0x80,0xF0,  //E
                                  0xF0,0x80,0xF0,0x80,0x80}; //F

void InitMemory()
{
    memset(memory,0, MEOMRY_SIZE);
    memcpy(&memory[ADDRESS_CHAR_0], character, sizeof(character));
}

uint8 GetData(uint16 address)
{
    uint8 data = 0;

    if(address < MEOMRY_SIZE)
        data = memory[address];

    return data;
}

void SetData(uint16 address, uint8 data)
{
    if(address < MEOMRY_SIZE)
        memory[address] = data;
}


int LoadRom(char* pName)
{
   int error = INVALID_PARAM;
   FILE *fp;
   uint16 index;

   fp = fopen(pName, "rb");

   if (fp != NULL) 
   {
     fseek(fp, 0, SEEK_END);
     long fsize = ftell(fp);
     fseek(fp, 0, SEEK_SET);

     for (index = MEMORY_START; index < (fsize + MEMORY_START); index++) 
     {
       int data = fgetc(fp);
       memory[index] = data;

       if (index >= MEOMRY_SIZE)
         break;
     }

     fclose(fp);
     error = SUCCESS;
   }

   return error;
}