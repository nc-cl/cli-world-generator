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
        string fgColor, bgColor;

        switch (_biome) {
            case BIOME_SEA:
                fgColor = "27";
                bgColor = "0";
                break;
            case BIOME_COAST:
                fgColor = "27";
                bgColor = "17";
                break;
            case BIOME_GRASSLAND:
                fgColor = "40";
                bgColor = "233";
                break;
            case BIOME_MOUNTAIN:
                fgColor = "249";
                bgColor = "0";
                break;
            case BIOME_SNOW:
                fgColor = "15";
                bgColor = "234";
                break;
            default:
                fgColor = "15";
                bgColor = "0";
        }

        return "\033[48;5;" + bgColor + "m\033[38;5;" + fgColor + "m" + biomeChar + "\033[0m";
    }

    return biomeChar;
}

void GenMapNode::setBiome(int biome) {
    _biome = biome;
}

void GenMapNode::setComputedBiome(float biomeVal) {
    if (biomeVal <= 0.45f) {
        setBiome(BIOME_SEA);
    } else if (biomeVal <= 0.55f) {
        setBiome(BIOME_COAST);
    } else if (biomeVal <= 0.75f) {
        setBiome(BIOME_GRASSLAND);
    } else if (biomeVal <= 0.85f) {
        setBiome(BIOME_MOUNTAIN);
    } else {
        setBiome(BIOME_SNOW);
    }
}
