#pragma once

namespace lima{
    class Resizable{
        public:
            virtual void Resize()=0;
            virtual void ResizeBeans(){
                beans.clear();
                currentRender->getBeans(beans, x, y, xSz, ySz);
            }
            uint x;
            uint y;
            uint xSz;
            uint ySz;
            lima::render* currentRender;
            std::vector<bean*> beans;
    };   
}