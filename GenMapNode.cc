#include "GenMapNode.h"

int GenMapNode::getBiome() {
    return _biome;
}

string GenMapNode::getBiomeString(bool useColor) {
    string biomeChar;

    switch (_biome) {
        case BIOME_SEA:
            biomeChar = "~";
            break;
        case BIOME_GRASSLAND:
            biomeChar = "G";
            break;
        default:
            biomeChar = "?";
    }

    if (useColor) {
        string color;

        switch (_biome) {
            case BIOME_SEA:
                color = "34";
                break;
            case BIOME_GRASSLAND:
                color = "32";
                break;
            default:
                color = "37";
        }

        return "\033[1;" + color + "m" + biomeChar + "\033[0m";
    }

    return biomeChar;
}

void GenMapNode::setBiome(int biome) {
    _biome = biome;
}
