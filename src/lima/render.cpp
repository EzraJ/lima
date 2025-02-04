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
        invisibleBean = new bean;
        timePt = std::chrono::high_resolution_clock::now();
    }

    render::~render(){        
        delete[] beans;
        delete streamBuffer;

        for(auto& e : renderScreens){
        	delete e;
        }
		delete globalScreen;
        delete invisibleBean;
    }


    void render::Process(){
        if(resized) Resize();
        modifyMutex.lock();
        for(auto& e : renderScreens){
            e->Process((float) ((float)std::chrono::duration_cast<std::chrono::milliseconds>(timePt - std::chrono::high_resolution_clock::now()).count() / 1000.0f));
        }
        modifyMutex.unlock();
    }

    void render::Print(){
        if(resized) Resize();
        renderMutex.lock();

        streamBuffer->clear();
        streamBuffer->add("\x1b[H", 3);
        for(uint i = 0; i<= beanCount -1; i++){
            beans[i].CStrAdd(*streamBuffer);
        }
        
        renderMutex.unlock();
        write(STDOUT_FILENO, streamBuffer->m_str, streamBuffer->m_size);
    }

    void render::SetBeans(char c, color bg, color fg, style s){
        if(resized) Resize();
        modifyMutex.lock();
        
        if(resized) Resize();
        for(uint i = 0; i <= beanCount - 1; i++){
            beans[i].SetBean(c, bg, fg, s);
        }

        modifyMutex.unlock();
    }

    uint render::getCount(){
        return beanCount;
    }

    Vector2 render::getSize(){
        return terminalSize;
    }

    void render::Resize(){
        modifyMutex.lock();
        renderMutex.lock();
        Vector2 sz = lima::LimaTermSize();
        beanCount = sz.x * sz.y;
        delete[] beans;
        beans = new bean[beanCount];
        terminalSize = sz;

        delete streamBuffer;
        streamBuffer = new basic_str((55*beanCount) + 3);
        resized = false;

        modifyMutex.unlock();
        renderMutex.unlock();
    }




    lima::screen* render::CreateScreen(uint x, uint y, uint szX, uint szY){
    	// 1,1 is the top left corner
        if(szX <= 0 || szY <= 0) { return nullptr; }
        if(x < 1 || y < 1) { return nullptr; }
        lima::screen* scrPtr = new lima::screen(x, y, szX, szY);
        for(uint i = y; i < y + szY; i++){
            for(uint j = x; j < x + szX; j++){
                scrPtr->beans.push_back(getBean(j, i));
            }
        }

        // Screen is inside terminal window and just needs beans appropriately given
        renderScreens.push_back(scrPtr);
        
        return scrPtr;
    }
}
