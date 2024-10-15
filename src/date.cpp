#include <algorithm>
#include <format>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <tuple>

#include "../include/date.h"

using namespace std;

Date::Date(int year, int month, int date)
    : year(year)
    , month(month)
    , date(date)
    , memo("") {};

// date format: "YYYY-MM-DD"
Date::Date(const std::string &date) {
    istringstream iss(date);
    char _; // discard '-'
    iss >> year >> _ >> month >> _ >> this->date;
}

Date::Date(const std::string &date, const std::string &description)
    : Date(date) {
    this->memo = description;
}

Date::Date(const std::string &date, const std::string &description, const std::list<Meal> &meals)
    : Date(date, description) {
    this->meals = meals;
}

[[nodiscard]] std::tuple<int, int, int> Date::getDate() const {
    return { year, month, date };
}

[[nodiscard]] string Date::getDateAsString() const {
    return format("{:04d}-{:02d}-{:02d}", year, month, date);
}

[[nodiscard]] list<Meal> Date::getMeals() const {
    return meals;
}

[[nodiscard]] string Date::getMemo() const {
    return memo;
}

// Edit discription
void Date::displayAndEdit() {
    cout << format("\n====== {} ({}) ======\n",
        getDateAsString(),
        memo.empty() ? "No memo" : memo);

    // ask for edit
    cout << "Would you like to edit the memo? (Y/N): ";

    char choice;
    cin >> choice;
    cin.ignore(); // Ignore any leftover newline character

    if (toupper(choice) == 'Y') {
        cout << "Enter new memo: ";
        getline(cin, memo);

        cout << "New Memo: " << memo << endl;
        cout << "Memo updated successfully.\n\n";
    }
    else {
        cout << "No changes made to the memo.\n\n";
    }
}

void Date::manageMeals() {
    while (true) {
        // Display current meals
        cout << "Meals for " << getDateAsString() << endl;

        if (meals.empty()) {
            cout << "No meals planned for this date." << endl;
        }

        cout << "\nWhat would you like to do? Choose one.\n\n"
             << "  1. Add a meal\n"
             << "  2. Remove a meal\n"
             << "  3. Exit\n\n"
             << "Enter your choice number: ";
        char choice;
        cin >> choice;
        cin.ignore();

        // Add a meal
        if (choice == '1') {
            cout << "Enter the name of the meal to add: ";

            string newMeal;
            cin >> newMeal;

            bool found = false;
            for (const auto &meal : meals) {
                if (meal.getName() == newMeal) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                // Meal meal;
                string mealName = newMeal;
                Meal meal(mealName);
                string recipeNames;

                meal.adjustServings();

                cout << "Add recipes to the meal, separated by space >> ";

                
                cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                getline(cin, recipeNames);

                for (istringstream iss(recipeNames); iss >> recipeNames;) {
                    meal.addRecipe(recipeNames);
                    // std::cout << "Recipe added: " << recipeNames << std::endl;
                }
                meals.push_back(meal);
                cout << "Meal added successfully." << endl;
            }
            else {
                cout << "Already exists." << endl;
            }
        }
        else if (choice == '2') {
            cout << "Enter the name of the meal to remove: ";

            string mealName;
            cin >> mealName;

            auto it = ranges::find_if(meals, [&mealName](const Meal &meal) {
                return meal.getName() == mealName;
            });

            if (it != meals.end()) {
                meals.erase(it);
                cout << "Meal removed successfully." << endl;
            }
            else {
                cout << "Meal not found." << endl;
            }
        }
        else if (choice == '3') {
            cout << "Exiting meal management." << endl;
            return;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void Date::setMeals(const list<Meal> &meals) {
    this->meals = meals;
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