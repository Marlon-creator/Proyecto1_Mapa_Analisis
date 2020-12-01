#include "World.h"

using namespace std;

// paint the countries of a vector based on the vector colors and the number of colors the user wants
void World::paintCountries(std::vector<Country*> pCountries, int pColors)
{
    int colorIndex = 0;
    for(int i = 0; i < pCountries.size(); i++)
    {
        if(colorIndex == pColors)
        {
            colorIndex = 0; 
        }
        pCountries.at(i)->setColor(colors.at(colorIndex));
        colorIndex++;
        painted++;
    }
}

// calculate the distance between two points
float calculateDistance(float firstDistanceX, float firstDistanceY, float secondDistanceX, float secondDistanceY)
{
    return sqrt( (firstDistanceX - secondDistanceX)*(firstDistanceX - secondDistanceX) + 
                 (firstDistanceY - secondDistanceY)*(firstDistanceY - secondDistanceY) 
               );
}

// if a pair of countries has the same color and they are too close, paint the second country white
int World::compareCountries(Country* firstCountry, Country* secondCountry)
{
    float distance = calculateDistance(firstCountry->getOriginX(), firstCountry->getOriginY(), 
                                         secondCountry->getOriginX(), secondCountry->getOriginY());
    if (distance <= 25)
    {
        secondCountry->setColor("#f2f2f2"); // paint a country white
        whites++;
    }

    return whites;
}

// function tu replace the color in the style string
void replaceString(string &style, string color)
{
    for(int index = 5; index < color.size() + 5; index++)
    {
        style.at(index) = color.at(index - 5);
    }
}

// function to update the colors of the countries in the SVG
void World::updateFile(string pFileName)
{
    // get the required file
    tinyxml2::XMLDocument worldSVG;
    // load file
    tinyxml2::XMLError eResult = worldSVG.LoadFile(pFileName.c_str());
    // get to the svg root
    tinyxml2::XMLNode * pRoot = worldSVG.FirstChildElement("svg"); 
    // get to the path elements
    tinyxml2::XMLElement * pElement = pRoot->FirstChildElement("path");
    // const char where we are gonna store the element style atributte
    const char* charStyle;

    for(int index = 0; index < countriesOriginal.size(); index++)
    {
        // get the vector's country's color attribute and ID
        string color = countries.at(index)->getColor();
        //cout << color << endl;
        // get the SVG's country's style attribute
        charStyle = pElement->Attribute("style");
        string style = charStyle;
        // edit the country's style with the new color
        replaceString(style, color);
        // write in the SVG the new style attribute
        pElement->SetAttribute("style", style.c_str());

        // get the next elemento of the svg
        pElement = pElement->NextSiblingElement("path");
    }
    worldSVG.SaveFile(pFileName.c_str());
}

// the divide and conquer function the user calls with the number of colors to use in the map
void World::divideAndConquer(int pColors)
{
    divideAndConquerAux(countries, pColors);
}

// the divide and conquer algorithm
void World::divideAndConquerAux(std::vector<Country*> &pCountries, int pColors)
{
    if (pCountries.size()/2  <= pColors)
    {
        paintCountries(pCountries, pColors);   
    }
    else
    {
        // iterator for halving the vector of countries
        auto start = pCountries.begin();
        auto half = pCountries.begin() + (pCountries.size() / 2) + 1;
        auto last = pCountries.end();
        // two new vectors 
        std::vector<Country*> firstHalf(start, half);
        std::vector<Country*> secondHalf(half, last);
        // recursively split the sub problems 
        divideAndConquerAux(firstHalf, pColors);
        divideAndConquerAux(secondHalf, pColors);
        
        // merge
        int sizeFirstHalf = firstHalf.size();
        int sizeSecondHalf = secondHalf.size();

        // compare the fist half elements to the second half elements
        for (int iterator = 0; iterator < sizeSecondHalf; iterator++)
        {   
            Country* firstActual = firstHalf.at(iterator);
            Country* secondActual = secondHalf.at(iterator);

            // compare iterator + pColors
            if (iterator + pColors < sizeFirstHalf)
            {
                compareCountries(firstActual, firstHalf.at(iterator + pColors));                
            }
            //compare first half element with second half element
            compareCountries(firstActual, secondActual);            
        }
        // update the file 
        if(painted >= 20)
        {
            updateFile("world-divide.svg");
           
        }   
    }
}

