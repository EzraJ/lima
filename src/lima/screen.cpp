#include "lima/screen.hpp"
#include "lima/screen_info.hpp"

namespace lima{

        screen::screen(Vector2 Pos, Vector2 Sz){
                Position = Pos;
                Size = Sz;
                funcSet = false;
        }

        void screen::setFunc(std::function<void(screen_info)> funcIn){
                func = funcIn;
                funcSet = true;
        }

        void screen::Process(float time){
            if(!funcSet) return;
            
            screen_info info;

            uint32_t xBuf = Position.x;
            uint32_t yBuf = Position.y;
            for(auto& b : beans){
                if(b == nullptr) continue;
                info.beanPtr = b;
                info.xPos = xBuf;
                info.yPos = yBuf;

                info.normX = (float)2 * (float)((float)xBuf - (float)Position.x)/((float)xSz) - 1.0f;
                info.normY = (float)2 * (float)((float)yBuf - (float)Position.y)/((float)ySz) - 1.0f;
                
                info.time = time;

                func(info);
                xBuf++;
                if(xBuf >= xPos + xSz){
                    xBuf = xPos;
                    yBuf++;
                }
            }
        }

        screen::~screen(){
            beans.clear();
		}

}