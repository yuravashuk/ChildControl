
# get os type
UNAME=$(shell uname)

# select compiler
ifeq ($(UNAME), Linux)
CC=g++
OUTPATH=./Bin/Linux
endif
ifeq ($(UNAME), Darwin)
CC=clang++
OUTPATH=./Bin/Mac
endif

# compiler flags
CFLAGS=-c -Wall -std=c++0x #-m32

# library flags
CLIBS=-pthread

# source files
SOURCES=./Source/Main.cpp ./Source/Deamon.cpp ./Source/TimeController.cpp ./Source/WebService.cpp

# object files
OBJECTS=$(SOURCES:.cpp=.o)

# executable app name
EXECUTABLE_NAME=service
BIN_PATH=$(EXECUTABLE_NAME:%=$(OUTPATH)/%)

all: $(SOURCES) $(BIN_PATH)
	
$(BIN_PATH): clean $(OBJECTS)
		$(CC) $(OBJECTS) $(CLIBS) -o $@ 
		rm -rf ./Source/*.o || true

.cpp.o:
		$(CC) $(CFLAGS) $(CLIBS) $< -o $@

clean:
	rm -rf ./Source/*.o service


