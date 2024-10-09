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

Greeter::Greeter(PlanManager &pm, RecipeDatabase &rdb)
    : planManager(pm)
    , recipeDatabase(rdb) {
}

void Greeter::run() {
    while (true) {
        printInitialMessage();

        switch (Option option = getUserOption(); option) {
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
        switch (std::cin >> option; option) {
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
        }
    }
}