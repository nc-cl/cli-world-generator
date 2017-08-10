#include <iostream>
#include <string.h>
#include "GenMap.cc"
#include "GenMapNode.cc"

using namespace std;

int main(int argc, char* argv[]) {
    int width = DEFAULT_SIZE_X;
    int height = DEFAULT_SIZE_Y;
    bool matchMapData = true;
    bool useColor = true;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--size") == 0 || strcmp(argv[i], "-s") == 0) {
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
        } else if (strcmp(argv[i], "--match-map-data") == 0 || strcmp(argv[i], "-m") == 0) {
            matchMapData = false;
        } else if (strcmp(argv[i], "--no-color") == 0 || strcmp(argv[i], "-nc") == 0) {
            useColor = false;
        }
    }

    srand(time(NULL));

    GenMap gmap(width, height);
    gmap.generate();
    gmap.printMap(useColor, matchMapData);
    cout << endl << "done" << endl;

    return 0;
}
