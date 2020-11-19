#ifndef COUNTRY_H
#define COUNTRY_H
#include <iostream>

class Country
{
// atributes
private:
    std::string id;
    std::string color;

    float originX;
    float originY;
    float originPoint;

// methods
public:
    // constructor
    Country(std::string pId, std::string pColor, float pOriginX, float pOriginY)
    {
        id = pId;
        color = pColor;
        originX = pOriginX;
        originY = pOriginY;
        originPoint = originX + originY;
    }

    void paintCountry(std::string pColor);

    float getOriginPoint()
    {
        return originPoint;
    }

    std::string getId()
    {
        return id;
    }

    float getOriginX()
    {
        return originX;
    }

    float getOriginY()
    {
        return originY;
    }
};

#endif //COUNTRY_H