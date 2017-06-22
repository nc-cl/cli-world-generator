#include <iostream>
#include "GenMapNode.h"


int GenMapNode::getBiome() {
    return _biome;
}

char GenMapNode::getBiomeChar() {
    return _biomeChar;
}

void GenMapNode::setBiome(int biome) {
    _biome = biome;
    
    switch(biome) {
        case BIOME_SEA:
            _biomeChar = '~';
            break;
        case BIOME_GRASSLAND:
            _biomeChar = 'G';
            break;
    }
}

