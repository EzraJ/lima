#include "lima/render.hpp"

namespace lima{

    lima::Vector2 LimaTermSize(){
        terminal::terminalSize();
        return lima::Vector2(terminal::termSize.x, terminal::termSize.y);
    }


    render::render(){
        terminalSize = LimaTermSize();
        beanCount = terminalSize.x * terminalSize.y;
        beans = new bean[beanCount];
        streamBuffer.reserve((beanCount * 55) + 3);
        resized = false;
    }

    render::~render(){        
        delete[] beans;
    }


    void render::Print(){
        streamBuffer.clear();
        streamBuffer.append("\x1b[H");
        for(uint i = 0; i <= beanCount-1; i++){
            streamBuffer.append(beans[i].getContent());
        }
        write(STDIN_FILENO, streamBuffer.c_str(), streamBuffer.length());
    }

    void render::SetBeans(char c, color bg, color fg, style s){
        if(resized) Resize();
        beans[0].SetBean(c, bg, fg, s);
        for(uint i = 1; i <= beanCount-1; i++){
            *(beans + i) = beans[0];
        }
    }

    uint render::getCount(){
        return beanCount;
    }

    void render::Resize(){
        Vector2 sz = lima::LimaTermSize();
        beanCount = sz.x * sz.y;
        delete[] beans;
        beans = new bean[beanCount];
        terminalSize = sz;
        streamBuffer.clear();
        streamBuffer.shrink_to_fit();
        streamBuffer.reserve((55 * beanCount) + 3);
        resized = false;
    }
}