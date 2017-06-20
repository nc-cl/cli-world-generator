#ifndef GEN_MAP_H_
#define GEN_MAP_H_

class GenMap {
    private:
        int _sizeX, _sizeY;
        int* _map;
    public:
        GenMap(void) : _sizeX(5), _sizeY(5) { populate(); }
        GenMap(int x, int y) : _sizeX(x), _sizeY(y) { populate(); }
        int getWidth(void);
        int getHeight(void);
        int getSize(void);
        void setSizeX(int);
        void setSizeY(int);
        void populate(void);
        void printMapValues(void);
};

#endif

