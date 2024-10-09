#include <iostream>

#include "date.h"
#include "meal.h"
#include "recipe.h"
#include "recipe_db.h"

//
// Constructors ============================
//

Meal::Meal(int servings = 1)
    : servings(servings) { }

Meal::Meal(const std::string &mealName, int servings = 1)
    : name(mealName)
    , servings(servings) { }

Meal::Meal(const std::string &mealName, int servings, std::list<Recipe> recipes)
    : name(mealName)
    , servings(servings)
    , recipes(recipes) { }

//
// Getters ================================
//

int Meal::getServings() const {
    return servings;
}

std::string Meal::getName() const {
    return name;
}

std::list<Recipe> Meal::getRecipes() const {
    return recipes;
}

// Return the complete grocery list for all recipes in the meal
std::map<std::string, int> Meal::getGroceryList() const {
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
    std::cout << "Information about " << name
              << "(" << servings << " servings)" << std::endl;

    std::cout << "Recipes included in this meal : " << std::endl;
    for (auto &recipe : recipes) {
        std::cout << " - " << recipe.getName() << std::endl; // print name
        recipe.displayRecipe(); // print details
    }
}

// Add a recipe to the meal from the database
void Meal::addRecipe(const std::string &recipeName) {
    recipes.push_back(recipeDB->getRecipe(recipeName));
}

void Meal::addRecipe(const Recipe &recipe) {
    recipes.push_back(recipe);
}

void Meal::removeRecipe(const std::string &recipeName) {
    recipes.remove_if([&recipeName](const Recipe &recipe) {
        return recipe.getName() == recipeName;
    });
}

void Meal::removeRecipe(const Recipe &recipe) {
    recipes.remove(recipe);
}

// 4. Print the meal (recipe names)
[[deprecated("No reasons to use this")]]
void Meal::printMeal() const {
    for (auto &recipe : recipes) {
        std::cout << recipe.getName() << std::endl;
    }
}

// 7. return Servings (for plan_manager )

void Meal::setRecipeDatabase(RecipeDatabase *db) {
    recipeDB = db;
}