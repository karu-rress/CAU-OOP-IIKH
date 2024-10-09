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
#include <string_view>

#include "greeter.h"

Greeter::Greeter(PlanManager &pm, RecipeDatabase &db) {
    planManager = &pm;
    recipeDatabase = &db;
}

void Greeter::run() {
    while (true) {
        printInitialMessage();

        switch (Option option = getUserOption(); option) {
        case Option::SearchRecipes:
            recipeDatabase->searchRecipes();
            break;
        case Option::AddNewRecipe:
            recipeDatabase->addNewRecipe();
            break;
        case Option::EditRecipe:
            recipeDatabase->editRecipe();
            break;
        case Option::ShowPlans:
            planManager->showPlans();
            break;
        case Option::CreateNewPlan:
            planManager->createNewPlan();
            break;
        case Option::Quit:
            exit(0);
        }
    }
}

RecipeDatabase &Greeter::getRecipeDatabase() {
    return *recipeDatabase;
}

void Greeter::printInitialMessage() {
    std::string_view logo = R"(
    ..                                                     
   .= .+==:                                                
   -      :-.:-::                                          
  ..         .--  ..=:                                     
  =              .-:    :--.                               
    .+                +.     -:                            
        :-.              :-.    :-:                        
            -:.              =:.    .=.                    
               .-:              .--    .:-                 
                 .:+-.           :   .=:.. .=:.            
            .=-:-:.:= .:=.      .=        .:-- :-.         
      .:-+. -:..-: :-. -:..-:.  -               .=:=-.     
  =-.= ..=..-- .=...=..-- .-: .+:                    ..+:  
  = .-: --..-:..-: :-. --..-:.:-: .--::                .:  
  =     .+. --  =: .+  --  =: .+. :=     :+.           -   
  =        .-: .-: :-..--..-: :-:.--..-:      :--:    -.   
  =             =...=. --. =...=. :=. =:..=.        -+:    
  =                :-..:-..-- :-:.:- .:- .-: :-.--:.  :    
  =                    --..=:..=. :-. =:..+=-.        :    
  =                       .-- .-..:=.=-:.             :    
  =.                          .=--                    :    
    .-:                        :                      :    
        :-.                    :                      :    
           .--                 :                      :    
               .-:             :                     -:    
                   .+.         :              ..=+.        
                       :-.     :          :-:.             
                           =:. :   ..-=.                   
                              .=-:.                        
)";

    std::cout << logo << "\n\n";
    std::cout << "================ IIKH ================\n";
    std::cout << "Welcome to IIKH, the Interactive Intelligent Kitchen Helper\n";
    std::cout << "Press Return to begin\n";
    std::cin.ignore();

    std::cout << "Please select an option:" << std::endl;

    std::cout << "1. Search recipes\n"
              << "2. Add a new recipe\n"
              << "3. Edit a recipe\n"
              << "4. Review meal plans\n"
              << "5. Create a new meal plan\n"
              << "6. Quit" << std::endl;
}

Option Greeter::getUserOption() {
    int option;

    while (true) {
        switch (option) {
        case 1:
            return Option::SearchRecipes;
        case 2:
            return Option::AddNewRecipe;
        case 3:
            return Option::EditRecipe;
        case 4:
            return Option::ShowPlans;
        case 5:
            return Option::CreateNewPlan;
        case 6:
            return Option::Quit;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
        }
    }
}