#ifndef EM_CPU_CHIP_8
#define EM_CPU_CHIP_8
#include "stdint.h"

#define MAX_REGISTER    16
#define STACK_SIZE      16

typedef void (*instructionCalls)(void);

void InitCpu(void);

void execution( void );

#endif /* EM_CPU_CHIP_8 */
