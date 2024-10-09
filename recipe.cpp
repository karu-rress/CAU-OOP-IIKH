#include <iostream>

#include "recipe.h"

// Recipe constructor: initialize recipe name, ingredients, instruction, preparation time
Recipe::Recipe(std::string n, std::map<std::string, int> ingr, std::string instr, int time)
    : name(n)
    , ingredients(ingr)
    , instructions(instr)
    , prepTime(time) { }

// Get name method
std::string Recipe::getName() const {
    return name;
}

// Get ingredients method
std::map<std::string, int> Recipe::getIngredients() const {
    return ingredients;
}

// Get instruction method
std::string Recipe::getInstructions() const {
    return instructions;
}

// Get preptime method
int Recipe::getPrepTime() const {
    return prepTime;
}

// Edit method
void Recipe::edit() {
    std::cout << "Editing Recipe: " << name << std::endl;

    // input new ingredients
    std::cout << "Enter ingredients (format: egg 100 flour 200 ...): ";

    ingredients.clear();
    std::string name;
    int quantity;

    while (std::cin >> name >> quantity) {
        ingredients[name] = quantity;
        if (std::cin.peek() == '\n') {
            std::cin.ignore();
            break;
        }
    }

    // input new instruction
    std::cout << "Enter instruction: ";
    std::getline(std::cin, instructions);

    // input new preptime
    std::cout << "Enter preparation time (minutes): ";
    std::cin >> prepTime;
    std::cin.ignore();
}

// Display method
void Recipe::displayRecipe() const {
    std::cout << "Recipe Name: " << name << "\n";
    std::cout << "Ingredients: \n";
    for (const auto &[name, quantity] : ingredients) {
        std::cout << "\t" << name << ": " << quantity << "g\n";
    }
    std::cout << "Instructions: " << instructions << "\n";
    std::cout << "Preparation Time: " << prepTime << " minutes\n";
}