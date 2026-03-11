#pragma once
#include <mutex>
#include <chrono>
#include <exception>
#include <memory>
#include <stdlib.h>
#include <random>

#include "terminal/terminal.hpp"
#include "lima/bean.hpp"
#include "lima/vector2.hpp"
#include "lima/basic_str.hpp"
#include "lima/screen.hpp"
#include "lima/Resizable.hpp"

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
            
            uint32_t getCount();

            Vector2 getSize();

            lima::screen* CreateScreen(uint32_t x, uint32_t y, uint32_t szX, uint32_t szY);

            void DeleteScreen(screen* ptr);

            void resizeScreen(screen* in);

            bean* getBean(uint32_t x, uint32_t y);
            std::vector<lima::bean*> getBeans(uint32_t xPos, uint32_t yPos, uint32_t xSz, uint32_t ySz);
            void getBeans(std::vector<bean*>& inVec, uint32_t xPos, uint32_t yPos, uint32_t xSz, uint32_t ySz);

            void AddResizable(lima::Resizable* in);

            bool resized;
            bean* beans;
            basic_str* streamBuffer;
            std::mutex modifyMutex;
            std::mutex renderMutex;
        private:
            bean* invisibleBean; // Bean that is to be never rendered
            uint32_t beanCount;
            Vector2 terminalSize;
            std::vector<lima::screen*> renderScreens;
            std::vector<lima::Resizable*> renderResizables;
            std::chrono::time_point<std::chrono::high_resolution_clock> timePt;
    };
}
