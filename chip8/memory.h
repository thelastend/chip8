#ifndef EM_MEMORY_CHIP_8
#define EM_MEMORY_CHIP_8

#include "emChip8Types.h"

#define MEOMRY_SIZE     4096
#define MEMORY_START    0x200


#define ADDRESS_CHAR_0  80
#define ADDRESS_CHAR_1  85
#define ADDRESS_CHAR_2  90
#define ADDRESS_CHAR_3  95
#define ADDRESS_CHAR_4  100
#define ADDRESS_CHAR_5  105
#define ADDRESS_CHAR_6  110
#define ADDRESS_CHAR_7  115
#define ADDRESS_CHAR_8  120
#define ADDRESS_CHAR_9  125
#define ADDRESS_CHAR_A  130
#define ADDRESS_CHAR_B  135
#define ADDRESS_CHAR_C  140
#define ADDRESS_CHAR_D  145
#define ADDRESS_CHAR_E  150
#define ADDRESS_CHAR_F  155


uint8 GetData(uint16 address);

void SetData(uint16 address, uint8 data);
void InitMemory(void);
int LoadRom(char* pName);
#endif /* EM_MEMORY_CHIP_8 */