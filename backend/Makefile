# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -pedantic
SOURCES = src/FileLogger.cpp src/JSONSerializer.cpp src/main.cpp src/MetricsCollector.cpp src/WebServer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = server

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

src/FileLogger.o: src/FileLogger.cpp include/FileLogger.h
	$(CXX) $(CXXFLAGS) -c src/FileLogger.cpp -o src/FileLogger.o

src/JSONSerializer.o: src/JSONSerializer.cpp include/JSONSerializer.h
	$(CXX) $(CXXFLAGS) -c src/JSONSerializer.cpp -o src/JSONSerializer.o

src/main.o: src/main.cpp include/WebServer.h include/MetricsCollector.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o src/main.o

src/MetricsCollector.o: src/MetricsCollector.cpp include/MetricsCollector.h include/SystemMetrics.h
	$(CXX) $(CXXFLAGS) -c src/MetricsCollector.cpp -o src/MetricsCollector.o

src/WebServer.o: src/WebServer.cpp include/WebServer.h include/MetricsCollector.h
	$(CXX) $(CXXFLAGS) -c src/WebServer.cpp -o src/WebServer.o

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean run