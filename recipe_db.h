#ifndef _RECIPE_DB_H_
#define _RECIPE_DB_H_

#include <filesystem>
#include <fstream>
#include <map>
#include <string_view>

#include "meal.h"
#include "recipe.h"

using namespace std::literals;

class RecipeDatabase {
public:
    RecipeDatabase();

private:
    // RecipeDatabase는 Recipe와 Meal 딕셔너리를 관리한다.
    std::map<std::string, Recipe> m_recipes;
    std::map<std::string, Meal> m_meals;

    // TODO: 수정
    constexpr static inline char* recipeFileName = "recipe.db";
    constexpr static inline char* mealFileName = "meal.db";

    // 이게 필요...한가?
    std::filesystem::path m_dbPath;
    std::fstream m_dbFile;
};

RecipeDatabase::RecipeDatabase() {
}

#endif