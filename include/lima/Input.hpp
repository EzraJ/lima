#pragma once

namespace lima{

    class Input{
        public:
            Input() {}
            ~Input() {}
            virtual void ProcessInput(char c) = 0;

    };

}