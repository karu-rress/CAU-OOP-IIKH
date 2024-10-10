# Makefile for IIKH

CC = g++
CXXFLAGS = -std=c++17

date.o: date.h date.cpp
	$(CC) $(CXXFLAGS) -c date.cpp

greeter.o: greeter.h greeter.cpp
	$(CC) $(CXXFLAGS) -c greeter.cpp

meal.o: meal.h meal.cpp
	$(CC) $(CXXFLAGS) -c meal.cpp

plan_manager.o: plan_manager.h plan_manager.cpp
	$(CC) $(CXXFLAGS) -c plan_manager.cpp

recipe_db.o: recipe_db.h recipe_db.cpp
	$(CC) $(CXXFLAGS) -c recipe_db.cpp

recipe.o: recipe.h recipe.cpp
	$(CC) $(CXXFLAGS) -c recipe.cpp

main.o: main.cpp
	$(CC) $(CXXFLAGS) -c main.cpp

main: date.o greeter.o meal.o plan_manager.o recipe_db.o recipe.o main.o
	$(CC) $(CXXFLAGS) -o iikh date.o greeter.o meal.o plan_manager.o recipe_db.o recipe.o main.o

clean:
	rm -f *.o iikh
