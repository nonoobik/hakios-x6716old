CC = aarch64-linux-gnu-gcc
OBJCOPY = aarch64-linux-gnu-objcopy
CFLAGS = -ffreestanding -nostdlib -nostartfiles -O2 -Wall -Iinclude

all: Image

Image: src/start.S src/main.c linker.ld
	$(CC) $(CFLAGS) -T linker.ld src/start.S src/main.c -o loader.elf
	$(OBJCOPY) -O binary -R .note -R .comment -S loader.elf Image

clean:
	rm -f loader.elf Image
