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
        m_dbFile.read(reinterpret_cast<char*>(&recipe), sizeof(Recipe));
        m_recipes.push_back(recipe);
    }
    m_dbFile.close();

    // Open the meal database file
    if (m_dbFile.open(m_dbPath / mealFileName, ios::in | ios::binary);
        !m_dbFile.is_open())
        return;

    // Read the meals from the file
    while (m_dbFile.eof() == false) {
        Meal meal;
        m_dbFile.read(reinterpret_cast<char*>(&meal), sizeof(Meal));
        m_meals.push_back(meal);
    }
}