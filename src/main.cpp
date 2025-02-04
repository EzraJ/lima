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


    //std::random_device dev;
    //std::mt19937 rng(dev());
    //std::uniform_int_distribution<std::mt19937::result_type> dist(0, 255);

    
    

    //for(uint i = 0; i <= 255; i++){
        //for(uint j = 0; j <= currentRender->getCount() -1; j++){
            //currentRender->beans[j].SetBean('#', lima::color(dist(rng), dist(rng), dist(rng)), lima::color(dist(rng), dist(rng), dist(rng)), myStyle);
        //}
        //currentRender->SetBeans('#', lima::color(dist(rng), dist(rng), dist(rng)), lima::color(dist(rng), dist(rng), dist(rng)), myStyle);
        //currentRender->Print();
    //}

    lima::screen* scrPtr = currentRender->CreateScreen(1, 1, 30, 30);

    scrPtr->setFunc([](lima::bean* b, uint xPos, uint yPos, float xGL, float yGL, float time){
        float x = ((xGL + 1)/2) * 255;
        float y = ((yGL + 1)/2) * 255;
        //b->setBG((int)x, (int)y, time);
        b->setBG((int)x, (int)y, time);
        //b->setBG(100*xGL, 30*yGL, 20);
        b->setChar(' ');
        xPos++;
        yPos++;
        time++;
        yGL++;
        xGL++;
    });

    std::jthread renderThread(renderThreadLoop); // Start rendering
    
    /*for(uint i = 0; i <= 100; i++){
        lima::bean* curBean = currentRender->getBean(i, i);
        if(curBean != nullptr){
            curBean->setBG(i*25, i*25, i*25);
            curBean->setChar(' ');
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }*/

    std::this_thread::sleep_for(std::chrono::seconds(10));

    /*for(int i = 0; i <= 255; i++){
        currentRender->SetBeans('#', lima::color(255, 0, i), lima::color(255, 0, i), myStyle);
        currentRender->getBean(1, 1)->setBG(100, 100, 100);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        //currentRender->Print();
    }
    for(int i = 0; i <= 255; i++){
        currentRender->SetBeans('#', lima::color(255-i, 0, 255), lima::color(255-i, 0, 255), myStyle);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        //currentRender->Print();
    }
    for(int i = 0; i <= 255; i++){
        currentRender->SetBeans('#', lima::color(0, i, 255), lima::color(0, i, 255), myStyle);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        //currentRender->Print();
    }
    for(int i = 0; i <= 255; i++){
        currentRender->SetBeans('#', lima::color(0, 255, 255-i), lima::color(0, 255, 255-i), myStyle);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        //currentRender->Print();
    }
    for(int i = 0; i <= 255; i++){
        currentRender->SetBeans('#', lima::color(i, 255, 0), lima::color(i, 255, 0), myStyle);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        //currentRender->Print();
    }
    for(int i = 0; i <= 255; i++){
        currentRender->SetBeans('#', lima::color(255, 255-i, 0), lima::color(255, 255-i, 0), myStyle);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        //std::this_thread::sleep_for(std::chrono::microseconds(1));
        //currentRender->Print();
    }*/

    //renderThread.join(); // Wait for thread to end
    renderThread.request_stop();
    
    delete currentRender;

	
    
    return 0;
    
    
    /*currentRender->SetBeans('#', myBGColor, myFGColor, myStyle);

    char c = '\0';
    
    while (1){
        c = '\0';
        read(STDIN_FILENO, &c, 1);
        //currentRender->Print();
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
        if (c == 'q'){
            currentRender->running = false;
            break;
        }
        currentRender->SetBeans('#', myBGColor, myFGColor, myStyle);
    }
    currentRender->running = false;
    renderThread.join(); // Wait for thread to end
    delete currentRender;
    return 0;*/
    
}
