// Object that needs to be updated every render loop.

#pragma once 

namespace lima{

    class Label{
        public:
            Label(){}
            ~Label(){}
            virtual void Process()=0;
        private:


    };

}