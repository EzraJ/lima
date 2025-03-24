#pragma once
#include <string>
#include "lima/Resizable.hpp"
#include "lima/Input.hpp"
#include "lima/keyboard.hpp"
#include "lima/bean.hpp"
#include "lima/render.hpp"

namespace lima{
    class TextInput : Resizable, Input{
        public:
            TextInput(lima::render* rend, lima::keyboard* key, uint xIn, uint yIn, uint xSzIn, uint ySzIn){
                currentRender = rend;
                currentKeyboard = key;
                currentRender->AddResizable((Resizable*)this);
                currentKeyboard->AddInput((Input*)this);
                x = xIn;
                y = yIn;
                xSz = xSzIn;
                ySz = ySzIn;
                enterString = "";
                curPos = 0;
                curString = "";

                ResizeBeans();
                for(auto& b : beans){
                    b->setChar(' ');
                }

                InputActive = false;
            }
            ~TextInput(){
                beans.clear();
            }


            void ProcessInput(char c) override {
                if(!InputActive) return;
                if(c == '\r'){
                    enterString = curString;
                    return;
                }
                if(c == 127 && curPos > 0){
                    curPos--;
                    beans[curPos]->setChar(' ');
                    curString.pop_back();
                    return;
                }else if (c == 127){
                    return;
                }
                if(curPos < xSz * ySz){
                    beans[curPos]->setChar(c);
                    curPos++;
                    curString += c;
                }
            }

            std::string EnteredText(){
                return enterString;
            }

            void Resize() override {
                ResizeBeans();
                for(auto& e : beans){
                    e->setChar(' ');
                }
                for(uint i = 0; i < curPos; i++){
                    beans[i]->setChar(curString[i]);
                }
            }

        private:
            uint curPos;
            std::string enterString;
            std::string curString;
    };
}