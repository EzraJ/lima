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
        globalScreen = CreateScreen(1, 1, terminalSize.x, terminalSize.y);
    }

    render::~render(){
        modifyMutex.lock();  
        delete globalScreen;
        for(auto& e : renderScreens){
            if(e == globalScreen) continue;
            delete e;
        }
        
        delete[] beans;
        delete invisibleBean;
        delete streamBuffer;
        modifyMutex.unlock();
    }
    

    void render::Process(){
        if(resized) Resize();
        modifyMutex.lock();
        //globalScreen->Process((float) ((float)std::chrono::duration_cast<std::chrono::milliseconds>(timePt - std::chrono::high_resolution_clock::now()).count() / 1000.0f));
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

        for(auto& e : renderScreens){
            resizeScreen(*e);
        }
        globalScreen->xSz = sz.x;
        globalScreen->ySz = sz.y;
        
        resizeScreen(*globalScreen);
        
        for(auto& e : renderResizables){
            e->Resize();
        }
        
        resized = false;
        
        modifyMutex.unlock();
        renderMutex.unlock();
    }

    std::vector<lima::bean*> render::getBeans(uint xPos, uint yPos, uint xSz, uint ySz){
        std::vector<lima::bean*> buf;
        buf.clear();
        for(uint i = yPos; i < yPos + ySz; i++){
            for(uint j = xPos; j < xPos + xSz; j++){
                buf.push_back(getBean(j, i));
            }
        }
        return buf;
    }

    void render::getBeans(std::vector<lima::bean*>& inVec, uint xPos, uint yPos, uint xSz, uint ySz){
        inVec.clear();
        for(uint i = yPos; i < yPos + ySz; i++){
            for(uint j = xPos; j < xPos + xSz; j++){
                inVec.push_back(getBean(j, i));
            }
        }
    }

    void render::AddResizable(lima::Resizable* in){
        renderResizables.push_back(in);
    }

    void render::resizeScreen(screen& in){
        in.beans.clear();
        for(uint i = in.yPos; i < in.yPos + in.ySz; i++){
            for(uint j = in.xPos; j < in.xPos + in.xSz; j++){
                in.beans.push_back(getBean(j, i));
            }
        }
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
        modifyMutex.lock();
        renderScreens.push_back(scrPtr);
        modifyMutex.unlock();

        return scrPtr;
    }

    void render::DeleteScreen(lima::screen* ptr){
        modifyMutex.lock();

        renderScreens.erase(std::remove(renderScreens.begin(), renderScreens.end(), ptr), renderScreens.end());

        delete ptr;

        modifyMutex.unlock();
    }

    lima::bean* render::getBean(uint x, uint y){
        if(x <= 0 || y <= 0) {return invisibleBean;};
        if(x > (uint)terminalSize.x || y > (uint)terminalSize.y) {return invisibleBean;}
        return &(beans[x - 1 + (y-1) * terminalSize.x]);
    }

}
