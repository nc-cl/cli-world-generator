#include "GenMapNode.h"

int GenMapNode::getBiome() {
    if (_height >= 0.85f) {
        return BIOME_SNOW;
    }
    if (_height >= 0.75f) {
        return BIOME_MOUNTAIN;
    }
    if (_height >= 0.55f) {
        return BIOME_GRASSLAND;
    }
    if (_height >= 0.45f) {
        return BIOME_COAST;
    }

    return BIOME_SEA;
}

string GenMapNode::getBiomeString(bool useColor) {
    int biome = getBiome();
    string biomeChar;

    switch (biome) {
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

        switch (biome) {
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

void GenMapNode::setHeight(float height) {
    _height = height;
}

void GenMapNode::setRainfall(float rfall) {
    _rainfall = rfall;
}
