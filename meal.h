#ifndef _MEAL_H_
#define _MEAL_H_

#include <list>
#include <map>
#include <string>

#include "date.h"
#include "greeter.h"
#include "recipe_db.h"

class Recipe;

class Meal {
public:
    // Constructor
    
    explicit Meal(int servings = 1);
    Meal(const std::string &mealName, int servings = 1);
    Meal(const std::string &mealName, int servings, const std::list<Recipe> &recipes);

    // Getters
    [[nodiscard]] int getServings() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::list<Recipe> getRecipes() const;
    // Return the complete grocery list for all recipes in the meal
    [[nodiscard]] std::map<std::string, int> getGroceryList() const;

    // Adjust ingredient quantities based on the number of servings
    void adjustServings();

    // Display information about the meal
    void displayMealInfo() const;

    // Add a recipe to the meal from the database
    void addRecipe(const std::string &recipeName);
    void addRecipe(const Recipe &recipe);

    // Remove a recipe from the meal
    void removeRecipe(const std::string &recipeName);

    // Print the meal (list of recipe names)
    [[deprecated("No reasons to use this")]]
    void printMeal() const;

    static void setRecipeDatabase(RecipeDatabase *db);

private:
    int servings; // Number of servings
    std::string name; // Name of the meal
    std::list<Recipe> recipes; // List of recipes included in the meal

    static inline RecipeDatabase *recipeDB = nullptr;
};

#endif