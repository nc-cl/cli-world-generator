#include "GenMapNode.h"

int GenMapNode::getBiome() {
    if ((!_isTropical && _height >= 0.85f) || (_isTropical && _height >= 0.95f)) {
        return BIOME_MOUNTAIN_SNOW;
    }
    if (_height >= 0.75f) {
        if (_isTropical && _height < 0.80f && _rainfall > 0.80f) {
            return BIOME_MOUNTAIN_RAINFOREST;
        }
        if (_height < 0.80f && _rainfall > 0.50f && _rainfall <= 0.60f) {
            return BIOME_MOUNTAIN_FOREST;
        }

        return BIOME_MOUNTAIN;
    }
    if (_height >= 0.50f) {
        if (_isTropical && _rainfall > 0.80f) {
            return BIOME_RAINFOREST;
        }
        if (_isTropical && _rainfall <= 0.35f && _rainfall > 0.25f) {
            return BIOME_SAVANNA;
        }
        if (_isTropical && _rainfall <= 0.25f) {
            return BIOME_DESERT;
        }
        if (_height < 0.55f && _rainfall > 0.70f) {
            return BIOME_MARSH;
        }
        if (_rainfall > 0.50f && _rainfall <= 0.60f) {
            return BIOME_FOREST;
        }

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
        case BIOME_MARSH:
            biomeChar = "~";
            break;
        case BIOME_GRASSLAND:
        case BIOME_SAVANNA:
            biomeChar = "G";
            break;
        case BIOME_DESERT:
            biomeChar = 'm';
            break;
        case BIOME_FOREST:
            biomeChar = "t";
            break;
        case BIOME_RAINFOREST:
            biomeChar = 'T';
            break;
        case BIOME_MOUNTAIN:
        case BIOME_MOUNTAIN_SNOW:
        case BIOME_MOUNTAIN_FOREST:
        case BIOME_MOUNTAIN_RAINFOREST:
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
            case BIOME_MARSH:
                fgColor = "40";
                bgColor = "233";
                break;
            case BIOME_GRASSLAND:
                fgColor = "40";
                bgColor = "233";
                break;
            case BIOME_FOREST:
                fgColor = "34";
                bgColor = "0";
                break;
            case BIOME_DESERT:
                fgColor = "221";
                bgColor = "233";
                break;
            case BIOME_SAVANNA:
                fgColor = "148";
                bgColor = "233";
                break;
            case BIOME_RAINFOREST:
                fgColor = "22";
                bgColor = "0";
                break;
            case BIOME_MOUNTAIN:
                fgColor = "249";
                bgColor = "233";
                break;
            case BIOME_MOUNTAIN_SNOW:
                fgColor = "15";
                bgColor = "236";
                break;
            case BIOME_MOUNTAIN_FOREST:
                fgColor = "34";
                bgColor = "233";
                break;
            case BIOME_MOUNTAIN_RAINFOREST:
                fgColor = "22";
                bgColor = "233";
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

void GenMapNode::setIsTropical(bool isTropical) {
    _isTropical = isTropical;
}
