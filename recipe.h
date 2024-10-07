#ifndef _RECIPE_H_
#define _RECIPE_H_

#define DEBUG_KARU

#include <string>

class Recipe {
public:
    // Compare
    // Update
    //

#ifdef DEBUG_KARU
    std::string getName() const
    {
        return "name";
    }

    void edit() {
        
    }
#endif

private:
};

#endif