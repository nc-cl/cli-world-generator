#include <algorithm>
#include "height_map_settings_mask.h"

HeightMapSettingsMask::HeightMapSettingsMask(const HeightMap *hmap) {
    this->setHeights(0.0f, hmap->getSizeX(), hmap->getSizeY());
}

HeightMapSettingsMask::HeightMapSettingsMask(int x, int y) {
    this->setHeights(0.0f, x, y);
}

void HeightMapSettingsMask::reset() {
    int size_y = this->getSizeY();

    for (auto i = _heights.begin(); i != _heights.end(); i++)
        (*i).assign(size_y, 0.0f);
}

void HeightMapSettingsMask::applyBorder(float border_h, float h_falloff, float h_falloff_limit,
    int border_width) {

    border_h = std::clamp(border_h, 0.0f, 1.0f) * 2.0f - 1.0f;
    h_falloff = std::clamp(h_falloff, -1.0f, 1.0f);

    int size_x = this->getSizeX(),
        size_y = this->getSizeY(),
        border_dist,
        x_dist,
        y_dist;
    float h,
        normal_h;
    bool h_falloff_is_positive = h_falloff > 0.0f;

    for (int x = 0; x < size_x; x++) {
        x_dist = std::min(x, std::abs(x - size_x) - 1);

        for (int y = 0; y < size_y; y++) {
            y_dist = std::min(y, std::abs(y - size_y) - 1);
            border_dist = std::min(x_dist, y_dist);

            if (border_dist < border_width) {
                h = std::clamp(border_h + h_falloff * border_dist, -1.0f, 1.0f);
                normal_h = (h + 1.0f) / 2.0f;

                if (h_falloff_is_positive ? normal_h < h_falloff_limit : normal_h > h_falloff_limit)
                    _heights[x][y] = h;
            }
        }
    }

}
