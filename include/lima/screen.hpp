#pragma once

#include <functional>

#include "lima/bean.hpp"
#include "lima/Vector2.hpp"
#include "lima/screen_info.hpp"

// TODO: Screen manager to handle stuff like window resizes

namespace lima{
    class screen{
        public:
            screen(Vector2 Pos, Vector2 Sz);
            
            void setFunc(std::function<void(screen_info)> funcIn);

            void Process(float time = 0.0f);
            
			~screen();
            
            Vector2 Position;
            Vector2 Size;
            
            bool funcSet;
            std::vector<lima::bean*> beans;
            
            private:
            // func(bean, xPos, yPos, normX, normY, time)
            std::function<void(screen_info)> func;
            
    };
}
