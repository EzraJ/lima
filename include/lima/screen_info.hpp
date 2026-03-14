#pragma once

#include "lima/bean.hpp"

// lima::bean*, uint32_t, uint32_t, float, float, float

namespace lima{
    struct screen_info{
        lima::bean* beanPtr;
        uint32_t xPos;
        uint32_t yPos;
        float normX;
        float normY;
        float time;
    };

}