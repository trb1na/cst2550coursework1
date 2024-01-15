CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic -std=c++17
LDFLAGS =
RM = rm -f
TARGET = Library
TEST_TARGET = tests
SRCS = main.cpp Book.cpp Librarian.cpp Member.cpp Person.cpp utils.cpp
TEST_SRCS = tests.cpp Book.cpp Librarian.cpp Member.cpp Person.cpp utils.cpp
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)