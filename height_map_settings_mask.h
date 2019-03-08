// Height map settings class.
// A derived class of the height map class; map settings are applied
// to the class' height map data via its exposed function, such that
// the settings can be applied to another height map via matrix-like
// addition.

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
