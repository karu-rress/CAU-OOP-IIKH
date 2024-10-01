#include "plan_manager.h"
#include <iostream>
#include "date.h"
#include "greeter.h"
#include <string>

using namespace std;

//4. review an existing plan for several meals.
//4-1. 날짜 출력 -> Date에게 권한 넘김.
//4-2. 해당 날짜의 meal(레시피 여러 개) 출력 -> Date에게 권한 넘김.
//4-3. meal에 필요한 ingredients(쇼핑목록) 출력 -> Date가 groceryList만들어주면 직접 출력.
//만약 등록되어있는 계획이 한 개도 없다면 -> "존재하는 일정이 없습니다." 직접 출력.

//e.g. 예시일 뿐.. 출력 형태는 다른 클래스에서 결정될 예정.
//2024년 11월 11일 파스타, 떡볶이, 국밥 / 쇼핑목록: 파스타면, 떡, 고추장, 토마토페이스트, 쌀, 사골국, 후추~~
//2024년 12월 11일 마라탕, 돈가스 / 쇼핑목록: ~~~
//2024년 12월 15일 김치찌개, 된장찌개 / 쇼핑목록: 김치, ~~~~


//5. create a new plan of meals.
//계획을 위한 날짜 목록을 입력하라는 프롬프트 띄우기 cin >> year, month, day
//입력받은 날짜는 Date 인스턴스 생성해서 Date에게 권한 위임. 


class PlanManager
{

public:
    
    void optionFourthFifth(int n){
        if(n == 3) //enum에서 index 3 - 네 번째 option ReviewPlan,
            showPlans();
        else if(n == 4) //enum에서 index 4 - 다섯 번째 option CreatePlan
            createNewPlan();
        else{
            cout << "4,5번이 아닌 숫자가 입력되었습니다." << endl;
        }
    }

    void showPlans() {
        if(m_dates.empty()){
                cout << "존재하는 일정이 없습니다." << endl;
                return; //Greeter로 돌아감.
        }
        for (Date date : m_dates) { //계획된 날짜들 리스트 돌면서 하나씩 출력.
            

            // 1. 일정(날짜) 출력: 여기서는 호출만. 직접 출력은 Date에게 권한넘김.
            date.displayAndEdit(); 
            // 2. 그 날의 레시피 출력. : 이거를 displayAndEdit()와 함께 출력? 아니면 따로 레시피 출력을 돕는 기능을 Date에 추가?
            
            // 3. 장바구니 출력
            groceryList = date.buildGroceryList(groceryList); //date에게 빈 groceryList 넘겨주면 string list 반환.
            for(string ingredient : groceryList){
                cout << "Grocery List: ";
                cout << ingredient << " ";
            }
            cout << endl;
        }
    }

    void createNewPlan(){
        int year, month, day;
        cout << "일정을 만들 날짜를 입력하세요.(e.g. 2024 10 01)";
        cin >> year >> month >> day;
        cout << year <<"년 " << month << "월 " << day << "일" << endl;
        Date dateNew(year, month, day); //입력받은 날짜로 Date 인스턴스 생성.
        dateNew.displayAndEdit(); //Date에게 control 위임.
  
        m_dates.push_back(dateNew); //m_dates에 dateNew 추가: 전체 일정에다가 새롭게 계획한 Date 추가.
        return; //일정 추가했으면 Greeter로 돌아감.
    }
    

private:
    std::list<Date> m_dates; //계획된 Date들이 들어가 있는 Date리스트 = 일정(Plan).
    std::list<std::string> groceryList;
};