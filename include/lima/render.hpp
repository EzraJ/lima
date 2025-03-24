#pragma once
#include <mutex>
#include <chrono>
#include <exception>
#include <memory>
#include <stdlib.h>

#include "terminal/terminal.hpp"
#include "lima/bean.hpp"
#include "lima/vector2.hpp"
#include "lima/basic_str.hpp"
#include "lima/screen.hpp"
#include "lima/Resizable.hpp"
#include <random>

namespace lima{ 
    lima::Vector2 LimaTermSize();
    class render{
        public:
            render();
            ~render();
        
            void Resize();

            void Process();

            void Print();

            void SetBeans(char c, color bg, color fg, style s);

            uint getCount();

            Vector2 getSize();

            lima::screen* CreateScreen(uint x, uint y, uint szX, uint szY);

            void DeleteScreen(lima::screen* ptr);

            void resizeScreen(screen& in);

            bean* getBean(uint x, uint y);
            std::vector<lima::bean*> getBeans(uint xPos, uint yPos, uint xSz, uint ySz);
            void getBeans(std::vector<bean*>& inVec, uint xPos, uint yPos, uint xSz, uint ySz);

            void AddResizable(lima::Resizable* in);

            bool resized;
            bean* beans;
            basic_str* streamBuffer;
            screen* globalScreen;
            std::mutex modifyMutex;
            std::mutex renderMutex;
        private:
            bean* invisibleBean; // Bean that is to be never rendered
            uint beanCount;
            Vector2 terminalSize;
            std::vector<lima::screen*> renderScreens;
            std::vector<lima::Resizable*> renderResizables;
            std::chrono::time_point<std::chrono::high_resolution_clock> timePt;
    };
}
