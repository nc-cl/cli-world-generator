#include <iostream>
#include <string.h>
#include "GenMap.cc"
#include "GenMapNode.cc"

using namespace std;

// Compiled using: g++ -std=c++11 -Wall -o test test.cc
int main(int argc, char* argv[]) {
    bool useColor = true;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-nc") == 0) {
            useColor = false;
        }
    }

    srand(time(NULL));

    GenMap gmap;
    gmap.printMap(useColor);

    return 0;
}
