#include <stdio.h>
#include <string.h>
#include "emChip8Types.h"
#include "memory.h"

volatile static uint8 memory[MEOMRY_SIZE];


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