/**
 *
 * recipe_db.h
 *
 * @author: Na Sunwoo@CSE-23 (@karu-rress)
 * @brief: Recipe와 Meal을 관리하는 데이터베이스 Wrapper
 * @version: 0.1
 *
 */

#ifndef _RECIPE_DB_H_
#define _RECIPE_DB_H_

// importing standard libraries
#include <filesystem>
#include <fstream>
#include <list>
#include <string_view>
#include <vector>

// importing user-defined libraries
#include "meal.h"
#include "recipe.h"

// Stores recipes and meals
class RecipeDatabase {
public:
    RecipeDatabase();

    // Search recipes by keyword
    std::list<Recipe> searchRecipes() const;

    // Get a recipe by name
    Recipe getRecipe(const std::string &name) const;

    // Operator overloading for []
    Recipe &operator[](const std::string &name) noexcept(false);
    Recipe operator[](const std::string &name) const;

    // Add a recipe
    void addRecipe();

    // Edit a recipe
    void editRecipe();

    // Remove a recipe
    void removeRecipe(const std::string &name);
    void removeRecipe(const Recipe &name);

    // Destructor automatically saves the database to the file
    ~RecipeDatabase();

private:
    // Lists storing recipes and meals
    //   Not using std::vector <- don't need std::random_access_iterator
    //   Not using std::map <- The name(key) is already stored in each class
    std::list<Recipe> recipes;

    // Database file names
    // 'constexpr' allows this variable to be evaluated at compile time
    // If a variable is 'constexpr', it automatically becomes 'inline'
    static constexpr inline std::string_view recipeFileName = "recipe.db";

    // stores path & file stream
    std::filesystem::path dbPath;
    std::fstream dbFile;
};

#endif