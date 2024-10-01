#ifndef _MEAL_H_
#define _MEAL_H_

#include <list>

class Meal {
public:
    Meal();
    Meal(const Meal& meal);
    Meal(Meal&& meal) noexcept;

    std::list<std::string> getMeals();

private:
};

#endif