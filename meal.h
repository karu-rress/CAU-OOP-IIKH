#ifndef _MEAL_H_
#define _MEAL_H_

#include <date.h>
#include <list>
#include <map>
#include <string>

#include "greeter.h"
#include "recipe_db.h"

class Meal {
public:
    // Constructor
    explicit Meal(int servings = 1);
    Meal(const std::string &mealName, int servings = 1);
    Meal(const std::string &mealName, int servings, std::list<Recipe> recipes);

    // Getters
    int getServings() const;
    std::string getName() const;
    std::list<Recipe> getRecipes() const;
    // Return the complete grocery list for all recipes in the meal
    std::map<std::string, double> getGroceryList() const;

    // Adjust ingredient quantities based on the number of servings
    void adjustServings();

    // Display information about the meal
    void displayMealInfo() const;

    // Add a recipe to the meal from the database
    void addRecipe(const std::string &recipeName);
    void addRecipe(const Recipe &recipe);

    // Print the meal (list of recipe names)
    [[deprecated("No reasons to use this")]]
    void printMeal() const;

    static void setRecipeDatabase(RecipeDatabase *db);

private:
    int servings; // Number of servings
    std::string name; // Name of the meal
    std::list<Recipe> recipes; // List of recipes included in the meal

    static RecipeDatabase *recipeDB;
};

#endif