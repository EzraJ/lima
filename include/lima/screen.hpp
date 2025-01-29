#include <functional>
#include "lima/render.hpp"

// TODO: Screen manager to handle stuff like window resizes

namespace lima{
    class screen{
        public:
            screen(uint xpos, uint ypos, uint xSz, uint ySz){
                xPos = xpos;
                yPos = ypos;
                xSize = xSz;
                ySize = ySz;
            }

            void cacheBeans(){
                // TODO: Calculate and store the beans we want to run with
            
            }

            void setFunc(std::function<void(float, float, uint, uint, unsigned float)> funcIn){
                func = funcIn;
            }

            void setRender(render* rendIn){
                rend = rendIn;
            }

            void process(unsigned float time = 0.0f){
                // TODO: thread cached beans and run function with appropriate variables
                

            }

            ~screen(){

            }
        private:
            uint xPos;
            uint yPos;
            uint xSize;
            uint ySize;

            std::vector<lima::bean*> beanCache;
            std::function<void(float, float, uint, uint, unsigned float)> renderFunc;
            lima::render rend;
            

    };
}