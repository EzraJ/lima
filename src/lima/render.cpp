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
        streamBuffer = new basic_str((beanCount * 55) + 3);
        resized = false;
    }

    render::~render(){        
        delete[] beans;
        delete streamBuffer;
    }


    void render::Print(){
        streamBuffer->clear();
        streamBuffer->add("\x1b[H", 3);
        for(uint i = 0; i<= beanCount -1; i++){
            beans[i].CStrAdd(*streamBuffer);
        }
        write(STDOUT_FILENO, streamBuffer->m_str, streamBuffer->m_size);
    }

    void render::SetBeans(char c, color bg, color fg, style s){
        if(resized) Resize();
        for(uint i = 0; i <= beanCount - 1; i++){
            beans[i].SetBean(c, bg, fg, s);
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

        delete streamBuffer;
        streamBuffer = new basic_str((55*beanCount) + 3);
        resized = false;
    }
}