#pragma once

#include <algorithm>

namespace lima{
    struct vector2{
        int x;
        int y;
        vector2(int _x, int _y){
            x = _x;
            y = _y;
        }
        friend void swap(vector2& lhs, vector2& rhs){
            std::swap(lhs.x, rhs.x);
            std::swap(lhs.y, rhs.y);
        }

    };
}
