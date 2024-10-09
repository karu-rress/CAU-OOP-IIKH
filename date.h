#ifndef _DATE_H_
#define _DATE_H_

#include <list>
#include <string>
#include <string_view>

#include "meal.h"

class Meal;

class Date {
public:
    Date(int year, int month, int day);
    Date(const std::string &date);

    std::string getDateAsString() const;
    std::list<Meal> getMeals() const;

    void displayAndEdit();
    void manageMeals();
    void buildGroceryList(std::map<std::string, double> &groceryList) const;

    bool operator<(const Date &rhs) const {
        return year < rhs.year || (year == rhs.year && month < rhs.month) ||
               (year == rhs.year && month == rhs.month && date < rhs.date);
    }

private:
    int year;
    int month;
    int date;

    std::string description;
    std::list<Meal> meals;
};

#endif
