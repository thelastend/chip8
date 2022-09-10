#include <stdio.h>
#include <string.h>
#include "emChip8Types.h"
#include "memory.h"

static uint8 memory[MEOMRY_SIZE];

uint8 char0[5] = {0xF0,0x90,0x90,0x90,0xF0};
uint8 char1[5] = {0x20,0x60,0x20,0x20,0x70};
uint8 char2[5] = {0xF0,0x10,0xF0,0x80,0xF0};
uint8 char3[5] = {0xF0,0x10,0xF0,0x10,0xF0};
uint8 char4[5] = {0x90,0x90,0xF0,0x10,0x10};
uint8 char5[5] = {0xF0,0x80,0xF0,0x10,0xF0};
uint8 char6[5] = {0xF0,0x80,0xF0,0x90,0xF0};
uint8 char7[5] = {0xF0,0x10,0x20,0x40,0x40};
uint8 char8[5] = {0xF0,0x90,0xF0,0x90,0xF0};
uint8 char9[5] = {0xF0,0x90,0xF0,0x10,0xF0};
uint8 charA[5] = {0xF0,0x90,0xF0,0x90,0x90};
uint8 charB[5] = {0xE0,0x90,0xE0,0x90,0xE0};
uint8 charC[5] = {0xF0,0x80,0x80,0x80,0xF0};
uint8 charD[5] = {0xE0,0x90,0x90,0x90,0xE0};
uint8 charE[5] = {0xF0,0x80,0xF0,0x80,0xF0};
uint8 charF[5] = {0xF0,0x80,0xF0,0x80,0x80};

void InitMemory()
{
    uint8 i;

    memset(memory,0, MEOMRY_SIZE);

    memcpy(&memory[ADDRESS_CHAR_0], char0,5);
    memcpy(&memory[ADDRESS_CHAR_1], char1,5);
    memcpy(&memory[ADDRESS_CHAR_2], char2,5);
    memcpy(&memory[ADDRESS_CHAR_3], char3,5);
    memcpy(&memory[ADDRESS_CHAR_4], char4,5);
    memcpy(&memory[ADDRESS_CHAR_5], char5,5);
    memcpy(&memory[ADDRESS_CHAR_6], char6,5);
    memcpy(&memory[ADDRESS_CHAR_7], char7,5);
    memcpy(&memory[ADDRESS_CHAR_8], char8,5);
    memcpy(&memory[ADDRESS_CHAR_9], char9,5);
    memcpy(&memory[ADDRESS_CHAR_A], charA,5);
    memcpy(&memory[ADDRESS_CHAR_B], charB,5);
    memcpy(&memory[ADDRESS_CHAR_C], charC,5);
    memcpy(&memory[ADDRESS_CHAR_D], charD,5);
    memcpy(&memory[ADDRESS_CHAR_E], charE,5);
    memcpy(&memory[ADDRESS_CHAR_F], charF,5);
}

uint8 GetData(uint16 address)
{
    uint8 data = 0;

    if(address < 4096)
        data = memory[address];

    return data;
}

void SetData(uint16 address, uint8 data)
{
    if(address < 4096)
        memory[address] = data;
}


int LoadRom(char* pName)
{
   int error = -1;
   FILE *fp;
   uint16 indexBank, index;
   uint16 indexAddress;
   size_t readError;
 
   fp = fopen(pName, "rb");

    if(fp != NULL)
    {
        fseek(fp, 0, SEEK_END);
        long fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        for(index = MEMORY_START; index < (fsize+MEMORY_START); index++)
        {
            int data = fgetc(fp);
            memory[index] = data;//TODO die richtige länge auslesen

            if(index >= MEOMRY_SIZE)
                break;
        }
        fclose(fp);
        error = 0;
    }


   return error;
}