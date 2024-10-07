#include "greeter.h"
#include "plan_manager.h"
#include "recipe_db.h"

int main() {
    PlanManager planManager;
    RecipeDatabase recipeDB;
    Greeter greeter(planManager, recipeDB);

    greeter.run();

    return 0;
}