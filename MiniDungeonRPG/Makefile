CXX = g++
CXXFLAGS = -Wall -std=c++14

TARGET = MiniDungeonRPG
SRC = MiniDungeonRPG.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Use 'del' instead of 'rm' for Windows
clean:
	del /Q *.o $(TARGET).exe

run: $(TARGET)
	.\$(TARGET).exe
