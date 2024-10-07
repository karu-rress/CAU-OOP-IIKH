#include "meal.h"
#include "recipe_db.h"
#include "recipe.h"
#include "date.h"

// Constructor implementation
Meal::Meal(int servings = 1) : servings(servings) {}

// 1. Adjust ingredient quantities based on the number of servings
void Meal::adjustServings(int newServings) {
    servings = newServings;
    for (auto& recipe : recipes) {
        recipe.adjustForServings(servings);
    }
}

// 2. Display information about the meal
void Meal::displayMealInfo() {
    // main 에서 Date::displayAndEdit()-> 
    std::cout << "Meal Information : " << std::endl;
    std::cout << "Number of servings : " << servings << std::endl;

    std::cout << "Recipes included in this meal : " << std::endl;
    for (auto& recipe : recipes) {
        std::cout << " - " << recipe.getName() << std::endl; // print name
        recipe.displayRecipe(); // print details
    }
} 

// 3. Add a recipe to the meal from the database
void Meal::addRecipeToMeal(RecipeDatabase& db, const std::string& recipeName) {
    Recipe recipe = db.getRecipe(recipeName); // Get the recipe from RecipeDatabase
    recipes.push_back(recipe); // Add recipe to the meal
}

// 4. Print the meal (recipe names) 
void Meal::printMeal() {
    for (auto& recipe : recipes) {
        std::cout << recipe.getName() << std::endl;
    }
}

// 5. Return the list of meal names (list of recipe names)
std::list<std::string> Meal::getMeals() {
    std::list<std::string> mealList;
    for (auto& recipe : recipes) {
        mealList.push_back(recipe.getName());
    }
    return mealList;
}

// 6. Return the complete grocery list for all recipes in the meal
std::map<std::string, double> Meal::getGroceryList() {
    std::map<std::string, double> groceryList;
    std::cout << "Grocery List : " << std::endl;
    for (auto& recipe : recipes) {
        std::map<std::string, double> recipeGroceryList = recipe.getGroceryList();
        for (auto& [ingredient, amount] : recipeGroceryList) {
            groceryList[ingredient] += amount;  // Combine ingredients and amounts
        }
    }
    for (auto& [ingredient, amount] : groceryList) {
        std::cout << " - " << ingredient << ": " << amount << std::endl;
    }
    return groceryList;
}