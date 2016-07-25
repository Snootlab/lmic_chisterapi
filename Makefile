TARGET=OTAA_JoinAndTransmit

CC=g++
RM=rm -f
CFLAGS=-I lib/lmic
LDFLAGS=-lwiringPi

SRC=$(wildcard src/*.c)
OBJ=$(SRC:%.c)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	@echo "\033[0;36mBuilding LMIC library\033[0m"
	cd lib/lmic && $(MAKE)
	@echo "\033[0;36mBuilding project\033[0m"
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) lib/lmic/*.o $(LDFLAGS)

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	@echo "\033[0;36mCleaning the project and libraries\033[0m"
	rm -f $(TARGET)
	cd lib/lmic && make clean
