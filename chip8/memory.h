#ifndef EM_MEMORY_CHIP_8
#define EM_MEMORY_CHIP_8

#include "emChip8Types.h"

#define MEOMRY_SIZE     4096U
#define MEMORY_START    0x200U

#define ADDRESS_CHAR_0  80U
#define ADDRESS_CHAR_1  85U
#define ADDRESS_CHAR_2  90U
#define ADDRESS_CHAR_3  95U
#define ADDRESS_CHAR_4  100U
#define ADDRESS_CHAR_5  105U
#define ADDRESS_CHAR_6  110U
#define ADDRESS_CHAR_7  115U
#define ADDRESS_CHAR_8  120U
#define ADDRESS_CHAR_9  125U
#define ADDRESS_CHAR_A  130U
#define ADDRESS_CHAR_B  135U
#define ADDRESS_CHAR_C  140U
#define ADDRESS_CHAR_D  145U
#define ADDRESS_CHAR_E  150U
#define ADDRESS_CHAR_F  155U

#define CHAR_ELEMENTS   80U
uint8 GetData(uint16 address);

void SetData(uint16 address, uint8 data);
void InitMemory(void);
int LoadRom(char* pName);
#endif /* EM_MEMORY_CHIP_8 */