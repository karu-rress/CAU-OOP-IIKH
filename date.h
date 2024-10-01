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

class Date {
public:
    Date(int year, int month, int day);

    void displayAndEdit();
    void buildGroceryList(const std::list<std::string>& groceryList);

private:
    int m_year;
    int m_month;
    int m_day;

    std::string description;
};

void Date::displayAndEdit() {
}

#endif
