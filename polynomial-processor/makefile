# Makefile

# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Directories
INCLUDE_DIR = include
SRC_DIR = src

# Targets
TARGET = polynomial_test

# Sources
SOURCES = \
	$(SRC_DIR)/List.cpp \
	$(SRC_DIR)/Node.cpp \
	$(SRC_DIR)/FileProcessor.cpp \
	main.cpp

# Objects
OBJECTS = \
	$(SRC_DIR)/List.o \
	$(SRC_DIR)/Node.o \
	$(SRC_DIR)/FileProcessor.o \
	main.o

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation Rules

# Compile List.cpp
$(SRC_DIR)/List.o: $(SRC_DIR)/List.cpp $(INCLUDE_DIR)/List.h $(INCLUDE_DIR)/Node.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile Node.cpp
$(SRC_DIR)/Node.o: $(SRC_DIR)/Node.cpp $(INCLUDE_DIR)/Node.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile FileProcessor.cpp
$(SRC_DIR)/FileProcessor.o: $(SRC_DIR)/FileProcessor.cpp $(INCLUDE_DIR)/FileProcessor.h $(INCLUDE_DIR)/List.h $(INCLUDE_DIR)/Node.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main.cpp
$(TEST_DIR)/main.o: $(TEST_DIR)/main.cpp $(INCLUDE_DIR)/List.h $(INCLUDE_DIR)/Node.h $(INCLUDE_DIR)/FileProcessor.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(TARGET)

# Run
run: $(TARGET)
	./$(TARGET) tests.txt

.PHONY: all clean
