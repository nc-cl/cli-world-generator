#include <iostream>
#include <string.h>
#include "GenMap.cc"
#include "GenMapNode.cc"

using namespace std;

int main(int argc, char* argv[]) {
    bool useColor = true;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-nc") == 0) {
            useColor = false;
        }
    }

    GenMap gmap;
    gmap.printMap(useColor);

    return 0;
}
