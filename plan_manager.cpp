/**
 *
 * plan_manager.h
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

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>

#include "date.h"
#include "greeter.h"
#include "plan_manager.h"
#include "meal.h"
#include "recipe_db.h"

using namespace std;

void PlanManager::showPlans() {

    // plan.txt 열기.
    std::ifstream planFile("plan.txt");
    if (!planFile.is_open()) {
        std::cerr << "Failed to open plan.txt file." << std::endl;
        return;
    }

    std::string line;
    RecipeDatabase recipeDb();
    
    while (std::getline(planFile, line)) {
        std::istringstream iss(line);
        int year, month, day, servings;

        // 연도, 월, 일 파일로부터 추출.
        iss >> year >> month >> day;
        Date date(year, month, day); // Date 객체 생성
        date.displayAndEdit();

        
        std::vector<std::string> recipes;
        std::string recipeName;
        
        // 레시피와 인분수 추출.
        while (iss >> recipeName) {
            if (isdigit(recipeName[0])) {
                servings = std::stoi(recipeName);
                break;
            } else {
                recipes.push_back(recipeName); // 레시피 이름을 벡터에 추가
            }
        }
        
        //추출한 인분수로 Meal 객체 생성.
        Meal meal(servings); 
        
        // Meal 객체에 추출한 레시피들 추가.
        for (const std::string& recipe : recipes) {
            meal.addRecipeToMeal(recipeDb, recipe);
        }

        //레시피 출력 함수 호출.(Meal에게 위임.)
        meal.displayMealInfo();

        //이번 meal의 장바구니 목록하는 함수 호출.(Meal에게 위임.)
        meal.getGroceryList();
    }
    planFile.close();
   
}

void PlanManager::createNewPlan() {
    int year, month, day;

    cout << "Enter the date to make your plan like this format(2024 10 01) : ";
    cin >> year >> month >> day;

    Date newDate(year, month, day); // 입력받은 날짜로 Date 인스턴스 생성.
    newDate.displayAndEdit(); // Date에게 control 위임.

    std::ofstream planFile("plan.txt", std::ios::app);
    if(planFile.is_open()){
        
        //1. 파일에 날짜 입력.
        planFile << year << " " << month << " " << day << " ";

        Meal meal = newDate.getMealList();
        std::list<std::string> recipesInMeal = meal.getMeals(); //meal로부터 레시피 담긴 string list 받기.
        //2. 파일에 레시피 입력.
        for(const std::string&recipe : recipesInMeal){
            planFile << recipe << " ";
        }

        int servings = meal.getServings(); //meal로부터 servings 받기.
        //3. 파일에 인분수 입력.
        planFile << servings << endl;
        
        planFile.close();
    }
    else {
        std::cerr << "file open failed." << std::endl;
    }

    return; // 일정 추가했으면 Greeter로 돌아감.
}
