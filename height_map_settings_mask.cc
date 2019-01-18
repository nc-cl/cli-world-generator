#include <algorithm>
#include "height_map_settings_mask.h"

HeightMapSettingsMask::HeightMapSettingsMask(const HeightMap *hmap) {
    _heights = hmap->getHeights();
}

void HeightMapSettingsMask::reset() {
    int size_y = _heights[0].size();

    for (auto i = _heights.begin(); i != _heights.end(); i++)
        (*i).assign(size_y, 0.0f);
}

void HeightMapSettingsMask::applyBorder(float border_val, float border_creep, int border_size) {
    border_val = std::clamp(border_val, 0.0f, 1.0f) * 2.0f - 1.0f;
    border_creep = std::clamp(border_creep, 0.0f, 1.0f);

    int size_x = this->getSizeX(),
        size_y = this->getSizeY(),
        border_dist,
        x_dist,
        y_dist;

    for (int x = 0; x < size_x; x++) {
        x_dist = std::min(x + 1, std::abs(x - size_x));

        for (int y = 0; y < size_y; y++) {
            y_dist = std::min(y + 1, std::abs(y - size_y));
            border_dist = std::min(x_dist, y_dist);

            if (border_dist <= border_size) {
                _heights[x][y] = border_val + border_creep * (border_dist - 1);
                _heights[x][y] = std::clamp(_heights[x][y], -1.0f, 1.0f);
            }
        }
    }

}
