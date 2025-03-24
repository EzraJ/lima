#pragma once

namespace lima{
    class Input{
        public:
            virtual void ProcessInput(char c) = 0;
            lima::keyboard* currentKeyboard;
            bool InputActive;
    };

}