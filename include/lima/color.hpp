#pragma once

namespace lima{
    struct color{
        unsigned char r,g,b;
        color(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0){
            r = red;
            g = green;
            b = blue;
        }
    };
}