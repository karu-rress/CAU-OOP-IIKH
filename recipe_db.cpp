/**
 *
 * recipe_db.cpp
 *
 * @author: Na Sunwoo@CSE-23 (@karu-rress)
 * @brief: Recipe와 Meal을 관리하는 데이터베이스 Wrapper
 * @version: 1.0
 *
 */

#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>

#include "recipe_db.h"

// namespace alias for std::filesystem
namespace fs = std::filesystem;
using namespace std;

// Initialize the RecipeDatabase
RecipeDatabase::RecipeDatabase() {
    // Get the path to the database file
    // If directory doesn't exist, return
    if (dbPath = fs::current_path() / "data"; !fs::exists(dbPath))
        return;

    // Open the recipe database file
    if (dbFile.open(dbPath / recipeFileName, ios::in);
        !dbFile.is_open())
        return;

    // Read the recipes from the file
    string name;
    map<string, int> ingredients;
    string instructions;

    string ingredientName;
    int quantity;

    // read lines from file
    string line;
    while (getline(dbFile, name)) {
        getline(dbFile, line);
        istringstream iss(line);
        while (iss >> ingredientName >> quantity)
            ingredients[ingredientName] = quantity;

        getline(dbFile, instructions);
        getline(dbFile, line);

        recipes.emplace_back(name, ingredients, instructions, stoi(line));
        ingredients.clear();
    }

    dbFile.close();
}

// Destructor automatically saves the database to the file
RecipeDatabase::~RecipeDatabase() {
    // Create directory if not exists
    if (dbPath = fs::current_path() / "data"; !fs::exists(dbPath))
        fs::create_directory(dbPath);

    // Open the recipe database file
    if (dbFile.open(dbPath / recipeFileName, ios::out);
        !dbFile.is_open())
        return;

    // Write the recipes to the file
    for (auto &recipe : recipes) {
        dbFile << recipe.getName() << endl;
        for (const auto &[name, quantity] : recipe.getIngredients())
            dbFile << format("{} {}\n", name, quantity);
        dbFile << endl;
        dbFile << recipe.getInstructions() << endl;
        dbFile << recipe.getPrepTime() << endl;
    }
    dbFile.close();
}

// Search recipes by keyword
void RecipeDatabase::searchRecipes() const {
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

    if (result.empty()) {
        cout << "\nNo recipes found.\n";
    }
    else {
        cout << "\nSearch results:\n\n";
        for (const auto &recipe : result)
            recipe.displayRecipe();
    }

    cout << "\nPress Return to continue...";
    cin.get();
}

// Get a recipe by name
[[nodiscard]] Recipe RecipeDatabase::getRecipe(const string &name) const {
    // Search for the recipe by name
    for (auto &recipe : recipes) {
        if (recipe.getName() == name)
            return recipe;
    }

    // Return an empty recipe if not found
    return Recipe();
}

// Operator overloading for []
[[nodiscard]] Recipe &RecipeDatabase::operator[](const string &name) {
    for (auto &recipe : recipes) {
        if (recipe.getName() == name)
            return recipe;
    }

    // If the recipe is not found, add a new recipe
    Recipe recipe(name);
    recipes.push_back(recipe);
    return recipes.back();
}

[[nodiscard]] Recipe RecipeDatabase::operator[](const string &name) const {
    return getRecipe(name);
}

// Add a recipe
void RecipeDatabase::addNewRecipe() {
    cout << "Enter the new name of the recipe: ";

    string name;
    cin >> name;

    Recipe recipe(name);
    recipe.edit();
    recipes.push_back(recipe);

    cout << "\nRecipe added successfully.\n"
         << "Press Return to continue...";
    cin.ignore();
    cin.get();
}

void RecipeDatabase::editRecipe() {
    // Get the recipe name from the user
    cout << "Enter the name of the recipe to edit: ";

    string name;
    cin >> name;

    if (ranges::find_if(recipes, [&name](const Recipe &recipe) {
            return recipe.getName() == name;
        })
        == recipes.end()) {
        cout << "Recipe not found.\n"
             << "Press Return to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << format("Edit or remove the recipe '{}'\n\n", name);
    cout << "  1. Edit\n"
         << "  2. Remove\n"
         << "  3. Cancel\n\n"
         << "Enter your choice > ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {
        // Get the recipe by name and edit it
        Recipe &recipe = (*this)[name];
        recipe.edit();

        cout << "Recipe edited successfully.\n"
             << "Press Return to continue...";
        break;
    }
    case 2: {
        // Remove the recipe by name
        removeRecipe(name);

        cout << "Recipe removed successfully.\n"
             << "Press Return to continue...";
        break;
    }
    default:
        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Operation canceled.\n"
             << "Press Return to continue...";
        return;
    }

    cin.ignore();
    cin.get();
}

// Remove a recipe (by name)
void RecipeDatabase::removeRecipe(const string &name) {
    recipes.remove_if([&name](const Recipe &recipe) {
        return recipe.getName() == name;
    });
}
