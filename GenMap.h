#ifndef GEN_MAP_H_
#define GEN_MAP_H_

class GenMap {
    private:
        int sizeX, sizeY;
        int* map;
        void populate(void);
    public:
        GenMap(void);
        GenMap(int, int);
        int getWidth(void);
        int getHeight(void);
        int getSize(void);
        void setSizeX(int);
        void setSizeY(int);
        void printMapValues(void);
};

void GenMap::populate() {
    int size = getSize();
    map = new int[size];
    
    int val = 0;

    for (int i = 0; i < size; i++) {
        map[i] = val;
        val++;
    }
}

GenMap::GenMap() {
    sizeX = 5;
    sizeY = 5;
    populate();
}

GenMap::GenMap(int sizeX, int sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    populate();
}

int GenMap::getWidth() {
    return sizeX;
}

int GenMap::getHeight() {
    return sizeY;
}

int GenMap::getSize() {
    return sizeX * sizeY;
}

void GenMap::setSizeX(int sizeX) {
    this->sizeX = sizeX;
}

void GenMap::setSizeY(int sizeY) {
    this->sizeY = sizeY;
}

#endif
