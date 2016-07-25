CC=g++

OBJ=aes.o hal.o lmic.o oslmic.o radio.o
SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: all
all: $(OBJ)

.PHONY: clean
clean:
	rm *.o
