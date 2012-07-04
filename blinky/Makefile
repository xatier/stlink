CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-ld -v
CP      = arm-none-eabi-objcopy
OD      = arm-none-eabi-objdump
  
CFLAGS  = -I./ -c -fno-common -Os -mcpu=cortex-m3 -mthumb -g
LFLAGS  = -Tstm32.ld -nostartfiles
CPFLAGS = -Obinary
ODFLAGS = -S

all: test

clean:
	-rm -f blinky.lst blinky.o blinky.none-eabi blinky.lst blinky.bin

test: blinky.none-eabi
	@ echo "...copying"
	$(CP) $(CPFLAGS) blinky.none-eabi blinky.bin
	$(OD) $(ODFLAGS) blinky.none-eabi > blinky.lst

blinky.none-eabi: blinky.o stm32.ld 
	@ echo "..linking"
	$(LD) $(LFLAGS) -o blinky.none-eabi blinky.o    

blinky.o: blinky.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) blinky.c


