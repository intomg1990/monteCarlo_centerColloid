# Variables
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Iinclude
OBJ_DIR = obj
BIN_DIR = bin
EXECUTABLE = $(BIN_DIR)/my_program.exe

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_DIR)/main.o $(OBJ_DIR)/initialization_funcs.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/initialization_funcs.o: src/initialization_funcs.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)
