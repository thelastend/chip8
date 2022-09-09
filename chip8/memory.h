#ifndef EM_MEMORY_CHIP_8
#define EM_MEMORY_CHIP_8

#include "emChip8Types.h"

#define MEOMRY_SIZE     4096
#define MEMORY_START    0x200


uint8 GetData(uint16 address);

void SetData(uint16 address, uint8 data);

int LoadRom(char* pName);
#endif /* EM_MEMORY_CHIP_8 */