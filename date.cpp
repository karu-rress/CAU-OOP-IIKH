#include "date.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

Date::Date(int year, int month, int day)
    : m_year(year), m_month(month), m_day(day), description("") {};

void Date::displayAndEdit()
{
    // Display date
    cout << "Date: " << m_year << "-" << m_month << "-" << m_day << endl;

    // Display current memo
    if (!description.empty())
    {
        cout << "Memo: " << description << endl;
    }
    else
    {
        cout << "There are currently no memo." << endl;
    }

    // Prompt user to edit the memo
    cout << "Would you like to edit the memo? (Y/N): ";
    char choice;
    cin >> choice;
    cin.ignore(); // Ignore any leftover newline character

    if (choice == 'y' || choice == 'Y')
    {
        cout << "Enter new memo: ";
        std::getline(cin, description);
        cout << "New Memo: " << description << endl;
        cout << "Memo updated successfully." << endl;
    }

    else
    {
        cout << "No changes made to the memo" << endl;
    }
}

void Date::manageMealList(const std::list<std::string> &mealList)
{
    std::list<std::string> mealsNames;
    for (const auto &meal : meals)
    {
        auto mealNames = meal.getMeals(); // Get the meal name using a method of the Meal class.
        mealsNames.insert(mealsNames.end(), mealNames.begin(), mealNames.end());
    }

    char choice;
    do
    {
        // Display current meals
        std::cout << "Meals for " << m_year << "-" << m_month << "-" << m_day << std::endl;

        if (!mealsNames.empty())
        {
            std::cout << "Meal list that is currently available for addition." << std::endl;
            for (const auto &meal : mealsNames)
            {
                std::cout << "- " << meal << std::endl;
            }

            std::cout << "\nWhat would you like to do? Choose one." << std::endl;
            std::cout << "1. Add a meal\n";
            std::cout << "2. Remove a meal\n";
            std::cout << "3. Exit\n";
            std::cout << "Enter your choice number: ";
            std::cin >> choice;
            std::cin.ignore();

            if (choice == '1')
            {
                std::cout << "Enter the name of the meal to add: ";
                std::string newMeal;
                std::getline(std::cin, newMeal);
                auto it = std::find(mealList.begin(), mealList.end(), newMeal);
                if (it != mealList.end())
                {
                    Meal newMealObject;
                    // Add logic to add appropriate recipes here
                    meals.push_back(newMealObject); // Add to actual meals vector
                    std::cout << "Meal added successfully." << std::endl;
                }
                else
                {
                    std::cout << "Meal not found in the provided meal list. Cannot add." << std::endl;
                }
            }
            else if (choice == '2')
            {
                std::cout << "Enter the name of the meal to remove: ";
                std::string mealToRemove;
                std::getline(std::cin, mealToRemove);
                auto it = std::find_if(meals.begin(), meals.end(),
                                       [&mealToRemove](const Meal &meal)
                                       { return meal.getName() == mealToRemove; });
                if (it != meals.end())
                {
                    meals.erase(it); // Delete from the actual meals vector
                    std::cout << "Meal removed successfully." << std::endl;
                }
                else
                {
                    std::cout << "Meal not found." << std::endl;
                }
            }
            else if (choice == '3')
            {
                std::cout << "Exiting meal management." << std::endl;
            }
            else
            {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
        else
        {
            std::cout << "No meals in meal list. You can't add a meal, sorry." << std::endl;
            choice = '3';
        }
    } while (choice != '3');
}

std::list<std::string> Date::getMealList() const
{
    std::list<std::string> mealNames;
    for (const auto &meal : meals)
    {
        auto names = meal.getMeals(); // Get name from Meal object
        mealNames.insert(mealNames.end(), names.begin(), names.end());
    }
    return mealNames;
}

void Date::buildGroceryList(std::map<std::string, double> &groceryList) const
{
    for (const auto &meal : meals)
    {
        std::map<std::string, double> mealGroceryList = meal.getGroceryList();
        for (const auto &[ingredient, amount] : mealGroceryList)
        {
            groceryList[ingredient] += amount;
        }
    }
}
