# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Libraries to link
LIBS = -lm -lpthread -lsqlite3 -lcurl -lpaho-mqtt3c -lcjson

# Target application name
TARGET = main

# Source files and object files
SRCS = main.c ml_unit.c sound_processing_unit.c shared_data.c ml_sender.c
OBJS = $(SRCS:.c=.o)

# Default target to build the application
all: $(TARGET)

# Rule to link object files and create the executable with libraries
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET) *.db

# Run the application
run: $(TARGET)
	./$(TARGET)

# Clean up build artifacts and run the application
test:
	make clean
	make run

# Phony targets
.PHONY: all clean run