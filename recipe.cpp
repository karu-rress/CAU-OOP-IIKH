#include "recipe.h"
#include <iostream>
#include <sstream>

// Recipe 생성자: 레시피 이름, 재료, 조리 방법, 준비 시간을 초기화
Recipe::Recipe(std::string n, std::vector<std::pair<std::string, int>> ingr, std::string instr, int time)
    : name(n), ingredients(ingr), instructions(instr), prepTime(time) {}

// 레시피 이름을 반환하는 메서드
std::string Recipe::getName() const {
    return name;
}

// 조리 방법을 반환하는 메서드
std::string Recipe::getInstruction() const {
    return instructions;
}

// 재료를 반환하는 메서드
std::vector<std::pair<std::string, int>> Recipe::getIngredients() const {
    return ingredients;
}

// 준비 시간을 반환하는 메서드
int Recipe::getPrepTime() const {
    return prepTime;
}

// 레시피를 한 번에 수정하는 메서드 (재료와 조리법 모두 수정)
void Recipe::edit() {
    std::cout << "Editing Recipe: " << name << std::endl;
    
    // 새로운 조리법 입력
    std::string newInstruction;
    std::cout << "Enter new instruction: ";
    std::getline(std::cin, newInstruction);  // 사용자로부터 새로운 조리법 입력
    instructions = newInstruction;
    
    // 새로운 재료 입력
    std::string newIngredientsStr;
    std::cout << "Enter new ingredients (format: name quantity, separated by comma): ";
    std::getline(std::cin, newIngredientsStr);  // 사용자로부터 새로운 재료 입력

    // 기존 재료 초기화 및 새로운 재료 리스트 업데이트
    ingredients.clear();
    std::stringstream ss(newIngredientsStr);
    std::string ingredient;
    while (std::getline(ss, ingredient, ',')) {
        std::stringstream item(ingredient);
        std::string name;
        int quantity;

        // "재료 이름"과 "양"을 쉼표로 구분하여 읽음
        if (item >> name >> quantity) {
            ingredients.push_back(std::make_pair(name, quantity));
        }
    }

    // 준비 시간 수정
    std::cout << "Enter preparation time (minutes): ";
    std::cin >> prepTime;
    std::cin.ignore(); // 버퍼 비우기
}

// 재료 양을 인분 수에 맞춰 조정하는 메서드
void Recipe::adjustForServings(int servings) {
    for (auto& ingredient : ingredients) {
        ingredient.second *= servings;  // 인분 수에 따라 재료 양 조정 (정수형 그람 단위)
    }
}

// 레시피 정보를 출력하는 메서드
void Recipe::displayRecipe() const {
    std::cout << "Recipe Name: " << name << "\n";
    std::cout << "Preparation Time: " << prepTime << " minutes\n";
    std::cout << "Ingredients: \n";
    for (const auto& ingredient : ingredients) {
        std::cout << ingredient.first << ": " << ingredient.second << "g\n";  // 재료 목록과 그람(g) 단위 출력
    }
    std::cout << "Instructions: " << instructions << "\n";  // 조리 방법 출력
}
