# Define the build configuration
BUILD_TYPE ?= Debug
CXXFLAGS_DEBUG = -g -O0 -std=c++11
CXXFLAGS_RELEASE = -O3 -std=c++11
CXXFLAGS = $(CXXFLAGS_DEBUG)
LDFLAGS = 

# Define the executable name
EXE_NAME = inOneWeekend
IMAGE_FILE = image.ppm

# Source files
SRC = $(wildcard *.cpp)
# Object files
OBJ = $(SRC:.cpp=.o)

# Default target
all: build run

# Build target
build: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXE_NAME) $(OBJ) $(LDFLAGS)

# Rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run target
run:
	./$(EXE_NAME) > $(IMAGE_FILE)

# Clean target
clean:
	rm -f $(OBJ) $(EXE_NAME) $(IMAGE_FILE)
