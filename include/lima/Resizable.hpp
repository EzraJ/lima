#pragma once

#include <vector>
#include <cstdint>

#include "lima/Vector2.hpp"
#include "lima/bean.hpp"

namespace lima{
    class Resizable{
        public:
            virtual void Resize()=0;
            Resizable(){}
            virtual ~Resizable(){}

            void SetPosition(Vector2 in){
                Position = in;
                Resize();
            }

            void SetSize(Vector2 in){
                Size = in;
                Resize();
            }

            Vector2 Position;
            Vector2 Size;
            std::vector<bean*> beans;
    };   
}
