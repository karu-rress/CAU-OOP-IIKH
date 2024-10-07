/*

Date Collaborators
Plan Manager
Meal
Maintain information about specic date
Date(year, month, day){create new date
DisplayAndEdit(){display date information
in window allowing user to edit entries

*/

#ifndef _DATE_H_
#define _DATE_H_

#include <list>
#include <string>
#include <vector>
#include "meal.h"

#include "meal.h"

class Date
{
public:
    Date(int year, int month, int day);

    std::string getDateAsString() const;
    void displayAndEdit();
    void manageMealList(const std::list<std::string> &mealList);
    std::list<std::string> getMealList() const; // To ensure safety, set it as const
    void buildGroceryList(std::map<std::string, double> &groceryList) const;

private:
    int m_year;
    int m_month;
    int m_day;

    std::string description;
    std::vector<Meal> meals;
};

#endif
