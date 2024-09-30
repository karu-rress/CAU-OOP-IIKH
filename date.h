/*

Date Collab orators
Plan Manager
Meal
Maintain information ab out sp eci c date
Date(year, month, day){create new date
DisplayAndEdit(){display date information
in window allowing user to edit entries
BuildGro ceryList(List &){add items from
all meals to gro cery li

*/

#ifndef _DATE_H_
#define _DATE_H_

#include <string>
#include <list>

class Date
{
public:
    Date(int year, int month, int day);

    void displayAndEdit();
    void buildGroceryList(const std::list<std::string> &);

private:
    int m_year;
    int m_month;
    int m_day;

    std::string description;
    std::list<std::string> groceryList;
};

void Date::displayAndEdit() {

}

#endif

