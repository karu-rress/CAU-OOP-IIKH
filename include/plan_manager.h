/**
 *
 * plan_manager.h
 *
 * @author: 권정주 (@cheongjay)
 * @brief: Plan의 데이터를 저장 및 호출하는 기능들
 *
 */
#ifndef _PLAN_MANAGER_H_
#define _PLAN_MANAGER_H_

#include <filesystem>
#include <fstream>
#include <list>
#include <map>
#include <string_view>

#include "date.h"
#include "meal.h"

class Date;
class Meal;

class PlanManager {
public:
    PlanManager();
    ~PlanManager();

    void reviewPlans();
    void createNewPlan();

private:
    // Plans files
    static constexpr inline std::string_view planFileName = "plans.txt";

    // stores path & file stream
    std::filesystem::path planPath;
    std::fstream planFile;

    std::list<Date> plans;

    void sortPlans();
};

#endif