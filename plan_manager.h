#ifndef _PLAN_MANAGER_H_
#define _PLAN_MANAGER_H_

#include <list>

#include "date.h"
#include "greeter.h"

class PlanManager {
public:
    PlanManager();

    void showPlans(); // option이 4번이면 실행.
    void createNewPlan(); // option이 5번이면 실행.

private:
    std::list<Date> m_dates; // 계획된 Date들이 들어가 있는 Date리스트 = 일정(Plan).
    std::list<std::string> groceryList; // 빈 장바구니 : Date한테 넘겨줄 아규먼트.
};

#endif