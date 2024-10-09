#include <iostream>

#include "date.h"
#include "meal.h"
#include "recipe.h"
#include "recipe_db.h"

// Constructor implementation
Meal::Meal(int servings = 1)
    : servings(servings) { }

void Meal::adjustServings() {
    std::cout << "Enter the number of servings: ";
    std::cin >> servings;
}

// Display informations about the meal
void Meal::displayMealInfo() const {
    // TODO: what is this
    // std::cout << "Meal Information : " << std::endl;
    std::cout << "Number of servings : " << servings << std::endl;

    std::cout << "Recipes included in this meal : " << std::endl;
    for (auto &recipe : recipes) {
        std::cout << " - " << recipe.getName() << std::endl; // print name
        recipe.displayRecipe(); // print details
    }
}

// Add a recipe to the meal from the database
void Meal::addRecipe(RecipeDatabase &db, const std::string &recipeName) {
    Recipe recipe = db.getRecipe(recipeName); // Get the recipe from RecipeDatabase
    recipes.push_back(recipe); // Add recipe to the meal
}

// Print the meal (recipe names)
void Meal::printMeal() const {
    for (auto &recipe : recipes) {
        std::cout << recipe.getName() << std::endl;
    }
}

// Return the list of meal names (list of recipe names)
std::list<std::string> Meal::getMeals() const {
    std::list<std::string> mealList;
    for (auto &recipe : recipes) {
        mealList.push_back(recipe.getName());
    }
    return mealList;
}

// Return the complete grocery list for all recipes in the meal
std::map<std::string, double> Meal::getGroceryList() const {
    std::map<std::string, double> groceryList;

    for (const auto &recipe : recipes) {
        for (const auto &[name, quantity] : recipe.getIngredients()) {
            groceryList[name] += quantity * servings;
        }
    }

    return groceryList;
}