#ifndef _PLAN_MANAGER_H_
#define _PLAN_MANAGER_H_

#include <string>
#include "date.h"
#include "greeter.h"
#include "meal.h"
#include "recipe_db.h"

class PlanManager {
public:
    void showPlans(); 
    void createNewPlan();
};

#endif