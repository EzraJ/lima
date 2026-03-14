#pragma once

#include <vector>
#include <cstdint>

#include "lima/bean.hpp"

namespace lima{
    class Resizable{
        public:
            virtual void Resize()=0;
            Resizable(){}
            virtual ~Resizable(){}
            
            uint32_t x;
            uint32_t y;
            uint32_t xSz;
            uint32_t ySz;
            std::vector<bean*> beans;
    };   
}
