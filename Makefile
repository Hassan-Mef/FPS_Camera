# Compiler
CXX = g++

# Output file
TARGET = game

# Source files
SRC = main.cpp

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -O2

# Libraries
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) Player/player.cpp HUD/HUD.cpp -o $(TARGET) $(CXXFLAGS) $(LIBS)

# Run the game
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -f $(TARGET)
