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
void World::compareCountries(Country* firstCountry, Country* secondCountry)
{
    float distance = calculateDistance(firstCountry->getOriginX(), firstCountry->getOriginY(), 
                                         secondCountry->getOriginX(), secondCountry->getOriginY());
    if (distance <= 40)
    {
        //cout << "blanco" << endl;
        secondCountry->setColor("#f2f2f2"); // paint a country white
        whites++;
    }
}

// function tu replace the color int the style string
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
        //cout << "trivial" << endl;
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
            // compare first half element with second half element
            else
            {
                compareCountries(firstActual, secondActual);
            }
        }
        cout << "---------------------" << endl;
        // the number of painted countries to do the lazy writing
        if (painted >= 20)
            updateFile("world-divide.svg");
    }
}