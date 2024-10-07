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

// TODO: 레시피는 저장하는 게 아닌가...?
// 일단 Recipe만 저장하는 것 같고...
// Meal은 오히려 RecipeDB를 이용하여 조회하는 등 해야 함.

#define SAVE_MEAL

// Stores recipes and meals
class RecipeDatabase {
public:
    RecipeDatabase();

    // Search recipes by keyword
    std::list<Recipe> searchRecipes(const std::vector<std::string> &keywords) const;

    // Get a recipe by name
    // TODO: 직접 파고 들어가서 수정할 건지,
    // 아니면 지우고 새로운 걸 삽입할 건지.
    Recipe &getRecipe(const std::string &name);
    Recipe getRecipe(const std::string &name) const;

    // Add a recipe
    void addRecipe();

    // Edit a recipe
    void editRecipe(const std::string &name);

    // Remove a recipe
    void removeRecipe(const std::string &name);
    void removeRecipe(const Recipe &name);

    // Destructor automatically saves the database to the file
    ~RecipeDatabase();

private:
    // Lists storing recipes and meals
    //   Not using std::vector <- don't need std::random_access_iterator
    //   Not using std::map <- The name(key) is already stored in each class
    std::list<Recipe> m_recipes;

    // TODO: 수정
    constexpr static inline char *recipeFileName = "recipe.db";

    // Database file names
    // 'constexpr' allows this variable to be evaluated at compile time
    // If a variable is 'constexpr', it automatically becomes 'inline'
    static constexpr inline std::string_view recipeFileName = "recipe.db";

#ifdef SAVE_MEAL
    static constexpr inline std::string_view mealFileName = "meal.db";
#endif

    // stores path & file stream
    std::filesystem::path m_dbPath;
    std::fstream m_dbFile;
};

#endif