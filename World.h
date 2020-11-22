#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include "Country.h"

class World{
    // atributes
private:
    std::vector<Country>* countries;

public:
    // constructor
    World()
    {
        countries = new std::vector<Country*>();
    }

    // methods
    void divideAndConquer();
    void dynamicProgramming(std::vector<Country*>,int);
    void backTracking();

    void insertCountry(Country pCountry);
};

#endif WORLD_H