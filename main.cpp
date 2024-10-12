/**
 *
 * main.cpp
 *
 * @author: Na Sunwoo@CSE-23 (@karu-rress)
 * @brief: Entry point of IIKH program
 * @version: 1.0
 *
 */

// include user-defined libraries
#include "greeter.h"
#include "plan_manager.h"
#include "recipe_db.h"

#include <iostream>

int main() {
    // Initialize the plan manager and recipe database
    RecipeDatabase recipeDB;
    Meal::setRecipeDatabase(&recipeDB);
    PlanManager planManager;

    // Initialize the greeter and connect
    // to the plan manager and recipe database
    Greeter greeter(planManager, recipeDB);

    try {
        // Run the greeter
        greeter.run();
    } catch (const std::exception &e) {
        std::cerr << "An error has occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error has occurred." << std::endl;
    }

    return 0;
}