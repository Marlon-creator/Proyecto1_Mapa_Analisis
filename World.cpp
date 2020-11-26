#include "World.h"
 
void World::insertCountry(Country pCountry)
{
    countries.push_back(pCountry);
}

void World::divideAndConquerMarn(std::vector<Country*> Quadrant, int colors,int ini, int fin)
{
    
    int i=0;
    if(i<Quadrant.size())//size=27 colors=3
    {
        for (int co=0; co<colors; co++){
            divideAndConquer(1-3)
            divideAndConquer(1-3)
            divideAndConquer(1-3)
        }
    }
}
void World::dynamicProgramming(std::vector<Country*> Quadrant, int colors){
    int tokenColors=0;
    for (int i = 0; i < Quadrant.size(); i+colors)
    {   
        if (tokenColor=0){
            for (int co=0; co<colors; co++)
                {Quadrant.at(co+1)->setColor(co+1);}
            tokenColor=1;
        }
        else{
            for (int co=0; co<colors; co++){
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