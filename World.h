#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include "Country.h"

class World{
    // atributes
private:
    std::vector<Country> countries;

public:
    // constructor
    World()
    {
        
    }
    // methods
    void startColoring();
    void insertCountry(Country pCountry);
};

#endif WORLD_H