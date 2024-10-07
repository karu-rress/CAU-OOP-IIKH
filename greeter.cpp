/**
 *
 * greeter.cpp
 *
 * @author: Na Sunwoo@CSE-23 (@karu-rress)
 * @brief: Greeter/UI class for IIKH
 * @version: 0.1
 *
 */

#include <iostream>

#include "greeter.h"

using namespace std;

Greeter::Greeter(PlanManager &pm, RecipeDatabase &rdb)
    : planManager(pm)
    , recipeDatabase(rdb) {
}

void Greeter::run() {
    printInitialMessage();
    Option option = getUserOption();

    switch (option) {
    case Option::BrowseRecipe:

        recipeDatabase.searchRecipes();
    case Option::AddRecipe:
        recipeDatabase.addRecipe();
        break;
    case Option::EditRecipe:
        recipeDatabase.editRecipe();
        break;
    case Option::ReviewPlan:
        planManager.showPlans();
        break;
    case Option::CreatePlan:
        planManager.createNewPlan();
        break;
    case Option::Quit:
        exit(0);
    }
}

void Greeter::printInitialMessage() {
    std::cout << "================ IIKH ================" << std::endl;
    std::cout << "Welcome to IIKH, the Interactive Intelligent Kitchen Helper" << std::endl
              << std::endl;
    std::cout << "Press Return to begin" << std::endl
              << std::endl;
    std::cout << "Please select an option:" << std::endl;

    /**
     * 1. Search recipes
    -Casually browse the database of existing recipes, but without reference to
    any particular meal plan.
    2. Add a new recipe
    -Add a new recipe to the database.
    3. Edit recipe
    -Edit or annotate an existing recipe.
    4. See existing meal plans or See exsting plans of meals
    -Review an existing plan for several meals.
    5. Create a new plan of meals or Create a new meal plan
    -Create a new plan of meals.
     */

    std::cout << "1. Search recipes" << std::endl;
    std::cout << "2. Add a new recipe" << std::endl;
    std::cout << "3. Edit a recipe" << std::endl;
    std::cout << "4. Review meal plans" << std::endl;
    std::cout << "5. Create a new meal plan" << std::endl;
    std::cout << "6. Quit" << std::endl;
}

Option Greeter::getUserOption() {
    int option;
    std::cin >> option;

    switch (option) {
    case 1:
        return Option::BrowseRecipe;
    case 2:
        return Option::AddRecipe;
    case 3:
        return Option::EditRecipe;
    case 4:
        return Option::ReviewPlan;
    case 5:
        return Option::CreatePlan;
    case 6:
        return Option::Quit;
    default:
        std::cout << "Invalid option. Please try again." << std::endl;
        return getUserOption();
    }
}