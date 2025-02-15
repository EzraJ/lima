#pragma once
#include <vector>
#include <functional>


namespace lima{
    
    class keyboard{
        public:
            
            keyboard();
            ~keyboard();
            
            void Read();

            void AddCallback(std::function<void(char)> funcIn);

        private:
            char lastPressed;
            std::vector<std::function<void(char)>> callbacks;
            
            
    };


}