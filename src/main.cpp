// Lima startup
// Get engines initialized(rendering, networking, sound, etc)
// Then start another thread and pass arguments to game_main

#include <iostream>
#include "lima/ansi.hpp"
#include "terminal/terminal.hpp"
#include "lima/bean.hpp"
#include "lima/render.hpp"
#include "game/game_main.hpp" // game_main(int argc, char** argv)

#include <chrono>

lima::render* currentRender = nullptr;

bool resizing = false;

void onTerminalResize(int signum [[maybe_unused]]){
    if(currentRender == nullptr) return;
    currentRender->resized = true;
}


int main(){

    terminal::initializeTerminal(); // Enter raw mode
    struct sigaction saSize;
    saSize.sa_handler = onTerminalResize;
    sigemptyset(&saSize.sa_mask);
    saSize.sa_flags = SA_RESTART;
    sigaction(SIGWINCH, &saSize, NULL);
    if(saSize.sa_handler == SIG_IGN){
        exit(1);
    }

    // and then have fun
    currentRender = new lima::render();
    lima::style myStyle;
    myStyle.bold = false;
    myStyle.dim = false;
    myStyle.italic = false;
    myStyle.underline = false;
    myStyle.blinking = false;
    myStyle.inverse = false;
    myStyle.invisible = false;
    myStyle.strikethrough = false;
    lima::color myFGColor(255, 255, 255);
    lima::color myBGColor(0,0,0);

    
    for(int i = 0; i <= 255; i++){
        currentRender->SetBeans('#', lima::color(), lima::color(255, 0, i), myStyle);
        currentRender->Print();
    }
    for(int i = 0; i <= 255; i++){
        currentRender->SetBeans('#', lima::color(), lima::color(255-i, 0, 255), myStyle);
        currentRender->Print();
    }
    for(int i = 0; i <= 255; i++){
        currentRender->SetBeans('#', lima::color(), lima::color(0, i, 255), myStyle);
        currentRender->Print();
    }
    for(int i = 0; i <= 255; i++){
        currentRender->SetBeans('#', lima::color(), lima::color(0, 255, 255-i), myStyle);
        currentRender->Print();
    }
    for(int i = 0; i <= 255; i++){
        currentRender->SetBeans('#', lima::color(), lima::color(i, 255, 0), myStyle);
        currentRender->Print();
    }
    for(int i = 0; i <= 255; i++){
        currentRender->SetBeans('#', lima::color(), lima::color(255, 255-i, 0), myStyle);
        currentRender->Print();
    }

    delete currentRender;
    return 0;
    
    
    /*currentRender->SetBeans('#', myBGColor, myFGColor, myStyle);

    char c = '\0';
    
    while (1){
        c = '\0';
        read(STDIN_FILENO, &c, 1);
        currentRender->Print();
        if(c == 0){
            continue;
        }

        if (c == 'B'){
            myStyle.bold = !myStyle.bold;
        } else if (c == 'b'){
            myStyle.blinking = !myStyle.blinking;
        } else if (c == 'i'){
            myStyle.inverse = !myStyle.inverse;
        } else if (c == 'I'){
            myStyle.italic = !myStyle.italic;
        } else if (c == 'u'){
            myStyle.underline = !myStyle.underline;
        } else if (c == 's'){
            myStyle.strikethrough = !myStyle.strikethrough;
        } else if (c == 'd'){
            myStyle.dim = !myStyle.dim;
        } else if (c == 'h'){
            myStyle.invisible = !myStyle.invisible;
        } 
        else if (c == 'a'){
            sleep(5);
            continue;
        }
        if (c == 'q') break;
        currentRender->SetBeans('#', myBGColor, myFGColor, myStyle);
    }
    
    delete currentRender;
    return 0;
    */
}
