#include "world_map_section.h"

WorldMapSection::WorldMapSection(void) {
    _height = 0.0f;
    _rainfall = 0.0f;
    _temperature = 0.0f;
}

WorldMapSection::WorldMapSection(float height, float rfall, float temp) {
    _height = height;
    _rainfall = rfall;
    _temperature = temp;
}

int WorldMapSection::getBiome() {
    if (_height >= 0.90f) {
        return BIOME_MOUNTAIN_SNOW;
    }
    if (_height >= 0.75f) {
        if (_temperature < 0.20f) {
            return BIOME_MOUNTAIN_SNOW;
        }
        return BIOME_MOUNTAIN;
    }
    if (_height >= 0.50f) {
        if (_temperature >= 0.70f) {
            if (_height >= 0.55f && _rainfall >= 0.80f) {
                return BIOME_RAINFOREST;
            }
            if (_height >= 0.55f && _rainfall < 0.25f) {
                return BIOME_DESERT;
            }
            if (_rainfall < 0.35f) {
                return BIOME_SAVANNA;
            }
        }
        if (_height >= 0.55f && _rainfall >= 0.50f && _rainfall < 0.60f) {
            return BIOME_FOREST;
        }
        if (_temperature < 0.20f) {
            return BIOME_SNOW;
        }
        if (_height < 0.55f && _rainfall >= 0.70f) {
            return BIOME_MARSH;
        }

        return BIOME_GRASSLAND;
    }
    if (_height >= 0.45f) {
        return BIOME_COAST;
    }

    return BIOME_SEA;
}

std::string WorldMapSection::getBiomeString(bool useColor) {
    int biome = getBiome();
    std::string biomeChar;

    switch (biome) {
        case BIOME_SEA:
        case BIOME_COAST:
        case BIOME_MARSH:
            biomeChar = "~";
            break;
        case BIOME_GRASSLAND:
        case BIOME_SAVANNA:
        case BIOME_DESERT:
        case BIOME_SNOW:
            biomeChar = "G";
            break;
        case BIOME_FOREST:
        case BIOME_RAINFOREST:
            biomeChar = "t";
            break;
        case BIOME_MOUNTAIN:
        case BIOME_MOUNTAIN_SNOW:
            biomeChar = "^";
            break;
        default:
            biomeChar = "?";
    }

    if (useColor) {
        std::string fgColor, bgColor;

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
            case BIOME_SNOW:
                fgColor = "15";
                bgColor = "233";
            case BIOME_MOUNTAIN_SNOW:
                fgColor = "15";
                bgColor = "236";
                break;
            default:
                fgColor = "15";
                bgColor = "0";
        }

        return "\033[48;5;" + bgColor + "m\033[38;5;" + fgColor + "m" + biomeChar + "\033[0m";
    }

    return biomeChar;
}

void WorldMapSection::setHeight(float height) {
    _height = height;
}

void WorldMapSection::setRainfall(float rfall) {
    _rainfall = rfall;
}

void WorldMapSection::setTemperature(float temp) {
    _temperature = temp;
}
