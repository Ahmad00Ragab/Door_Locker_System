TARGET = HMI_ECU
MCU = atmega328p
F_CPU = 8000000UL
CC = avr-gcc
CFLAGS = -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Iinclude
OBJCOPY = avr-objcopy
OBJCOPY_FLAGS = -O ihex -R .eeprom
SRCS = $(wildcard src/*.c) $(wildcard src/*/*.c)
OBJS = $(SRCS:src/%.c=build/%.o)

.PHONY: all clean flash

all: build/$(TARGET).hex

build/$(TARGET).hex: build/$(TARGET).elf
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

build/$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build

flash: build/$(TARGET).hex
	avrdude -c PROGRAMMER_TYPE -p MCU_TYPE -P PORT -U flash:w:$<:i


