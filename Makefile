# Makefile for Embedded Network Traffic Analyzer

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2

# Libraries
LIBS = -lpcap

# Target executable
TARGET = traffic_analyzer

# Source files
SRC = traffic_analyzer.c

# Default rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

# Clean rule
clean:
	rm -f $(TARGET)

# Run rule (optional)
run: $(TARGET)
	sudo ./$(TARGET)

