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
    ShowPlans,
    CreateNewPlan,
    Quit,
};

// Greeter class for IIKH
class Greeter {
public:
    Greeter(PlanManager &pm, RecipeDatabase &db);
    void run();

    static RecipeDatabase &getRecipeDatabase();

private:
    static inline PlanManager *planManager = nullptr;
    static inline RecipeDatabase *recipeDatabase = nullptr;
    
    void printInitialMessage();
    Option getUserOption();
};

#endif