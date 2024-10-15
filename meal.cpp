#include <format>
#include <iostream>

#include "date.h"
#include "meal.h"
#include "recipe.h"
#include "recipe_db.h"

//
// Constructors ============================
//

Meal::Meal(int servings)
    : servings(servings) { }

Meal::Meal(const std::string &mealName, int servings)
    : servings(servings)
    , name(mealName) { }

Meal::Meal(const std::string &mealName, int servings, const std::list<std::string> &recipes)
    : Meal(mealName, servings) {
    for (const auto &recipe : recipes) {
        addRecipe(recipe);
    }
}

//
// Getters ================================
//

[[nodiscard]] int Meal::getServings() const {
    return servings;
}

[[nodiscard]] std::string Meal::getName() const {
    return name;
}

[[nodiscard]] std::list<Recipe> Meal::getRecipes() const {
    return recipes;
}

// Return the complete grocery list for all recipes in the meal
[[nodiscard]] std::map<std::string, int> Meal::getGroceryList() const {
    std::map<std::string, int> groceryList;

    for (const auto &recipe : recipes) {
        for (const auto &[name, quantity] : recipe.getIngredients()) {
            groceryList[name] += quantity * servings;
        }
    }

    return groceryList;
}

//////////

void Meal::adjustServings() {
    std::cout << "Enter the number of servings: ";
    std::cin >> servings;
}

// Display informations about the meal
void Meal::displayMealInfo() const {
    std::cout << std::format("Information about {} ({} servings)\n", name, servings);

    std::cout << "Recipes included in this meal : " << std::endl;
    for (auto &recipe : recipes) {
        // print name
        std::cout << std::format(" - {} (for {} servings)\n", recipe.getName(), servings);
        recipe.displayRecipe(); // print details
    }
}

// Add a recipe to the meal from the database
void Meal::addRecipe(const std::string &recipeName) {
    recipes.push_back((*Meal::recipeDB)[recipeName]);
}

void Meal::addRecipe(const Recipe &recipe) {
    recipes.push_back(recipe);
}

void Meal::removeRecipe(const std::string &recipeName) {
    recipes.remove_if([&recipeName](const Recipe &recipe) {
        return recipe.getName() == recipeName;
    });
}

// Print the meal (recipe names)
[[deprecated("Use displayMealInfo() instead")]]
void Meal::printMeal() const {
    for (auto &recipe : recipes) {
        std::cout << recipe.getName() << std::endl;
    }
}

// return Servings (for plan_manager)
void Meal::setRecipeDatabase(RecipeDatabase *db) {
    Meal::recipeDB = db;
}