#include <unistd.h>
#include <string>
#include "lima/ansi.hpp"
#include "lima/keyboard.hpp"

namespace lima{
    void keyboard::Read(){
        lastPressed = '\0';
        if(read(STDIN_FILENO, &lastPressed, 1) == 1){
            if(lastPressed == ANSI::ESC[0]){
                // TODO: Setup special key processing, for now just discard
                // i.e arrow keys 
                if(read(STDIN_FILENO, &lastPressed, 1) != 1){
                    lastPressed = '\0';
                    return;
                }
                if(read(STDIN_FILENO, &lastPressed, 1) != 1){
                    lastPressed = '\0';
                    return;
                }
                lastPressed = '\0';
                return;
            }
            for(auto& e : callbacks){
                e(lastPressed);
            }
            for(auto& e : inputObjects){
                e->ProcessInput(lastPressed);
            }
        }
        // Cycle through all callback functions for onpress events
    }

    void keyboard::AddInput(lima::Input* in){
        inputObjects.push_back(in);
    }

    keyboard::keyboard(){

    }

    keyboard::~keyboard(){
        
    }

}