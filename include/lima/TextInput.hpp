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
                curRender = rend;
                curKeyboard = key;
                rend->AddResizable((Resizable*)this);
                key->AddInput((Input*)this);
                x = xIn;
                y = yIn;
                xSz = xSzIn;
                ySz = ySzIn;
                rend->getBeans(beans, x, y, xSz, ySz);
                enterString = "";
                curPos = 0;
                curString = "";
                for(auto& b : beans){
                    b->setChar(' ');
                }
            }
            ~TextInput(){
                
            }

            void ProcessInput(char c[[maybe_unused]]) override {
                if(curRender->resized == true) return;
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
                beans.clear();
                curRender->getBeans(beans, x, y, xSz, ySz);
                for(auto& e : beans){
                    e->setChar(' ');
                }
                
                for(uint i = 0; i < curPos; i++){
                    beans[i]->setChar(curString[i]);
                }
            }

        private:
            uint curPos;
            uint x;
            uint y;
            uint xSz;
            uint ySz;
            std::vector<bean*> beans;
            std::mutex resizeMutex;
            lima::render* curRender;
            lima::keyboard* curKeyboard;

            std::string enterString;
            std::string curString;
    };

}