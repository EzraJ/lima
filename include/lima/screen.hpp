#include <functional>
#include "lima/bean.hpp"
#include "lima/render.hpp"

// TODO: Screen manager to handle stuff like window resizes

namespace lima{
    class screen{
        public:
            screen(uint32_t x, uint32_t y, uint32_t sX, uint32_t sY){
                xPos = x;
                yPos = y;
                xSz = sX;
                ySz = sY;
                funcSet = false;
            }

                // Func(bean, xPosition, yPosition, xGL, yGL, time)

            void setFunc(std::function<void(lima::bean*, uint32_t, uint32_t, float, float, float)> funcIn){
                func = funcIn;
                funcSet = true;
            }

            void Process(float time = 0.0f){
                if(!funcSet) return;
                
                uint32_t xBuf = xPos;
                uint32_t yBuf = yPos;
                for(auto& b : beans){
                    if(b == nullptr) continue;
                    float xGL = (float)2 * (float)((float)xBuf - (float)xPos)/((float)xSz) - 1;
                    float yGL = (float)2 * (float)((float)yBuf - (float)yPos)/((float)ySz) - 1;
                    func(b, xBuf, yBuf, xGL, yGL, time);
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

            uint32_t xPos;
            uint32_t yPos;

            uint32_t xSz;
            uint32_t ySz;
            bool funcSet;
            std::vector<lima::bean*> beans;

        private:
            std::function<void(lima::bean*, uint32_t, uint32_t, float, float, float)> func;

    };
}
