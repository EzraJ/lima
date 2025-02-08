#include <functional>
#include "lima/bean.hpp"
#include "lima/render.hpp"

// TODO: Screen manager to handle stuff like window resizes

namespace lima{
    class screen{
        public:
            screen(uint x, uint y, uint sX, uint sY){
                xPos = x;
                yPos = y;
                xSz = sX;
                ySz = sY;
                funcSet = false;
            }

                // Func(bean, xPosition, yPosition, xGL, yGL, time)

            void setFunc(std::function<void(lima::bean*, uint, uint, float, float, float)> funcIn){
                func = funcIn;
                funcSet = true;
            }

            void Process(float time = 0.0f){
                if(!funcSet) return;
                
                uint xBuf = xPos;
                uint yBuf = yPos;
                for(auto& b : beans){
                    float xGL = (float)2 * (float)((float)xBuf - (float)xPos)/((float)xSz) - 1;
                    float yGL = (float)2 * (float)((float)yBuf - (float)yPos)/((float)ySz) - 1;
                    if(b != nullptr) func(b, xBuf, yBuf, xGL, yGL, time);
                    xBuf++;
                    if(xBuf >= xPos + xSz){
                        xBuf = xPos;
                        yBuf++;
                    }
                }
                
            }

			~screen(){
				beans.clear();
			}

            uint xPos;
            uint yPos;

            uint xSz;
            uint ySz;
            bool funcSet;
            std::vector<lima::bean*> beans;

        private:

            std::function<void(lima::bean*, uint, uint, float, float, float)> func;

    };
}
