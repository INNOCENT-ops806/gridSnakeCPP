TARGET = main.out

SRC = main.cpp

CXX = g++

CXXFLAGS = -Wall -std=c++17
LDFLAGS = -lraylib -lm -lpthread -ldl -lrt -lX11

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

