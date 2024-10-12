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

    Meal::setRecipeDatabase(recipeDatabase);
}

void Greeter::run() {
    try {
        printInitialMessage();

        while (true) {
            clearScreen();
            PrintMenu();

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
            case Option::ReviewPlans:
                planManager->reviewPlans();
                break;
            case Option::CreateNewPlan:
                planManager->createNewPlan();
                break;
            case Option::Quit:
                return;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }
}

void Greeter::printInitialMessage() {
    constexpr std::string_view logo = R"(
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
    std::cout << "=================== IIKH ===================\n";
    std::cout << "Welcome to IIKH, the Interactive Intelligent Kitchen Helper\n\n";
    std::cout << "Press Return to begin\n";
    std::cin.get();
}

void Greeter::PrintMenu() {
    std::cout << "Please select an option\n\n";

    std::cout << "  1. Search recipes\n"
              << "  2. Add a new recipe\n"
              << "  3. Edit a recipe\n"
              << "  4. Review meal plans\n"
              << "  5. Create a new meal plan\n"
              << "  6. Quit\n\n"
              << "Input > ";
}

Option Greeter::getUserOption() {
    int option;

    while (true) {
        std::cin >> option;
        if (!std::cin) {
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (option) {
        case 1:
            return Option::SearchRecipes;
        case 2:
            return Option::AddNewRecipe;
        case 3:
            return Option::EditRecipe;
        case 4:
            return Option::ReviewPlans;
        case 5:
            return Option::CreateNewPlan;
        case 6:
            return Option::Quit;
        default:
            std::cout << "Invalid option. Please try again.\n\n"
                      << "Input > ";
        }
    }
}

void Greeter::clearScreen() {
    if constexpr (os == OS::Windows) {
        system("cls");
    }
    else {
        system("clear");
    }
}
