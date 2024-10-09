#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>

#include "date.h"

using namespace std;

Date::Date(int year, int month, int date)
    : year(year)
    , month(month)
    , date(date)
    , description("") {};

tuple<int, int, int> Date::getDate() const {
    return make_tuple(m_year, m_month, m_day);
}

string Date::getDateAsString() const {
    ostringstream oss;
    oss << setw(2) << setfill('0');
    oss << year << '-' << month << '-' << date;

    return oss.str();
}

// Edit discription
void Date::displayAndEdit() {
    cout << "Date: " << getDateAsString() << endl;

    // Display current memo
    if (!description.empty()) {
        cout << "Memo: " << description << endl;
    }
    else {
        cout << "There are currently no memo." << endl;
    }

    // Prompt user to edit the memo
    cout << "Would you like to edit the memo? (Y/N): ";
    char choice;
    cin >> choice;
    cin.ignore(); // Ignore any leftover newline character

    if (toupper(choice) == 'Y') {
        cout << "Enter new memo: ";
        getline(cin, description);

        cout << "New Memo: " << description << endl;
        cout << "Memo updated successfully." << endl;
    }
    else {
        cout << "No changes made to the memo" << endl;
    }
}

void Date::manageMealList(const list<Meal> &allMeals) {
    char choice;
    do {
        // 현재 날짜에 해당하는 식사 목록 출력
        cout << "Meals for " << year << "-" << month << "-" << day << endl;

        if (!meals.empty()) {
            cout << "Current meal list for this date:" << endl;
            for (const auto &meal : meals) {
                cout << "- " << meal.getName() << endl;
            }
        }
        else {
            cout << "No meals in the list for this date." << endl;
        }

        cout << "\nWhat would you like to do? Choose one." << endl;
        cout << "1. Add a meal\n";
        cout << "2. Remove a meal\n";
        cout << "3. Exit\n";
        cout << "Enter your choice number: ";
        cin >> choice;
        cin.ignore();

        if (choice == '1') {
            cout << "Enter the name of the meal to add: ";
            string newMealName;
            getline(cin, newMealName);

            // 전체 Meal 리스트에서 이름에 맞는 Meal 객체 찾기
            auto it = find_if(allMeals.begin(), allMeals.end(),
                [&newMealName](const Meal &meal) { return meal.getName() == newMealName; });

            if (it != allMeals.end()) {
                // 이미 존재하는 Meal 객체를 현재 Date 객체의 meals 리스트에 추가
                meals.push_back(*it);
                cout << "Meal added successfully to this date." << endl;
            }
            else {
                cout << "Meal not found in the available meals." << endl;
            }
        }
        else if (choice == '2') {
            cout << "Enter the name of the meal to remove: ";
            string mealToRemove;
            getline(cin, mealToRemove);

            // meals 리스트에서 이름에 맞는 Meal 객체 찾기
            auto it = find_if(meals.begin(), meals.end(),
                [&mealToRemove](const Meal &meal) { return meal.getName() == mealToRemove; });

            if (it != meals.end()) {
                meals.erase(it); // Date 객체의 meals 리스트에서 삭제
                cout << "Meal removed successfully from this date." << endl;
            }
            else {
                cout << "Meal not found in this date's meal list." << endl;
            }
        }
        else if (choice == '3') {
            cout << "Exiting meal management" << endl;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
            choice = 3;
        }
    } while (choice != '3');
}

list<std::string> Date::getMealList() const {
    list<string> mealNames;
    for (const auto &meal : meals) {
        mealNames.push_back(meal.getName()); // Meal 클래스의 getName() 사용
    }
    return mealNames;
}

// Build grocery list
//   NOTE: groceryList is output parameter
void Date::buildGroceryList(map<string, double> &groceryList) const {
    for (const auto &meal : meals) {
        for (const auto &[name, quantity] : meal.getGroceryList()) {
            groceryList[name] += quantity;
        }
    }
}