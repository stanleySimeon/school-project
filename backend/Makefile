# Makefile for School Management Backend

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = school_server
SRC = main.cpp

all: download_json $(TARGET)

# Download the JSON library if not present
download_json:
	@if [ ! -f json.hpp ] || grep -q "error" json.hpp; then \
		echo "Downloading nlohmann/json library..."; \
		curl -o json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp; \
		echo "JSON library downloaded successfully!"; \
	fi

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) data.json

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run download_json
