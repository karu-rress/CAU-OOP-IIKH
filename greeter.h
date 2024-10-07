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

enum class Option {
    BrowseRecipe,
    AddRecipe,
    EditRecipe,
    ReviewPlan,
    CreatePlan,
    Quit,
};

class Greeter {
public:
    Greeter(PlanManager &pm, RecipeDatabase &rdb);
    void run();

private:
    PlanManager &planManager;
    RecipeDatabase &recipeDatabase;
    
    void printInitialMessage();
    Option getUserOption();
};

#endif