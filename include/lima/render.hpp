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

            bool resized;
            bean* beans;
        private:

            std::string streamBuffer;
            uint beanCount;
            Vector2 terminalSize;
            
    };

}