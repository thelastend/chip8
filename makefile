# Toolchain
NAME = emChip8
CC   = gcc
RM   = rm -rf
SRC  = $(wildcard ./chip8/*.c)
SRC  += $(wildcard ./chip8/driver/*.c)
SRC  += $(wildcard ./main.c)


INC = -I./chip8/driver/SDL2/include
INC += -I./chip8/driver
INC += -I./chip8

LIB = -L./chip8/driver/SDL2/lib/x86
LIB += -lmingw32
LIB += -lSDL2main
LIB += -lSDL2test
LIB += -lSDL2filler
LIB += -lSDL2

CFLAGS =  -Wall --pedantic -O3 -g
CFLAGS += $(INC)
CFLAGS += -std=c18
OBJS   = $(SRC:.c=.o)

all: $(OBJS) $(NAME)

%.o: %.c
	$(CC) $(SRC) $(INC) $(CFLAGS) $(LIB) -o $(NAME)

clean:
	$(RM) $(OBJS) $(NAME) core *~
