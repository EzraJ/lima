#pragma once
// Who's ready for the 99999th implementation of a vector?
#include <cstdint>

namespace lima{
    class Vector2{
        public:
            Vector2(int64_t xIn = 0, int64_t yIn = 0){
                x = xIn; y = yIn;
            }
            ~Vector2(){
                
            }
            int64_t x, y;
    };
}