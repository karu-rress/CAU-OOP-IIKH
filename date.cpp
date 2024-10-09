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

// date format: "YYYY-MM-DD"
Date::Date(const std::string &date) {
    istringstream iss(date);
    char delimiter;
    iss >> year >> delimiter >> month >> delimiter >> this->date;
}

string Date::getDateAsString() const {
    ostringstream oss;
    oss << setw(2) << setfill('0'); // 출력 폭 설정
    oss << year << '-' << month << '-' << date;

    return oss.str();
}

list<Meal> Date::getMeals() const {
    return meals;
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

void Date::manageMealList(const list<string> &mealList) {
    list<string> mealsNames;
    for (const auto &meal : meals) {
        auto mealNames = meal.getMeals(); // Get the meal name using a method of the Meal class.
        mealsNames.insert(mealsNames.end(), mealNames.begin(), mealNames.end());
    }

    char choice;
    do {
        // Display current meals
        cout << "Meals for " << year << "-" << month << "-" << date << endl;

        if (!mealsNames.empty()) {
            cout << "Meal list that is currently available for addition." << endl;
            for (const auto &meal : mealsNames) {
                cout << "- " << meal << endl;
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
                string newMeal;
                getline(cin, newMeal);
                auto it = find(mealList.begin(), mealList.end(), newMeal);
                if (it != mealList.end()) {
                    Meal newMealObject;
                    // Add logic to add appropriate recipes here
                    meals.push_back(newMealObject); // Add to actual meals vector
                    cout << "Meal added successfully." << endl;
                }
                else {
                    cout << "Meal not found in the provided meal list. Cannot add." << endl;
                }
            }
            else if (choice == '2') {
                cout << "Enter the name of the meal to remove: ";
                string mealToRemove;
                getline(cin, mealToRemove);
                auto it = find_if(meals.begin(), meals.end(),
                    [&mealToRemove](const Meal &meal) { return meal.getName() == mealToRemove; });
                if (it != meals.end()) {
                    meals.erase(it); // Delete from the actual meals vector
                    cout << "Meal removed successfully." << endl;
                }
                else {
                    cout << "Meal not found." << endl;
                }
            }
            else if (choice == '3') {
                cout << "Exiting meal management." << endl;
            }
            else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
        else {
            cout << "No meals in meal list. You can't add a meal, sorry." << endl;
            choice = '3';
        }
    } while (choice != '3');
}

list<string> Date::getMealList() const {
    list<string> mealNames;
    for (const auto &meal : meals) {
        auto names = meal.getMeals(); // Get name from Meal object
        mealNames.insert(mealNames.end(), names.begin(), names.end());
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