# Makefile for School Management Backend

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = school_server
SOURCES = main.cpp datastore.cpp http.cpp handlers.cpp router.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: download_json $(TARGET)

# Download the JSON library if not present
download_json:
	@if [ ! -f json.hpp ] || grep -q "error" json.hpp; then \
		echo "Downloading nlohmann/json library..."; \
		curl -o json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp; \
		echo "JSON library downloaded successfully!"; \
	fi

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) data.json

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run download_json
