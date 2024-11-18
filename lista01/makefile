# Makefile

# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Directories
INCLUDE_DIR = include
SRC_DIR = src
TEST_DIR = tests

# Targets
TARGET = polynomial_test
SOURCES = $(SRC_DIR)/List.cpp $(SRC_DIR)/Node.cpp $(TEST_DIR)/main.cpp
OBJECTS = $(SRC_DIR)/List.o $(SRC_DIR)/Node.o $(TEST_DIR)/main.o

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation
$(SRC_DIR)/List.o: $(SRC_DIR)/List.cpp $(INCLUDE_DIR)/List.h $(INCLUDE_DIR)/Node.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SRC_DIR)/Node.o: $(SRC_DIR)/Node.cpp $(INCLUDE_DIR)/Node.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_DIR)/main.o: $(TEST_DIR)/main.cpp $(INCLUDE_DIR)/List.h $(INCLUDE_DIR)/Node.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(TARGET)

.PHONY: all clean
