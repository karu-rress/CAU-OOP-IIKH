/*

Date Collab orators
Plan Manager
Meal
Maintain information ab out sp eci c date
Date(year, month, day){create new date
DisplayAndEdit(){display date information
in window allowing user to edit entries

*/

#ifndef _DATE_H_
#define _DATE_H_

#include <list>
#include <string>
#include <vector>

class Date
{
public:
    Date(int year, int month, int day);

    void displayAndEdit();
    void manageMealList(const std::list<std::string> &mealList);
    std::list<std::string> getMealList() const; // To ensure safety, set it as const
    void buildGroceryList(const std::map<std::string, double> &groceryList) const;

private:
    int m_year;
    int m_month;
    int m_day;

    std::string description;
    std::vector<Meal> meals;
};

#endif
