# Makefile for IIKH

CC = g++

date.o: date.h date.cpp
	$(CC) -c date.cpp

greeter.o: greeter.h greeter.cpp
	$(CC) -c greeter.cpp

meal.o: meal.h meal.cpp
	$(CC) -c meal.cpp

plan_manager.o: plan_manager.h plan_manager.cpp
	$(CC) -c plan_manager.cpp

recipe_db.o: recipe_db.h recipe_db.cpp
	$(CC) -c recipe_db.cpp

recipe.o: recipe.h recipe.cpp
	$(CC) -c recipe.cpp

main.o: main.cpp
	$(CC) -c main.cpp

main: date.o greeter.o meal.o plan_manager.o recipe_db.o recipe.o main.o
	$(CC) -o iikh date.o greeter.o meal.o plan_manager.o recipe_db.o recipe.o main.o

clean:
	rm -f *.o iikh