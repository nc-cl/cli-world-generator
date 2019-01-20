#ifndef HEIGHT_MAP_SETTINGS_MASK_H_
#define HEIGHT_MAP_SETTINGS_MASK_H_

#include "height_map.h"

class HeightMapSettingsMask : public HeightMap {
    public:
        HeightMapSettingsMask(const HeightMap *hmap);
        HeightMapSettingsMask(int x, int y);
        void reset(void);
        void applyBorder(float border_h, float h_falloff, float h_falloff_limit, int border_width);
};

#endif
