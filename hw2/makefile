# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Libraries to link
LIBS = -lm -lpthread -lsqlite3 -lcurl -lpaho-mqtt3c -lcjson -fopenmp

# Target application name
TARGET = main

# Source files and object files
# SRCS = main.c ml_unit.c sound_processing_unit.c shared_data.c ml_sender.c
SRCS = ./main.c ./ml_sender.c ./model_update_sender.c ./sound_processing_sender.c ./codegen/lib/NeuralNgin/filter.c ./codegen/lib/NeuralNgin/NeuralNgin_data.c ./codegen/lib/NeuralNgin/internal_softmax.c ./codegen/lib/NeuralNgin/predictForRNN.c ./codegen/lib/NeuralNgin/designMelFilterBank.c ./codegen/lib/NeuralNgin/mean.c ./codegen/lib/NeuralNgin/mfcc.c ./codegen/lib/NeuralNgin/std.c ./codegen/lib/NeuralNgin/predict.c ./codegen/lib/NeuralNgin/NeuralPredictAudio2.c ./codegen/lib/NeuralNgin/LSTMLayer.c ./codegen/lib/NeuralNgin/rtGetInf.c ./codegen/lib/NeuralNgin/NeuralNgin_terminate.c ./codegen/lib/NeuralNgin/scores2label.c ./codegen/lib/NeuralNgin/SoftmaxLayer.c ./codegen/lib/NeuralNgin/NeuralNgin_emxutil.c ./codegen/lib/NeuralNgin/cepstralCoefficients.c ./codegen/lib/NeuralNgin/rt_nonfinite.c ./codegen/lib/NeuralNgin/rtGetNaN.c ./codegen/lib/NeuralNgin/NeuralNgin_rtwutil.c ./codegen/lib/NeuralNgin/NeuralNgin_initialize.c ./codegen/lib/NeuralNgin/insertionsort.c ./codegen/lib/NeuralNgin/elementwiseOperationInPlace.c ./codegen/lib/NeuralNgin/minOrMax.c ./codegen/lib/NeuralNgin/FFTImplementationCallback.c ./codegen/lib/NeuralNgin/CheckEvent.c ./codegen/lib/NeuralNgin/ExtractFeatures.c ./codegen/lib/NeuralNgin/introsort.c ./shared_data.c ./sound_processing_unit.c ./ml_unit.c
# SRCS = main.c abs.c cepstralCoefficients.c CheckEvent.c CheckEvent_data.c CheckEvent_emxutil.c CheckEvent_initialize.c CheckEvent_rtwutil.c CheckEvent_terminate.c designMelFilterBank.c elementwiseOperationInPlace.c ExtractFeatures.c FFTImplementationCallback.c filter.c insertionsort.c internal_softmax.c introsort.c LSTMLayer.c mean.c mfcc.c minOrMax.c ml_sender.c ml_unit.c NeuralPredictAudio.c predict.c predictForRNN.c rtGetInf.c rtGetNaN.c rt_nonfinite.c scores2label.c shared_data.c SoftmaxLayer.c sound_processing_unit.c std.c
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
	rm -f $(OBJS) $(TARGET) *.db *.db-journal

gone:
	rm -f $(TARGET) $(OBJS) *.db *.o *.db-journal

# Run the application
run: $(TARGET)
	./$(TARGET)

# Clean up build artifacts and run the application
suite:
	make clean
	make run

ez:
	make gone
	c_files=$(find . -name "*.c")
	for file in $c_files; do
		$(CC) $(CFLAGS) -c $file -o $(file:.c=.o)
	done
	$(CC) $(CFLAGS) -o $(TARGET) $(c_files:.c=.o) $(LIBS)
	./$(TARGET)

# Phony targets
.PHONY: all clean run