# Makefile for IIKH

CC = g++
CXXFLAGS = -Wall -Wextra -std=c++20

all: iikh

./bin/date.o: date.h date.cpp
# save to ./bin
	$(CC) $(CXXFLAGS) -c date.cpp -o ./bin/date.o

./bin/greeter.o: greeter.h greeter.cpp
	$(CC) $(CXXFLAGS) -c greeter.cpp -o ./bin/greeter.o

./bin/meal.o: meal.h meal.cpp
	$(CC) $(CXXFLAGS) -c meal.cpp -o ./bin/meal.o

./bin/plan_manager.o: plan_manager.h plan_manager.cpp
	$(CC) $(CXXFLAGS) -c plan_manager.cpp -o ./bin/plan_manager.o

./bin/recipe_db.o: recipe_db.h recipe_db.cpp
	$(CC) $(CXXFLAGS) -c recipe_db.cpp -o ./bin/recipe_db.o

./bin/recipe.o: recipe.h recipe.cpp
	$(CC) $(CXXFLAGS) -c recipe.cpp -o ./bin/recipe.o

./bin/main.o: main.cpp
	$(CC) $(CXXFLAGS) -c main.cpp -o ./bin/main.o

iikh: ./bin/date.o ./bin/greeter.o ./bin/meal.o ./bin/plan_manager.o ./bin/recipe_db.o ./bin/recipe.o ./bin/main.o
	$(CC) $(CXXFLAGS) -o iikh ./bin/date.o ./bin/greeter.o ./bin/meal.o ./bin/plan_manager.o ./bin/recipe_db.o ./bin/recipe.o ./bin/main.o

clean:
	rm -f ./bin/*.o iikh
