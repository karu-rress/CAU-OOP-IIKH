#ifndef _MEAL_H_
#define _MEAL_H_

#include <date.h>
#include <list>
#include <map>
#include <string>

#include "recipe_db.h"

class Meal {
public:
    // Constructor
    Meal(int servings = 1);
    Meal::Meal(std::string mealName) : name(mealName) {}

    // Adjust ingredient quantities based on the number of servings
    void adjustServings();

    // Display information about the meal
    void displayMealInfo() const;

    // Add a recipe to the meal from the database
    void addRecipe(RecipeDatabase &db, const std::string &recipeName);

    // Print the meal (list of recipe names)
    void printMeal() const;

    // Return the list of meal names (list of recipe names)
    std::list<std::string> getMeals() const;

    // Return the complete grocery list for all recipes in the meal
    std::map<std::string, double> getGroceryList() const;

    // Return the servings
    int Meal::getServings();

private:
    int servings;    
    std::string name;            // Number of servings
    std::list<Recipe> recipes;      // List of recipes included in the meal
};

#endif