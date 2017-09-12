CC=gcc
CFLAGS=-std=c99 -g -Wall -Wpedantic -Werror
LFLAGS=-lm


%.o: %.c
	$(CC) $(CFLAGS) -c $? -o $@ 

all: AddressTranslator

AddressTranslator: AddressTranslator.o
	$(CC) AddressTranslator.o -o AddressTranslator $(LFLAGS)

clean:
	rm -f *.o
	rm -f ProducerConsumer