void World::dynamicProgramming(int pColors)
{
    // get the first group of countries
    auto startFirst = countries.begin();
    auto endFirst = countries.begin() + pColors;
    vector<Country*> firstCountries(startFirst, endFirst);
    // paint it
    paintCountries(firstCountries, pColors);
    // iterate the list of countries to make the stages
    for (int index = pColors; index + pColors < countries.size(); index = index + pColors)
    {   
        // get the second group of countries
        auto startSecond = countries.begin() +  index;
        auto endSecond = countries.begin() + index + pColors;
        vector<Country*> secondCountries(startSecond, endSecond);
        // paint it
        paintCountries(secondCountries, pColors);
        // compare the actual stage and the past stage
        for(int indexCountries = 0; indexCountries < pColors; indexCountries++)
        {
            compareCountries(firstCountries.at(indexCountries), secondCountries.at(indexCountries));
        }
        // second group of countries is now the first stage
        firstCountries = secondCountries;
    }
    // update the file 
        if(painted >= 20)
        {
            updateFile("world-dynamic.svg");
        }   
}

// if a pair of countries has the same color and they are too close, paint the second country white
int compareCountriesB(Country* firstCountry, Country* secondCountry)
{
    int whites = 0;
    float distance = calculateDistance(firstCountry->getOriginX(), firstCountry->getOriginY(), 
                                         secondCountry->getOriginX(), secondCountry->getOriginY());
    if (distance <= 25 && firstCountry->getColor() == secondCountry->getColor())
    {
        secondCountry->setColor("#f2f2f2"); // paint a country white
        whites++;
    }

    return whites;
}

void World::paintCountriesB(vector<int>& pPermutation, vector<Country*> &secondCountries)
{
    for (int index = 0; index < pPermutation.size(); index++)
    {
        secondCountries.at(index)->setColor(colors.at(pPermutation.at(index)));
    }
}

int World::testPermutation(vector<vector<int>> &pPermutations, vector<Country*> &firstCountries, vector<Country*> &secondCountries, int pColors)
{
    int whitesAux = INT_MAX;
    int indexWhites = 0;
    int whitesFinal;
    // test the permutation in the second group of countries
    for(int index = 0; index < pPermutations.size(); index++)
    {
        // paint the second group with the permutation
        paintCountriesB(pPermutations.at(index), secondCountries);
        // compare the groups of countries
        
        for(int indexCountries = 0; indexCountries < pColors; indexCountries++)
        {
            // get the whites of the permutation
            whitesFinal = compareCountriesB(firstCountries.at(indexCountries), secondCountries.at(indexCountries));
            // store the permutation with less whites
            if (whitesFinal <= whitesAux)
                indexWhites = indexCountries;
        }        
    }
    // return the permutation with less whites
    whites = whitesFinal;
    return indexWhites;
}

void World::backTracking(int pColors)
{
    // create a vector of permutations
    vector<vector<int>> permutations; 
    // create an array of ints from 0 to pColor
    vector<int> permutation;
    for (int index = 0; index < pColors; index++)
    {
        permutation.push_back(index);
    }
    // next permutation of the array
    int poda = 0;
    do {
        // insert the permutation in the array of permutations
        permutations.push_back(permutation);
        poda++;
    } while(std::next_permutation(permutation.begin(), permutation.end()) && poda <= 100);

    // get the first group of countries
    auto startFirst = countries.begin();
    auto endFirst = countries.begin() + pColors;
    vector<Country*> firstCountries(startFirst, endFirst);
    // paint it
    paintCountries(firstCountries, pColors);
    // iterate the list of countries to make the stages
    for (int index = pColors; index + pColors < countries.size(); index = index + pColors)
    {
        // get the second group of countries
        auto startSecond = countries.begin() +  index;
        auto endSecond = countries.begin() + index + pColors;
        vector<Country*> secondCountries(startSecond, endSecond);
        // test the different permutations between the two countries
        int bestPermutation = testPermutation(permutations, firstCountries, secondCountries, pColors);
        // paint the secondCountries with the best permutation
        paintCountriesB(permutations.at(bestPermutation), secondCountries);
        painted += pColors;
        // second group of countries is now the first stage
        firstCountries = secondCountries;

           
    }
    // update the file 
    if(painted >= 20)
    {
        updateFile("world-backtracking.svg");
            
    }
}