#include "World.h"
 
void World::insertCountry(Country pCountry)
{
    countries.push_back(pCountry);
}

void World::divideAndConquer()
{
    
}
void World::dynamicProgramming(std::vector<Country*> Quadrant, int colors){
    int tokenColors=0;
    for (int i = 0; i < Quadrant.size(); i+colors)
    {   
        if (tokenColor=0){
            Quadrant.at(co+colors)->setColor(co+1);
            tokenColor=1;
        }
        else{
            for (int co=0; i<colors; co++){
                if(Quadrant.at(((i+colors)->getOriginPoint())-(Quadrant.at(i)->getOriginPoint()))>20){
                    Quadrant.at(i+colors)->setColor(co+1);  
                }
                else{
                    Quadrant.at(i+colors)->setColor(0);
                }
            }
        }
    }
}