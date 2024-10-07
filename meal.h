/*
- Holds information about a single meal
- Allows the user to interact with the recipe database to
  select individual recipes for meals
- The user sets the number of servings, and the recipes
  are automatically scaled accordingly
- Can generate a grocery list for the entire meal by combining
  grocery lists from individual scaled recipes
*/
#ifndef _MEAL_H_
#define _MEAL_H_

#include <iostream>
#include <string>
#include <list>
#include <map>

#include <recipe_db.h>
#include <date.h>

class Meal {
public:
    // Constructor
    Meal(int servings = 1);

    // Adjust ingredient quantities based on the number of servings
    void adjustServings(int newServings);

    // Display information about the meal
    void displayMealInfo();

    // Add a recipe to the meal from the database
    void addRecipeToMeal(RecipeDatabase& db, const std::string& recipeName);

    // Print the meal (list of recipe names)
    void printMeal();

    // Return the list of meal names (list of recipe names)
    std::list<std::string> getMeals();

    // Return the complete grocery list for all recipes in the meal
    std::map<std::string, double> getGroceryList();

private:
    int servings;                  // Number of servings
    std::list<Recipe> recipes;      // List of recipes included in the meal
};

#endif