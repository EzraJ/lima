#pragma once
#include "render.hpp"

namespace lima{

    class resizable{
        public:

            resizable(){}
            ~resizable(){}

            virtual void Resize(lima::render* in)=0;
    };

    
}