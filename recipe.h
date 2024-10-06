#ifndef _RECIPE_H_
#define _RECIPE_H_

#include <string>
#include <vector>

class Recipe {
private:
    std::string name;                                      // 레시피 이름
    std::vector<std::pair<std::string, int>> ingredients;  // 재료 (이름, 양 in grams)
    std::string instructions;                              // 조리 방법
    int prepTime;                                          // 준비 시간 (분 단위)

public:
    // 생성자
    Recipe(std::string n, std::vector<std::pair<std::string, int>> ingr, std::string instr, int time);

    // Getter 메서드
    std::string getName() const;                           // 레시피 이름 반환
    std::string getInstruction() const;                    // 조리 방법 반환
    std::vector<std::pair<std::string, int>> getIngredients() const; // 재료 반환
    int getPrepTime() const;                               // 준비 시간 반환

    // 레시피 수정 메서드 (재료와 조리법 모두 수정)
    void edit();

    // 재료 양을 인분 수에 맞춰 조정하는 메서드
    void adjustForServings(int servings);

    // 레시피 정보를 출력하는 메서드
    void displayRecipe() const;
};

#endif