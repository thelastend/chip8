#ifndef EM_GPU_CHIP_8
#define EM_GPU_CHIP_8

void GpuClearDisplay();

uint8 GpuSetPixel(uint8 y, uint8 x, uint16 address, uint8 nBytes);

void GpuDrawScreen(void);

void GpuInitScreen(void);

void GpuCloseScreen(void);

#endif  /* EM_GPU_CHIP_8 */