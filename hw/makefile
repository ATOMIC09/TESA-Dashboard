# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Libraries to link
LIBS = -lm -lpthread -lsqlite3 -lcurl -lpaho-mqtt3c -lcjson

# Target application name
TARGET = main

# Source files and object files
SRCS = main.c ml_unit.c sound_processing_unit.c shared_data.c ml_sender.c
# cepstralCoefficients.c elementwiseOperationInPlace.c FFTImplementationCallback.c insertionsort.c internal_softmax.c introsort.c LSTMLayer.c mean.c mfcc.c minOrMax.c NeuralPredictAudio.c NeuralPredictAudio_data.c NeuralPredictAudio_emxutil.c NeuralPredictAudio_initialize.c NeuralPredictAudio_rtwutil.c NeuralPredictAudio_terminate.c predict.c predictForRNN.c rtGetInf.c rtGetNaN.c rt_nonfinite.c scores2label.c SoftmaxLayer.c std.c
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
suite:
	make clean
	make run

# Phony targets
.PHONY: all clean run