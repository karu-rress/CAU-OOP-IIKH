#ifndef _DATE_H_
#define _DATE_H_

#include <list>
#include <string>
#include <vector>

#include "meal.h"

class Date {
public:
    Date(int year, int month, int day);

    std::string getDateAsString() const;
    void displayAndEdit();
    void manageMealList(const std::list<std::string> &mealList);
    std::list<std::string> getMealList() const; // To ensure safety, set it as const
    void buildGroceryList(std::map<std::string, double> &groceryList) const;

private:
    int year;
    int month;
    int date;

    std::string description;
    std::vector<Meal> meals;
};

#endif
