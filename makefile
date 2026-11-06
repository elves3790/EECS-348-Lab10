CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET = lab10
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC) Matrix.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
