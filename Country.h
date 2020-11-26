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

    // methods
    void paintCountry(std::string pColor);
    // getters
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

    std::string getColor()
    {
        return color;
    }
    // setters
    void setColor(std::string pColor)
    {
        color = pColor;
    }
};

#endif //COUNTRY_H