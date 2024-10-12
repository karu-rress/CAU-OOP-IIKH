# Makefile for IIKH

CC = g++
CXXFLAGS = -Wall -Wextra -std=c++20

BIN_DIR := ./bin
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

all: iikh

$(BIN_DIR)/date.o: date.h date.cpp | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -c date.cpp -o $(BIN_DIR)/date.o

$(BIN_DIR)/greeter.o: greeter.h greeter.cpp | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -c greeter.cpp -o $(BIN_DIR)/greeter.o

$(BIN_DIR)/meal.o: meal.h meal.cpp | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -c meal.cpp -o $(BIN_DIR)/meal.o

$(BIN_DIR)/plan_manager.o: plan_manager.h plan_manager.cpp | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -c plan_manager.cpp -o $(BIN_DIR)/plan_manager.o

$(BIN_DIR)/recipe_db.o: recipe_db.h recipe_db.cpp | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -c recipe_db.cpp -o $(BIN_DIR)/recipe_db.o

$(BIN_DIR)/recipe.o: recipe.h recipe.cpp | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -c recipe.cpp -o $(BIN_DIR)/recipe.o

$(BIN_DIR)/main.o: main.cpp | $(BIN_DIR)
	$(CC) $(CXXFLAGS) -c main.cpp -o $(BIN_DIR)/main.o

iikh: $(BIN_DIR)/date.o $(BIN_DIR)/greeter.o $(BIN_DIR)/meal.o $(BIN_DIR)/plan_manager.o $(BIN_DIR)/recipe_db.o $(BIN_DIR)/recipe.o $(BIN_DIR)/main.o
	$(CC) $(CXXFLAGS) -o iikh $(BIN_DIR)/date.o $(BIN_DIR)/greeter.o $(BIN_DIR)/meal.o $(BIN_DIR)/plan_manager.o $(BIN_DIR)/recipe_db.o $(BIN_DIR)/recipe.o $(BIN_DIR)/main.o

clean:
	rm -f $(BIN_DIR)/*.o iikh
