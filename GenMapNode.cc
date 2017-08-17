#include "GenMapNode.h"

int GenMapNode::getBiome() {
    return _biome;
}

string GenMapNode::getBiomeString(bool useColor) {
    string biomeChar;

    switch (_biome) {
        case BIOME_SEA:
        case BIOME_COAST:
            biomeChar = "~";
            break;
        case BIOME_GRASSLAND:
            biomeChar = "G";
            break;
        case BIOME_MOUNTAIN:
        case BIOME_SNOW:
            biomeChar = '^';
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
            case BIOME_COAST:
                color = "36";
                break;
            case BIOME_GRASSLAND:
                color = "32";
                break;
            case BIOME_MOUNTAIN:
                color = "30";
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

void GenMapNode::setComputedBiome(float biomeVal) {
    if (biomeVal <= 0.35f) {
        setBiome(BIOME_SEA);
    } else if (biomeVal <= 0.49f) {
        setBiome(BIOME_COAST);
    } else if (biomeVal <= 0.79f) {
        setBiome(BIOME_GRASSLAND);
    } else if (biomeVal <= 0.89f) {
        setBiome(BIOME_MOUNTAIN);
    } else {
        setBiome(BIOME_SNOW);
    }
}
