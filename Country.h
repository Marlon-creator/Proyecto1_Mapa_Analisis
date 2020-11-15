#ifndef COUNTRY_H
#define COUNTRY_H

Country
{
// atributes
private:
    string id;
    string color;

    float originX;
    float originY;

// methods
public:
    // constructor
    Country(string pId, string pColor, int pOriginX,, int pOriginY)
    {
        id = pId;
        color = pColor;
        originX = pOriginX;
        originY = pOriginY;
    }

    void paintCountry(string pColor);
}

#endif COUNTRY_H