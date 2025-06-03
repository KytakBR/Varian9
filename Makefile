CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS = 
SRC = src/main.cpp src/transport.cpp
OUT_DIR = build
TARGET = $(OUT_DIR)/app

$(TARGET): $(SRC)
	mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf $(OUT_DIR)

