#ifndef _DATE_H_
#define _DATE_H_

#include <list>
#include <string>
#include <string_view>
#include <tuple>

#include "meal.h"

class Date {
public:
    Date(int year, int month, int day);
    // Date(const std::string &date);

    std::tuple<int, int, int> getDate() const;
    std::string getDateAsString() const;

    void displayAndEdit();
    void manageMealList(const std::list<Meal> &allMeals);
    std::list<std::string> getMealList() const; // To ensure safety, set it as const
    void buildGroceryList(std::map<std::string, double> &groceryList) const;

private:
    int year;
    int month;
    int date;

    std::string description;
    std::list<Meal> meals;
};

#endif
