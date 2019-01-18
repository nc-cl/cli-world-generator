#ifndef HEIGHT_MAP_SETTINGS_MASK_H_
#define HEIGHT_MAP_SETTINGS_MASK_H_

#include "height_map.h"

class HeightMapSettingsMask : public HeightMap {
    public:
        HeightMapSettingsMask(const HeightMap *hmap);
        void reset(void);
        void applyBorder(float border_val, float border_creep, int border_size);
};

#endif
