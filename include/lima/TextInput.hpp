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
                currentRender->AddResizable((lima::Resizable*)this);
                currentKeyboard->AddInput((lima::Input*)this);
                Resizable::x = xIn;
                Resizable::y = yIn;
                Resizable::xSz = xSzIn;
                Resizable::ySz = ySzIn;
                enterString = "";
                curPos = 0;
                curString = "";

                ResizeBeans();
                for(auto& b : Resizable::beans){
                    b->setChar(' ');
                }

                Input::InputActive = false;
            }
            ~TextInput(){
                Resizable::beans.clear();
            }

            void SetActive(bool in){
                Input::InputActive = in;
            }

            void ToggleActive(){
                Input::InputActive = !Input::InputActive;
            }

            void ProcessInput(char c) override {
                if(!Input::InputActive || c == '\t') return;
                if(c == '\r'){
                    enterString = curString;
                    return;
                }
                if(c == 127 && curPos > 0){
                    curPos--;
                    Resizable::beans[curPos]->setChar(' ');
                    curString.pop_back();
                    return;
                }else if (c == 127){
                    return;
                }
                if(curPos < xSz * ySz){
                    Resizable::beans[curPos]->setChar(c);
                    curPos++;
                    curString += c;
                }
            }

            std::string EnteredText(){
                return enterString;
            }

            void ResizeBeans(){
                if(currentRender != nullptr){
                    Resizable::beans.clear();
                    currentRender->getBeans(Resizable::beans, x, y, xSz, ySz);
                }
            }

            void Resize() override {
                ResizeBeans();
                for(auto& e : Resizable::beans){
                    e->setChar(' ');
                }
                for(uint i = 0; i < curPos; i++){
                    Resizable::beans[i]->setChar(curString[i]);
                }
            }

        private:
            uint curPos;
            std::string enterString;
            std::string curString;
            lima::render* currentRender;
            lima::keyboard* currentKeyboard;
    };
}