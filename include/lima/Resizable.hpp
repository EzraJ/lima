#pragma once

#include <vector>
#include "lima/bean.hpp"

namespace lima{
    class Resizable{
        public:
            virtual void Resize()=0;
            Resizable(){}
            virtual ~Resizable(){}
            
            uint x;
            uint y;
            uint xSz;
            uint ySz;
            std::vector<bean*> beans;
    };   
}