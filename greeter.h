/**
 *
 * greeter.h
 *
 * @author: Na Sunwoo@CSE-23 (@karu-rress)
 * @brief: Greeter/UI class for IIKH
 * @version: 0.1
 *
 */

#ifndef _GREETER_H_
#define _GREETER_H_

#include "plan_manager.h"
#include "recipe_db.h"

// Options for the user
enum class Option {
    SearchRecipes = 1,
    AddNewRecipe,
    EditRecipe,
    ReviewPlans,
    CreateNewPlan,
    Quit,
};

enum class OS {
    Windows,
    macOS,
    Linux,
};

class PlanManager;
class RecipeDatabase;

// Greeter class for IIKH
class Greeter {
public:
    Greeter(PlanManager &pm, RecipeDatabase &db);
    void run();

private:
    static inline PlanManager *planManager = nullptr;
    static inline RecipeDatabase *recipeDatabase = nullptr;

#if WIN32 || _WIN32 || __WIN32__
    static constexpr OS os = OS::Windows;
#elif __APPLE__
    static constexpr OS os = OS::macOS;
#elif __linux__
    static constexpr OS os = OS::Linux;
#endif

    void printInitialMessage();
    void printMenu();
    [[nodiscard]] Option getUserOption();

    void clearScreen();
};

#endif