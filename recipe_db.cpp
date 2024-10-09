/**
 *
 * recipe_db.cpp
 *
 * @author: Na Sunwoo@CSE-23 (@karu-rress)
 * @brief: Recipe와 Meal을 관리하는 데이터베이스 Wrapper
 * @version: 0.1
 *
 */

#include <algorithm>
#include <iostream>
#include <iterator>

#include "recipe_db.h"

// namespace alias for std::filesystem
namespace fs = std::filesystem;
using namespace std;

// Initialize the RecipeDatabase
RecipeDatabase::RecipeDatabase() {
    // Get the path to the database file
    // If directory doesn't exist, return
    if (dbPath = fs::current_path() / "data"; fs::exists(dbPath) == false)
        return;

    // Open the recipe database file
    if (dbFile.open(dbPath / recipeFileName, ios::in | ios::binary);
        !dbFile.is_open())
        return;

    // Read the recipes from the file
    while (dbFile.eof() == false) {
        Recipe recipe;
        dbFile.read(reinterpret_cast<char *>(&recipe), sizeof(Recipe));
        recipes.push_back(recipe);
    }
    dbFile.close();
}

// Destructor automatically saves the database to the file
RecipeDatabase::~RecipeDatabase() {
    // Open the recipe database file
    if (dbFile.open(dbPath / recipeFileName, ios::out | ios::binary);
        !dbFile.is_open())
        return;

    // Write the recipes to the file
    for (auto &recipe : recipes)
        dbFile.write(reinterpret_cast<char *>(&recipe), sizeof(Recipe));
    dbFile.close();
}

// Search recipes by keyword
list<Recipe> RecipeDatabase::searchRecipes() const {
    cout << "Input keywords (separated by spaces): ";

    // Get the keywords from the user
    string input;
    getline(cin, input);
    istringstream iss(input);

    // istream_iterator automatically splits the input by spaces
    vector<string> keywords((istream_iterator<string>(iss)),
        istream_iterator<string>());

    list<Recipe> result;

    // Search for the keyword in the recipe list
    for (const auto &recipe : recipes) {
        bool allKeywordsFound = true;

        for (const auto &keyword : keywords) {
            bool nameFound = recipe.getName().find(keyword) != string::npos;
            bool instructionFound = recipe.getInstructions().find(keyword) != string::npos;
            bool ingredientsFound = [recipe, keyword] {
                for (const auto &[name, _] : recipe.getIngredients())
                    if (name == keyword)
                        return true;
                return false;
            }();

            if (!nameFound && !ingredientsFound && !instructionFound) {
                allKeywordsFound = false;
                break;
            }
        }

        // If all keywords are found, add the recipe to the result list
        if (allKeywordsFound)
            result.push_back(recipe);
    }

    return result;
}

// Get a recipe by name
Recipe RecipeDatabase::getRecipe(const string &name) const {
    // Search for the recipe by name
    for (auto &recipe : recipes) {
        if (recipe.getName() == name)
            return recipe;
    }

    // Return an empty recipe if not found
    return Recipe();
}

// Operator overloading for []
Recipe &RecipeDatabase::operator[](const string &name) {
    for (auto &recipe : recipes) {
        if (recipe.getName() == name)
            return recipe;
    }

    // If the recipe is not found, add a new recipe
    Recipe recipe(name);
    recipes.push_back(recipe);
    return recipes.back();
}

Recipe RecipeDatabase::operator[](const string &name) const {
    return getRecipe(name);
}

// Add a recipe
void RecipeDatabase::addNewRecipe() {
    Recipe recipe;

    recipe.edit();
    recipes.push_back(recipe);
}

// TODO: check if this works
void RecipeDatabase::editRecipe() {
    // Get the recipe name from the user
    cout << "Enter the name of the recipe to edit: ";
    string name;
    cin >> name;

    // Get the recipe by name and edit it
    Recipe &recipe = (*this)[name];
    recipe.edit();
}

// Remove a recipe (by name)
void RecipeDatabase::removeRecipe(const string &name) {
    recipes.remove_if([&name](const Recipe &recipe) {
        return recipe.getName() == name;
    });
}

// Remove a recipe (by object)
void RecipeDatabase::removeRecipe(const Recipe &recipe) {
    recipes.remove(recipe);
}

