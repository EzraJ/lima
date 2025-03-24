#pragma once
#include "lima/Input.hpp"
#include <vector>
#include <functional>
#include <mutex>


namespace lima{
    class keyboard{
        public:
            keyboard();
            ~keyboard();
            
            void Read();

            void AddCallback(std::function<void(char)> funcIn);

            void AddInput(lima::Input* in);

        private:
            char lastPressed;
            std::vector<std::function<void(char)>> callbacks;
            std::vector<lima::Input*> inputObjects;
            std::mutex addMutex;
            
    };
}