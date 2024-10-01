/**
 *
 * recipe_db.cpp
 *
 * @author: Na Sunwoo@CSE-23 (@karu-rress)
 * @brief: Recipe와 Meal을 관리하는 데이터베이스 Wrapper
 * @version: 0.1
 *
 */

#include "recipe_db.h"

// namespace alias for std::filesystem
namespace fs = std::filesystem;
using namespace std;

// Initialize the RecipeDatabase
RecipeDatabase::RecipeDatabase() {
    // Get the path to the database file
    // If directory doesn't exist, return
    if (m_dbPath = fs::current_path() / "data"; fs::exists(m_dbPath) == false)
        return;

    // Open the recipe database file
    if (m_dbFile.open(m_dbPath / recipeFileName, ios::in | ios::binary);
        !m_dbFile.is_open())
        return;

    // Read the recipes from the file
    while (m_dbFile.eof() == false) {
        Recipe recipe;
        m_dbFile.read(reinterpret_cast<char *>(&recipe), sizeof(Recipe));
        m_recipes.push_back(recipe);
    }
    m_dbFile.close();

#ifdef SAVE_MEAL
    // Open the meal database file
    if (m_dbFile.open(m_dbPath / mealFileName, ios::in | ios::binary);
        !m_dbFile.is_open())
        return;

    // Read the meals from the file
    while (m_dbFile.eof() == false) {
        Meal meal;
        m_dbFile.read(reinterpret_cast<char *>(&meal), sizeof(Meal));
        m_meals.push_back(meal);
    }
    m_dbFile.close();
#endif
}

// Search recipes by keyword
list<Recipe> RecipeDatabase::searchRecipes(const vector<string> &keywords) const {
    list<Recipe> result;

    // Search for the keyword in the recipe list
    for (auto &recipe : m_recipes) {
        for (auto &keyword : keywords) {
            // TODO: find only "name"? or include "description"?
            // TODO: getName function or other names...
            if (recipe.getName().find(keyword) != string::npos)
                // recipe.getDescription().find(keyword) != string::npos)
                result.push_back(recipe);
            break;
        }
    }

    return result;
}

// Get a recipe by name
Recipe RecipeDatabase::getRecipe(const string &name) const {
    // Search for the recipe by name
    for (auto &recipe : m_recipes) {
        if (recipe.getName() == name)
            return recipe;
    }

    // Return an empty recipe if not found
    return Recipe();
}

// Add a recipe
void RecipeDatabase::addRecipe() {
    Recipe recipe;

    // TODO: Edit function
    recipe.edit();
    m_recipes.push_back(recipe);
}

// Remove a recipe (by name)
void RecipeDatabase::removeRecipe(const string &name) {
    m_recipes.remove_if([&name](const Recipe &recipe) {
        return recipe.getName() == name;
    });
}

// Remove a recipe (by object)
void RecipeDatabase::removeRecipe(const Recipe &recipe) {
    m_recipes.remove(recipe);
}

// Destructor automatically saves the database to the file
RecipeDatabase::~RecipeDatabase() {
    // Open the recipe database file
    if (m_dbFile.open(m_dbPath / recipeFileName, ios::out | ios::binary);
        !m_dbFile.is_open())
        return;

    // Write the recipes to the file
    for (auto &recipe : m_recipes)
        m_dbFile.write(reinterpret_cast<char *>(&recipe), sizeof(Recipe));
    m_dbFile.close();

#ifdef SAVE_MEAL
    // Open the meal database file
    if (m_dbFile.open(m_dbPath / mealFileName, ios::out | ios::binary);
        !m_dbFile.is_open())
        return;

    // Write the meals to the file
    for (auto &meal : m_meals)
        m_dbFile.write(reinterpret_cast<char *>(&meal), sizeof(Meal));
    m_dbFile.close();
#endif
}