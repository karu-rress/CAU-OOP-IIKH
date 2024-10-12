/**
 *
 * plan_manager.cpp
 *
 *
 * @author: 권정주
 * @brief: Plan의 데이터를 저장 및 호출하는 기능들 - 저장 형태는 하단의 plan_txt 예시 참고.
 *
 * @method: showPlans() - plan.txt에 저장되어있는 date, meal(레시피들), servings 읽기
 *                        date는 Date 클래스에게 위임.
 *                        meal과 servings는 Meal 클래스에게 위임.
 *          createNewPlan() - year, month, day 입력받기
 *                          - Date 클래스에게 위임.
 *                          - newDate의 date, meal, servings를 plan.txt에 추가.
 * @plan_txt: user가 생성한 plan을 저장해놓는 txt 파일.
 *            년 월 일 meal servings 순으로 저장.
 *            e.g.
 *            2024 10 24 curry noodle kimbop 3
 *            2024 12 25 cake maratang 2
 *
 *
 */

#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <vector>

#include "plan_manager.h"
#include "recipe.h"

using namespace std;
namespace fs = std::filesystem;

// Reads plans from the file
PlanManager::PlanManager() {
    if (planPath = fs::current_path() / "data"; !fs::exists(planPath))
        return;

    // Open the plans file
    if (planFile.open(planPath / planFileName, ios::in);
        !planFile.is_open())
        return;

    // Read the plans from the file
    std::string line;

    std::regex dateRegex(R"((\d{4}-\d{2}-\d{2}))");
    std::regex memoRegex(R"(\$\#(.*?)\#\$)");
    std::regex entryRegex(R"(\[(.*?)\]=\{([^}]+)\})");
    std::regex itemRegex(R"(([^,]+))");

    while (std::getline(planFile, line)) {
        // Regex to match date
        std::smatch dateMatch, memoMatch;
        regex_search(line, dateMatch, dateRegex);
        regex_search(line, memoMatch, memoRegex);

        std::string memo;
        if (memoMatch.size() > 1) {
            memo = memoMatch[1].str();
        }
        Date date(dateMatch[1].str(), memo);

        std::sregex_iterator entryBegin(line.cbegin(), line.cend(), entryRegex);
        std::sregex_iterator entryEnd;
        std::list<Meal> meals;

        for (auto entryIt = entryBegin; entryIt != entryEnd; ++entryIt) {
            // Meal 매칭
            std::string mealName = (*entryIt)[1].str();
            std::string items = (*entryIt)[2].str();

            std::list<Recipe> recipes;
            int servings { 1 };

            std::sregex_iterator itemBegin(items.cbegin(), items.cend(), itemRegex);
            std::sregex_iterator itemEnd;

            for (auto it = itemBegin; it != itemEnd; ++it) {
                // Recipe 매칭
                std::string item = (*it).str();

                // Check if the item is a number
                if (isdigit(item[0])) {
                    servings = std::stoi(item);
                    // recipes.clear();
                    break;
                }
                else {
                    recipes.push_back(item);
                }
            }
            meals.emplace_back(mealName, servings, recipes);
            recipes.clear();
        }

        plans[date] = meals;
    }

    planFile.close();
}

PlanManager::~PlanManager() {
    // Create directory
    if (planPath = fs::current_path() / "data"; !fs::exists(planPath))
        fs::create_directory(planPath);

    // Open the plans file
    if (planFile.open(planPath / planFileName, std::ios::out);
        !planFile.is_open()) {
        std::cerr << "file open failed." << std::endl;
        return;
    }

    for (const auto &[date, meals] : plans) {
        planFile << date.getDateAsString() << " ";

        if (!date.getMemo().empty())
            planFile << format("$#{}#$ ", date.getMemo());

        for (const Meal &meal : meals) {
            planFile << format("[{}]={{", meal.getName());
            for (const Recipe &recipe : meal.getRecipes()) {
                planFile << format("{},", recipe.getName());
            }
            planFile << format("{}}}, ", meal.getServings());
        }
        planFile << endl;
    }

    planFile.close();
}

void PlanManager::reviewPlans() {
    auto newPlan(plans);

    // iterate plans and modify
    for (auto &[oldDate, meal] : plans) {
        Date newDate = oldDate;
        newDate.displayAndEdit();

        for (Meal &m : meal) {
            m.displayMealInfo();

            cout << "Ingredients: \n";
            for (const auto &[name, quantity] : m.getGroceryList()) {
                cout << name << " (" << quantity << "g)\n";
            }

            cout << "If you want to edit meal, type either 1 or 2:\n"
                 << "1. add recipe from meal\n"
                 << "2. remove recipe from meal\n"
                 << "3. quit\n"
                 << endl;

            int selection;
            cin >> selection;

            if (selection == 1) { // add recipe from meal
                Recipe newRecipe;
                newRecipe.edit();
                m.addRecipe(newRecipe);
            }
            else if (selection == 2) { // remove recipe from meal
                string recipeToRemove;
                cout << "Enter the name of the recipe to remove: ";
                cin >> recipeToRemove;
                m.removeRecipe(recipeToRemove);
            }
            else {
                break; // go to next meal (or return to main menu)
            }

            newPlan[newDate] = meal;
        }

        plans = newPlan;
        return;
    }
}

void PlanManager::createNewPlan() {
    cout << "Enter the date to make your plan (YYYY-MM-DD) : ";
    string date;
    cin >> date;
    Date newDate(date);
    newDate.displayAndEdit();
    newDate.manageMeals();

    std::list<Meal> mealList = newDate.getMeals();
    plans[newDate] = mealList;

    return;
}
