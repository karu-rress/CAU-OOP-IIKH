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

// importing user-defined libraries
#include "meal.h"
#include "recipe.h"

// Stores recipes and meals
class RecipeDatabase {
public:
    RecipeDatabase();

    void action();
    
private:
    // Lists storing recipes and meals
    //   Not using std::vector <- don't need std::random_access_iterator
    //   Not using std::map <- The name(key) is already stored in each class
    std::list<Recipe> m_recipes;
    std::list<Meal> m_meals;

    // Database file names
    // 'static' allows this variable to be shared among all instances
    // 'constexpr' allows this variable to be evaluated at compile time
    // If a variable is 'constexpr', it automatically becomes 'inline'
    static constexpr inline std::string_view recipeFileName = "recipe.db";
    static constexpr inline std::string_view mealFileName = "meal.db";

    // stores path & file stream
    std::filesystem::path m_dbPath;
    std::fstream m_dbFile;
};

#endif