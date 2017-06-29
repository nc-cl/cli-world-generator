#include <iostream>
#include <string.h>
#include "GenMap.cc"
#include "GenMapNode.cc"

using namespace std;

int main(int argc, char* argv[]) {
    int width = DEFAULT_SIZE_X;
    int height = DEFAULT_SIZE_Y;
    bool useColor = true;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0) {
            if (i + 1 < argc) {
                i++;

                try {
                    width = stoi(argv[i]);
                } catch (const invalid_argument& e) {}

                if (i + 1 < argc) {
                    i++;

                    try {
                        height = stoi(argv[i]);
                    } catch (const invalid_argument& e) {}
                }
            }
        } else if (strcmp(argv[i], "-nc") == 0) {
            useColor = false;
        }
    }

    srand(time(NULL));

    GenMap gmap(width, height);
    gmap.printMap(useColor);

    return 0;
}
