#ifndef _GREETER_H_
#define _GREETER_H_

enum class Option {
    BrowseRecipe,
    AddRecipe,
    EditRecipe,
    ReviewPlan,
    CreatePlan,
    Quit,
};

class Greeter {
public:
    void printInitialMessage();

    Option getUserOption();

private:
};

void Greeter::printInitialMessage() {
}

Option Greeter::getUserOption() {
}

#endif