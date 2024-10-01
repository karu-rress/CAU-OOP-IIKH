#ifndef _PLAN_MANAGER_H_
#define _PLAN_MANAGER_H_

#include "date.h"
#include <list>

class PlanManager {
public:
    void showPlans() {
        for (Date date : m_dates) {
            // 1. 일정 출력
            date.displayAndEdit();

            // 2. 장바구니 출력
        }
    }

private:
    std::list<Date> m_dates;
};

#endif