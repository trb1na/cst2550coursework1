CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iincludes
LDFLAGS = 
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDES = includes

LIB_SRCS := $(filter-out $(SRC_DIR)/tests.cpp, $(wildcard $(SRC_DIR)/*.cpp))
LIB_OBJS := $(LIB_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TEST_SRCS := $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))
TEST_OBJS := $(TEST_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all clean library test

all: library test

library: $(BIN_DIR)/library

test: $(BIN_DIR)/test

$(BIN_DIR)/library: $(LIB_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BIN_DIR)/test: $(TEST_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)/*.o $(BIN_DIR)/test $(BIN_DIR)/library