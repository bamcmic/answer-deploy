CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS=-mcpu=cortex-m23 -mthumb -O2

all:
	$(CC) $(CFLAGS) main.c -o main.elf
	$(OBJCOPY) -O binary main.elf firmware.bin