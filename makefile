# Masukkan semua file c Anda
OBJS = graphics/frame_buffer.c graphics/draw.cpp paint/command.cpp paint/render.cpp object/object.cpp object/pointer/pointer.cpp main.cpp

# frame_buffer.c draw.c object.cpp sample_object.cpp driver_sampleObject.cpp

CC = g++
# COMPILER_FLAGS = -g -std=c++11 -Wall -O2
LINKER_FLAGS = -pthread
OBJ_NAME = image
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
