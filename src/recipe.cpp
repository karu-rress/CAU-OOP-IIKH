#include <format>
#include <iostream>
#include <limits>
#include <sstream>

#include "../include/recipe.h"

// Recipe constructor: initialize recipe name, ingredients, instruction, preparation time
Recipe::Recipe(std::string n)
    : name(n)
    , ingredients()
    , instructions("")
    , prepTime(0) { }

Recipe::Recipe(std::string n, std::map<std::string, int> ingr, std::string instr, int time)
    : name(n)
    , ingredients(ingr)
    , instructions(instr)
    , prepTime(time) { }

// Get name method
[[nodiscard]] std::string Recipe::getName() const {
    return name;
}

// Get ingredients method
[[nodiscard]] std::map<std::string, int> Recipe::getIngredients() const {
    return ingredients;
}

// Get instruction method
[[nodiscard]] std::string Recipe::getInstructions() const {
    return instructions;
}

// Get preptime method
[[nodiscard]] int Recipe::getPrepTime() const {
    return prepTime;
}

// Edit method
void Recipe::edit() {
    ingredients.clear();

    // input new ingredients
    std::cout << "Enter ingredients (format: egg 100 flour 200 ...): ";

    std::string line;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, line);

    std::istringstream iss(line);

    std::string name;
    int quantity;

    while (iss >> name >> quantity) {
        ingredients[name] = quantity;
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
    std::cout << "  Ingredients: \n";
    for (const auto &[name, quantity] : ingredients) {
        std::cout << std::format("    {}: {}g\n", name, quantity);
    }
    std::cout << std::format("  Instructions: {}\n", instructions);
    std::cout << std::format("  Preparation Time: {} minutes\n", prepTime);
}