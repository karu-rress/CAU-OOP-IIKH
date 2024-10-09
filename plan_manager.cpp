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

#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <vector>

#include "plan_manager.h"

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
    std::regex entryRegex(R"(\[(.*?)\]={([^}]+)})");
    std::regex itemRegex(R"(([^,]+))");

    while (std::getline(planFile, line)) {
        // Regex to match date
        std::smatch dateMatch;
        regex_search(line, dateMatch, dateRegex);
        Date date(dateMatch[1].str());

        // Regex to match entries
        std::smatch entryMatch;
        std::list<Meal> meals;

        while (std::regex_search(line.cbegin(), line.cend(), entryMatch, entryRegex)) {
            // Meal 매칭
            std::string mealName = entryMatch[1].str();
            std::string items = entryMatch[2].str();

            std::list<Recipe> recipes;
            std::sregex_iterator itemBegin(items.cbegin(), items.cend(), itemRegex);
            std::sregex_iterator itemEnd;

            for (auto it = itemBegin; it != itemEnd; ++it) {
                // Recipe 매칭
                std::string item = (*it).str();

                // Check if the item is a number
                if (isdigit(item[0])) {
                    int servings = std::stoi(item);
                    meals.emplace_back(mealName, servings, recipes);
                    recipes.clear();
                    break;
                }
                else {
                    recipes.push_back(item);
                }
            }
        }

        plans[date] = meals;
    }

    planFile.close();
}

PlanManager::~PlanManager() {
    // Open the plans file
    if (planFile.open(planPath / planFileName, std::ios::out);
        !planFile.is_open()) {
        std::cerr << "file open failed." << std::endl;
        return;
    }

    for (const auto &[date, meals] : plans) {
        planFile << date.getDateAsString() << " ";

        for (const Meal &meal : meals) {
            planFile << "[" << meal.getName() << "]={";

            for (const Recipe &recipe : meal.getRecipes()) {
                planFile << recipe.getName() << ",";
            }

            planFile << meal.getServings() << "}, ";
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
        meal.displayMealInfo();
        meal.getGroceryList();

        newPlan[newDate] = meal;
    }

    plans = newPlan;
    return;
}

void PlanManager::createNewPlan() {
    int year, month, day;

    cout << "Enter the date to make your plan like this format(2024 10 01) : ";
    cin >> year >> month >> day;

    Date newDate(year, month, day); // 입력받은 날짜로 Date 인스턴스 생성.
    newDate.displayAndEdit(); // Date에게 control 위임.

    std::list<Meal> mealList;
    std::list<std::string> mealNames;
    newDate.manageMealList(mealNames); // manageMealList()가 list<string>을 argument로 받음.
    plans[newDate] = mealList;

    return;
}
