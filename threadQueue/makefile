# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Source and Object Files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Target executable
TARGET = $(BIN_DIR)/threadQueue

# Default rule
all: $(TARGET)

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Link executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean the build files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Debug mode
debug: CXXFLAGS += -g
debug: clean all