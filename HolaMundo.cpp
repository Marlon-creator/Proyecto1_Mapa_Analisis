#include <iostream>
#include <vector>
#include "tinyxml2.h"

using namespace std;

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

int main()
{
    const char* idPais;
    vector<string> listaPaises;

    tinyxml2::XMLDocument mundo;

    tinyxml2::XMLError eResult = mundo.LoadFile("world.SVG");

    XMLCheckResult(eResult);
    
    tinyxml2::XMLNode * pRoot = mundo.FirstChildElement("svg"); 

    if (pRoot == nullptr) cout << "return tinyxml2::XML_ERROR_FILE_READ_ERROR";

    tinyxml2::XMLElement * pElement = pRoot->FirstChildElement("path");
    if (pElement == nullptr) cout << "return tinyxml2::XML_ERROR_PARSING_ELEMENT";

    while (pElement != nullptr)
    {   
        idPais = pElement->Attribute("id");
        if (idPais == nullptr) cout << "return tinyxml2::XML_ERROR_PARSING_ATTRIBUTE";
        string idPaisF = idPais;
        
        cout << idPaisF << " ";
        pElement = pElement->NextSiblingElement("path");
    }
    
    return 0;
}