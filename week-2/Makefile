##################################################
# Makefile template to build the define target
##################################################

# C compiler
CC = gcc
# C compiler flags
CFLAGS = -g -Wall
# Target executable name
TARGET = write-demo

all: $(TARGET)

# Used to build executable from .o file(s)
$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o

# Used to build .o file(s) from .c files(s)
$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

# clean built artifacts
clean:
	rm -f $(TARGET) $(TARGET).o

# Used to output a help message for the Makefile
help:
	@echo  "Usage: make [target] ...\n"
	@echo  "Miscellaneous:"
	@echo  "help\t\t\tShows this help\n"
	@echo  "Build:"
	@echo  "all\t\t\tBuild all the project\n"
	@echo  "Cleaning:"
	@echo  "clean\t\t\tRemove all intermediate objects"
