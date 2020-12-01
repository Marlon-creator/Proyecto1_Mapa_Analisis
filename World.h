#ifndef WORLD_H
#define WORLD_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>

#include "tinyxml2.h"
#include "Country.h"

class World{
private:
    // atributes
    std::vector<Country*> countries;
    std::vector<Country*> countriesOriginal;

    int whites;
    int painted;

    std::vector<std::string> colors;

public:
    // constructor
    World(std::vector<Country*> &pCountries, std::vector<Country*> pCountriesOriginal)
    {
        countries = pCountries;
        countriesOriginal = pCountriesOriginal;

        whites = 0;
        painted = 0;

        colors = {"#ff0000", "#00ff00", "#0000ff", "#ffe600",  "#ff8000", "#00ffff", "#bb00ff", "#88ff00",   "#ff006a", "#00ff77", "#ff9e9e"};
        //           red       green       blue      yellow      orange     cyan       purple  yellow/green    fucsia  green/blue    pink
    }

    // methods
    void divideAndConquer(int pColors);
    void divideAndConquerAux(std::vector<Country*> &pCountries, int pColors);
    void dynamicProgramming(int pColors);
    void backTracking(int pColors);

    int compareCountries(Country* firstCountry, Country* secondCountry);
    void paintCountries(std::vector<Country*> pCountries, int pColors);
    void updateFile(std::string pFileName);

    void paintCountriesB(std::vector<int>& pPermutation, std::vector<Country*> &secondCountries);
    int testPermutation(std::vector<std::vector<int>> &pPermutations, std::vector<Country*> &firstCountries, std::vector<Country*> &secondCountries, int pColors);

    int getWhites()
    {
        return whites;
    }
};

#endif