# Makefile for IIKH

# Use the GNU C++ compiler
CC = g++

# Using C++20 standard
CXXFLAGS = -Wall -Wextra -std=c++20

SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

all: iikh

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(BIN_DIR)/date.o: $(INCLUDE_DIR)/date.h $(SRC_DIR)/date.cpp | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -c $(SRC_DIR)/date.cpp -o $(BIN_DIR)/date.o

$(BIN_DIR)/greeter.o: $(INCLUDE_DIR)/greeter.h $(SRC_DIR)/greeter.cpp | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -c $(SRC_DIR)/greeter.cpp -o $(BIN_DIR)/greeter.o

$(BIN_DIR)/meal.o: $(INCLUDE_DIR)/meal.h $(SRC_DIR)/meal.cpp | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -c $(SRC_DIR)/meal.cpp -o $(BIN_DIR)/meal.o

$(BIN_DIR)/plan_manager.o: $(INCLUDE_DIR)/plan_manager.h $(SRC_DIR)/plan_manager.cpp | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -c $(SRC_DIR)/plan_manager.cpp -o $(BIN_DIR)/plan_manager.o

$(BIN_DIR)/recipe_db.o: $(INCLUDE_DIR)/recipe_db.h $(SRC_DIR)/recipe_db.cpp | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -c $(SRC_DIR)/recipe_db.cpp -o $(BIN_DIR)/recipe_db.o

$(BIN_DIR)/recipe.o: $(INCLUDE_DIR)/recipe.h $(SRC_DIR)/recipe.cpp | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -c $(SRC_DIR)/recipe.cpp -o $(BIN_DIR)/recipe.o

$(BIN_DIR)/main.o: main.cpp | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -c main.cpp -o $(BIN_DIR)/main.o

iikh: $(BIN_DIR)/date.o $(BIN_DIR)/greeter.o $(BIN_DIR)/meal.o $(BIN_DIR)/plan_manager.o $(BIN_DIR)/recipe_db.o $(BIN_DIR)/recipe.o $(BIN_DIR)/main.o
	$(CC) $(CXXFLAGS) -o iikh $(BIN_DIR)/date.o $(BIN_DIR)/greeter.o $(BIN_DIR)/meal.o $(BIN_DIR)/plan_manager.o $(BIN_DIR)/recipe_db.o $(BIN_DIR)/recipe.o $(BIN_DIR)/main.o

clean:
	rm -f $(BIN_DIR)/*.o iikh
