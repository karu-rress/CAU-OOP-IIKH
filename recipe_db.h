#ifndef _RECIPE_DB_H_
#define _RECIPE_DB_H_

#include <fstream>
#include <filesystem>
#include <string_view>
#include <map>

#include "recipe.h"
#include "meal.h"

using namespace std::literals;

class RecipeDatabase
{
public:
    RecipeDatabase();

private:
    // RecipeDatabase는 Recipe와 Meal 딕셔너리를 관리한다.
    std::map<std::string, Recipe> m_recipes;
    std::map<std::string, Meal> m_meals;

    // TODO: 수정
    constexpr static inline char *recipeFileName = "recipe.db";
    constexpr static inline char *mealFileName = "meal.db";

    // 이게 필요...한가?
    std::filesystem::path m_dbPath;
    std::fstream m_dbFile;
};

RecipeDatabase::RecipeDatabase()
{
}

#endif