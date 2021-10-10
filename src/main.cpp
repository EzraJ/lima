#include <iostream>
#include "args.hxx"
#include "core/terminal/terminal.hpp"
#include "core/engine/block/block.hpp"
#include "core/engine/scene.hpp"





int main(){
    //lima::terminal::terminal& myTerm = lima::terminal::terminal::getInstance();

    lima::core::engine::scene myScene(0);
    myScene.openManifest("test.man");
    myScene.openFile("test.level");

    auto level = myScene.sceneData();

    for(auto& e : level){
        for(auto& v: e){
            std::cout << v.getRender() <<"["<<v.getPos().x << ", " << v.getPos().y <<"]";
        }
        std::cout << "\n";
    }
    
    /*myTerm.enableRawMode();

    myTerm.print("Hello World!");
    myTerm.pPrint("Testing World!\n");
    myTerm.cPrint("Downhere, world!", lima::vector2(15, 15));
    myTerm.pPrint("\nABC0");
    myTerm.xPrint("X", lima::vector2(15, 15));

    myTerm.xPrint("ABCDEFG\rABC2\n", lima::vector2(15,17));
        myTerm.setCursorPosition(lima::vector2(15,20));
    

    myTerm.disableRawMode();*/

    
    return 0;
}