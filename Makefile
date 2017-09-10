## Makefile for Anakata
## Author- Abhishek Shrivastava <abhishek.shrivastava.ts@gmail.com)
CC = g++
CC_OPTIONS = -ggdb3 -Wall -std=c++11
CFLAGS = $(CC_OPTIONS)

ODIR = obj
BUILD = build
BIN = bin
SDIR = src

.PHONY: clean cleano

all:
	$(CC) $(CC_OPTIONS) -o $(EXE) $(SRC)

run:
	$(CC) $(CC_OPTIONS) -o $(EXE) $(SRC)
	./$(EXE)

config:
	$(CC) $(CC_OPTIONS) $(SDIR)/configure.cpp -o $(BUILD)/$@
	cd $(BUILD); ./$@

# this target compiles and links the client
client: clean
	$(CC) $(CC_OPTIONS) -c $(SDIR)/KatClient/KatClient.cpp -o $(ODIR)/KatClient.o
	$(CC) $(CC_OPTIONS) -c $(SDIR)/KatClient/katalyn.cpp -o $(ODIR)/katalyn.o
	$(CC) $(CC_OPTIONS) -c $(SDIR)/logger.cpp -o $(ODIR)/logger.o
	$(CC) $(CC_OPTIONS) $(ODIR)/*.o  -o $(BUILD)/$@
	cp $(BUILD)/* $(BIN)/

cleano:
	rm -f $(ODIR)/*.o

clean:
	rm -f $(BUILD)/* $(ODIR)/*.o
