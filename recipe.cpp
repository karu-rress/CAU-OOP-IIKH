#include "recipe.h"
#include <iostream>
#include <sstream>

// Recipe constructor: initialize recipe name, ingredients, instruction, preparation time
Recipe::Recipe(std::string n,
    std::vector<std::pair<std::string, int>> ingr, std::string instr, int time)
    : name(n)
    , ingredients(ingr)
    , instructions(instr)
    , prepTime(time) { }

// Get name method
std::string Recipe::getName() const {
    return name;
}

// Get ingredients method
std::vector<std::pair<std::string, int>> Recipe::getIngredients() const {
    return ingredients;
}

// Get instruction method
std::string Recipe::getInstruction() const {
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
    std::string newIngredientsStr;
    std::cout << "Enter ingredients (e.g. egg 100, flour 300, ...): ";
    std::getline(std::cin, newIngredientsStr);

    // clear original and update new ingredients
    ingredients.clear();
    std::stringstream ss(newIngredientsStr);
    std::string ingredient;
    while (std::getline(ss, ingredient, ',')) {
        std::stringstream item(ingredient);
        std::string name;
        int quantity;

        if (item >> name >> quantity) {
            ingredients.push_back(std::make_pair(name, quantity));
        }
    }

    // input new instruction
    std::string newInstruction;
    std::cout << "Enter instruction: ";
    std::getline(std::cin, newInstruction);
    instructions = newInstruction;

    // input new preptime
    std::cout << "Enter preparation time (minutes): ";
    std::cin >> prepTime;
    std::cin.ignore();
}

// Adjust for servings method
void Recipe::adjustForServings(int servings) {
    for (auto &ingredient : ingredients) {
        ingredient.second *= servings;
    }
}

// Display method
void Recipe::displayRecipe() const {
    std::cout << "Recipe Name: " << name << "\n";
    std::cout << "Ingredients: \n";
    for (const auto &ingredient : ingredients) {
        std::cout << ingredient.first << ": " << ingredient.second << "g\n";
    }
    std::cout << "Instructions: " << instructions << "\n";
    std::cout << "Preparation Time: " << prepTime << " minutes\n";
}
