#include <iostream>
#include <string>
#include <sstream>
#include "GenMap.h"

using namespace std;

void GenMap::printMapValues() {
    std::stringstream strstr;

    strstr << "map:";
    
    for (int i = 0; i < getSize(); i++) {
        strstr << " " << map[i];
    }

    cout << strstr.str() << endl;
}
