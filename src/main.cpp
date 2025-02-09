// Lima startup
// Get engines initialized(rendering, networking, sound, etc)
// Then start another thread and pass arguments to game_main

#include <iostream>
#include "lima/ansi.hpp"
#include "terminal/terminal.hpp"
#include "lima/bean.hpp"
#include "lima/render.hpp"
#include "game/game_main.hpp" // game_main(int argc, char** argv)
#include <thread>
#include <stop_token>

#include <chrono>

lima::render* currentRender = nullptr;




void onTerminalResize(int signum [[maybe_unused]]){
    if(currentRender == nullptr) return;
    currentRender->resized = true;
}


void renderThreadLoop(std::stop_token stopToken){
    while(!stopToken.stop_requested()){
        if(currentRender == nullptr) continue;
        currentRender->Process();
        currentRender->Print();
    }
}


int main(int argc, char** argv){

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

    std::jthread renderThread(renderThreadLoop); // Start rendering
    
    int game_result = game_main(argc, argv, currentRender);
    

    renderThread.request_stop();
    
    delete currentRender;
        
    return game_result;
    

    
}
