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
    Greeter(PlanManager &planManager, RecipeDatabase &recipeDatabase);

    void run();

    void printInitialMessage();

    Option getUserOption();

private:
    PlanManager &planManager;
    RecipeDatabase &recipeDatabase;
};


#endif