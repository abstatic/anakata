## Makefile for Anakata
## Author- Abhishek Shrivastava <abhishek.shrivastava.ts@gmail.com)
CC = g++
CC_OPTIONS = -ggdb3 -Wall -std=c++11
CFLAGS = $(CC_OPTIONS)

ODIR = obj
BUILD = build/
SDIR = src
SDIRK = src/katalyn/
SDIRT = src/trackr/

.PHONY: clean

all:
	$(CC) $(CC_OPTIONS) -o $(EXE) $(SRC)

run:
	$(CC) $(CC_OPTIONS) -o $(EXE) $(SRC)
	./$(EXE)

config:
	$(CC) $(CC_OPTIONS) $(SDIR)/configure.cpp -o $(BUILD)configure
	cd $(BUILD); ./configure

# this target compiles and links the client
client: cleano
	$(CC) $(CC_OPTIONS) -c $(SDIR)/KatClient/KatClient.cpp -o $(ODIR)/KatClient.o
	$(CC) $(CC_OPTIONS) -c $(SDIR)/logger.cpp -o $(BUILD)/logger.o

cleano:
	rm $(ODIR)/*


clean:
	rm $(BUILD)/* $(ODIR)/*
