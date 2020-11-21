#include <vector>
#include "tinyxml2.h"
#include "Country.h"
#include "World.h"

using namespace std;

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif
  
/* This function takes last element as pivot, places  
the pivot element at its correct position in sorted  
array, and places all smaller (smaller than pivot)  
to left of pivot and all greater elements to right  
of pivot */
int partition (vector<Country*> &arr, int low, int high)  
{  
    Country* pivot = arr.at(high); // pivot  
    int i = (low - 1); // Index of smaller element  
    for (int j = low; j < high; j++)  
    {  
        // If current element is smaller than the pivot  
        if (arr.at(j)->getOriginPoint() < pivot->getOriginPoint())  
        {  
            i++; // increment index of smaller element  
            swap(arr[i], arr[j]);  
        }  
    }  
    swap(arr[i + 1], arr[high]);  
    return (i + 1);  
}  
  
/* The main function that implements QuickSort  
arr[] --> Array to be sorted,  
low --> Starting index,  
high --> Ending index */
void quickSort(vector<Country*> &arr, int low, int high)  
{  
    if (low < high)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partition(arr, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}  

int main()
{
    // atributtes
    const char* idPais;
    const char* path;
    // map quadrants
    vector<Country*> firstQuadrant;
    vector<Country*> secondQuadrant;
    vector<Country*> thirdQuadrant;
    vector<Country*> fourthQuadrant;

    // XML 
    tinyxml2::XMLDocument mundo;

    tinyxml2::XMLError eResult = mundo.LoadFile("world.SVG");

    XMLCheckResult(eResult);
    
    tinyxml2::XMLNode * pRoot = mundo.FirstChildElement("svg"); 

    if (pRoot == nullptr) cout << "return tinyxml2::XML_ERROR_FILE_READ_ERROR";

    tinyxml2::XMLElement * pElement = pRoot->FirstChildElement("path");
    if (pElement == nullptr) cout << "return tinyxml2::XML_ERROR_PARSING_ELEMENT";

    while (pElement != nullptr)
    {   
        // country's id
        idPais = pElement->Attribute("id");
        if (idPais == nullptr) cout << "return tinyxml2::XML_ERROR_PARSING_ATTRIBUTE";
        string idPaisF = idPais;

        // country's d
        path = pElement->Attribute("d");
        if(path == nullptr) cout << "return tinyxml2::XML_ERROR_PARSING_ATTRIBUTE";
        string pathF = path;

        
        // getting the m of the d attribute
        string s = "";
        float originX;
        float originY;
        for (int i = 2; pathF.at(i) != ' '; i++)
        {
            if (pathF.at(i) != ',')
            {
                s.push_back(pathF.at(i));
            }
            else
            {
                originX = stof(s);
                s = "";
            }
        }
        originY = stof(s);  

        // Unify originX and Y to get originPoint
        // int iOriginX = stoi(originX);
        // int iOriginY = stoi(originY);

        // originX = to_string(iOriginX);
        // originY = to_string(iOriginY);

        // while(originX.size() != 4)
        // {
        //     originX = "0" + originX;
        // }
        // while(originY.size() != 3)
        // {
        //     originY = "0" + originY;
        // }

        // create and add Country
        //int originPoint = stoi(originX + originY);
        Country* country = new Country(idPais, "#f2f2f2", originX, originY);

        // insert the country in one of the four quadrants
        if (originX <= 800)
        {
            if (originY <= 500)
            {
                firstQuadrant.push_back(country);
            }
            else
            {
                thirdQuadrant.push_back(country);
            }
        }
        else
        {
            if (originY <= 500)
            {
                secondQuadrant.push_back(country);
            }   
            else
            {
                fourthQuadrant.push_back(country);
            }
        }
        pElement = pElement->NextSiblingElement("path");
    }

    // sort the array of countries
    quickSort(firstQuadrant, 0, firstQuadrant.size() - 1);
    quickSort(secondQuadrant, 0, secondQuadrant.size() - 1);
    quickSort(thirdQuadrant, 0, thirdQuadrant.size() - 1);
    quickSort(fourthQuadrant, 0, fourthQuadrant.size() - 1);

    for (int i = 0; i < firstQuadrant.size(); i++)
    {
        cout << firstQuadrant.at(i)->getId() << ": " << firstQuadrant.at(i)->getOriginPoint() << endl;
    }
    cout << "2---------------------------------------" << endl;
    for (int i = 0; i < thirdQuadrant.size(); i++)
    {
        cout << thirdQuadrant.at(i)->getId() << ": " << thirdQuadrant.at(i)->getOriginPoint() << endl;
    }
    cout << "3----------------------------------------" << endl;
    for (int i = 0; i < secondQuadrant.size(); i++)
    {
        cout << secondQuadrant.at(i)->getId() << ": " << secondQuadrant.at(i)->getOriginPoint() << endl;
    }
    cout << "4---------------------------------------" << endl;
    for (int i = 0; i < fourthQuadrant.size(); i++)
    {
        cout << fourthQuadrant.at(i)->getId() << ": " << fourthQuadrant.at(i)->getOriginPoint() << endl;
    }

    return 0;
}