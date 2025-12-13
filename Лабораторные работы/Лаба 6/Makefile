CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS = -lsqlite3
TEST_LDFLAGS = -lgtest -lgtest_main -pthread -lsqlite3
SRC_DIR = src
OBJ_DIR = build
TEST_DIR = tests
TARGET = university_db
TEST_TARGET = test_runner

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Объектные файлы для тестов (исключаем main.cpp)
LIB_SOURCES = $(filter-out $(SRC_DIR)/main.cpp, $(SOURCES))
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Цель для компиляции и запуска тестов
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(LIB_OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(LIB_OBJECTS) $(TEST_OBJECTS) -o $(TEST_TARGET) $(TEST_LDFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_TARGET) university.db university.db-shm university.db-wal

.PHONY: all clean test
