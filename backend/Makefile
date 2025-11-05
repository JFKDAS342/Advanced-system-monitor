# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Iinclude -Wall -Wextra -pedantic
LDFLAGS = 

# Директории и файлы
SRCDIR = src
INCDIR = include
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = server

# Основная цель
$(TARGET): $(OBJECTS)
	@echo "🔨 Линковка исполняемого файла..."
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "✅ Сервер собран: $(TARGET)"

# Правило для компиляции .cpp файлов
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "📦 Компиляция $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Основные цели
all: $(TARGET)

clean:
	@echo "🧹 Очистка проекта..."
	rm -f $(OBJECTS) $(TARGET) server.log
	@echo "✅ Проект очищен"

run: $(TARGET)
	@echo "🚀 Запуск сервера..."
	./$(TARGET)

debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Зависимости для объектных файлов
$(SRCDIR)/main.o: $(INCDIR)/WebServer.h
$(SRCDIR)/WebServer.o: $(INCDIR)/WebServer.h $(INCDIR)/MetricsCollector.h
$(SRCDIR)/MetricsCollector.o: $(INCDIR)/MetricsCollector.h $(INCDIR)/JSONSerializer.h
$(SRCDIR)/JSONSerializer.o: $(INCDIR)/JSONSerializer.h
$(SRCDIR)/FileLogger.o: $(INCDIR)/FileLogger.h

.PHONY: all clean run debug info help