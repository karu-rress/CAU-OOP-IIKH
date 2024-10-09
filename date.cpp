#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
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

void Date::manageMeals() {
    while (true) {
        // Display current meals
        cout << "Meals for " << getDateAsString() << endl;

        if (meals.empty()) {
            cout << "No meals planned for this date." << endl;
        }
        else {
            for (const auto &meal : meals) {
                cout << "- " << meal.getName() << endl;
            }
        }

        cout << "\nWhat would you like to do? Choose one.\n"
             << "1. Add a meal\n"
             << "2. Remove a meal\n"
             << "3. Exit\n"
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
                cout << "Add recipes to the meal, separated by space >> ";

                Meal meal;
                string recipeNames;
                cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                getline(cin, recipeNames);

                for (istringstream iss(recipeNames); iss >> recipeNames;)
                    meal.addRecipe(recipeNames);

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

// Build grocery list
//   NOTE: groceryList is output parameter
void Date::buildGroceryList(map<string, double> &groceryList) const {
    for (const auto &meal : meals) {
        for (const auto &[name, quantity] : meal.getGroceryList()) {
            groceryList[name] += quantity;
        }
    }
}