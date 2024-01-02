# Compiler settings - Can be customized.
CC = g++
CCFLAGS = -std=c++17 -Wall -Iinclude

# Build target
TARGET = StudentDatabase

# Source and object files
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^

# Compiling
%.o: %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean
