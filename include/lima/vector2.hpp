#pragma once
// Who's ready for the 99999th implementation of a vector?

namespace lima{
    class Vector2{
        public:
            Vector2(int xIn = 0, int yIn = 0){
                x = xIn; y = yIn;
            }
            ~Vector2(){
                
            }
            int x;
            int y;
    };


}