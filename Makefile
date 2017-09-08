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


all:
	$(CC) $(CC_OPTIONS) -o $(EXE) $(SRC)

run:
	$(CC) $(CC_OPTIONS) -o $(EXE) $(SRC)
	./$(EXE)

config:
	$(CC) $(CC_OPTIONS) $(SDIR)/configure.cpp -o $(BUILD)configure
	cd $(BUILD); ./configure

clean:
	rm $(BUILD)/* $(ODIR)/*

