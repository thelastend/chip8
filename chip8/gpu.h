#ifndef EM_GPU_CHIP_8
#define EM_GPU_CHIP_8

#define FRAME_Y     32
#define FRAME_X     64

#define SCAL        8

#define WINDOW_WIDTH    (FRAME_X*SCAL)
#define WINDOW_HIGHT    (FRAME_Y*SCAL)

void GpuClearDisplay();


uint8 GpuSetPixel(uint8 y, uint8 x, uint16 address, uint8 nBytes);

void GpuDrawScreen(void);

void GpuInitScreen(void);

void GpuCloseScreen(void);


uint8 UpdatedKeyPresses(void);
#endif  /* EM_GPU_CHIP_8 */