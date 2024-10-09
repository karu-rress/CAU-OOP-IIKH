# Makefile for IIKH

CC = g++
OPTIONS = -Wall -Wextra -std=c++20

date.o: date.h date.cpp
	$(CC) -c date.cpp $(OPTIONS)

greeter.o: greeter.h greeter.cpp
	$(CC) -c greeter.cpp $(OPTIONS)

meal.o: meal.h meal.cpp
	$(CC) -c meal.cpp $(OPTIONS)

plan_manager.o: plan_manager.h plan_manager.cpp
	$(CC) -c plan_manager.cpp $(OPTIONS)

recipe_db.o: recipe_db.h recipe_db.cpp
	$(CC) -c recipe_db.cpp $(OPTIONS)

recipe.o: recipe.h recipe.cpp
	$(CC) -c recipe.cpp $(OPTIONS)

main.o: main.cpp
	$(CC) -c main.cpp $(OPTIONS)

main: date.o greeter.o meal.o plan_manager.o recipe_db.o recipe.o main.o
	$(CC) -o iikh date.o greeter.o meal.o plan_manager.o recipe_db.o recipe.o main.o $(OPTIONS)

clean:
	rm -f *.o iikh