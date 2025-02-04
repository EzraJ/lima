// I wanted to make this a class, I really did. But having to interface with sigaction
// and other terminal stuff makes it not a good idea. I thought about making it a singleton so it
// could atleast be a class and more "modern C++", but at that point this would be easier to understand and
// have less bugs

#pragma once
#include <mutex>
#include <exception>
#include <memory>
#include <stdlib.h>

#include "terminal/terminal.hpp"
#include "lima/bean.hpp"
#include "lima/vector2.hpp"
#include "lima/basic_str.hpp"
#include "lima/screen.hpp"
#include <random>

namespace lima{
    lima::Vector2 LimaTermSize();
    class render{
        public:
            render();
            ~render();
        
            void Resize();

            void Print();

            void SetBeans(char c, color bg, color fg, style s);

            uint getCount();

            Vector2 getSize();

            lima::screen* CreateScreen(uint x, uint y, uint szX, uint szY);

            bean* getBean(uint x, uint y){
                if(x <= 0 || y <= 0) {return nullptr;}
                if(x > (uint)terminalSize.x || y > (uint)terminalSize.y) { return nullptr; }
                return &(beans[x - 1 + (y-1) * terminalSize.x]);
            }

            bool resized;
            bean* beans;
            basic_str* streamBuffer;
            std::mutex modifyMutex;
            std::mutex renderMutex;
        private:
            uint beanCount;
            Vector2 terminalSize;
            std::vector<lima::screen*> renderScreens;
            screen* globalScreen;
            
    };

}
