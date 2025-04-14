
# Email: thelet.shevach@gmail.com

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude -I.

# Directory definitions
SRC_DIR = src
TEST_DIR = tests

# Executable names
MAIN_EXEC = main
TEST_EXEC = test

# Default target - build main demonstration
all: Main

Main: $(SRC_DIR)/main.cpp $(SRC_DIR)/Graph.cpp $(SRC_DIR)/Algorithms.cpp
	$(CXX) $(CXXFLAGS) -o $(MAIN_EXEC) $(SRC_DIR)/main.cpp $(SRC_DIR)/Graph.cpp $(SRC_DIR)/Algorithms.cpp

# Test target (doctest driver)
test: $(TEST_DIR)/test.cpp $(SRC_DIR)/Graph.cpp $(SRC_DIR)/Algorithms.cpp
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_DIR)/test.cpp $(SRC_DIR)/Graph.cpp $(SRC_DIR)/Algorithms.cpp
	./$(TEST_EXEC)

# Valgrind target to check for memory leaks on the main executable
valgrind: Main
	valgrind --leak-check=full ./$(TEST_EXEC)

# Clean target to remove generated executables
clean:
	rm -f $(MAIN_EXEC) $(TEST_EXEC)
