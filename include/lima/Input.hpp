#pragma once

namespace lima{
    class Input{
        public:
            Input(){}
            virtual ~Input(){}
            virtual void ProcessInput(char c) = 0;
            bool InputActive;
    };

}