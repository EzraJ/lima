#pragma once

#include "lima/render.hpp"
#include "lima/screen.hpp"
#include "lima/Input.hpp"

namespace lima{

        class GUI : Input{
            public:
                GUI(lima::render* rend, lima::keyboard* key){
                    currentRender = rend;
                    currentKeyboard = key;
                    currentKeyboard->AddInput((lima::Input*)this);
                    index = 0;
                }
                ~GUI(){

                }
                
                void AddInput(lima::Input* in){
                    
                }

                void ProcessInput(char c) override {
                    if(!Input::InputActive) return;
                    if(c != '\t') return;

                }

                void SetActive(bool in){
                    Input::InputActive = in;
                }
    
                void ToggleActive(){
                    Input::InputActive = !Input::InputActive;
                }


            private:
                lima::keyboard* currentKeyboard;
                lima::render* currentRender;
                lima::screen* currentScreen;
                std::vector<lima::Input*> inputs;
                uint index;
        };

}