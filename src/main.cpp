#include <iostream>
#include "args.hxx"
#include "core/terminal/terminal.hpp"
#include <sys/ioctl.h>






int main(){
    lima::terminal::terminal& myTerm = lima::terminal::terminal::getInstance();

    myTerm.enableRawMode();

    myTerm.print("Hello World!");
    myTerm.pPrint("Testing World!\n");
    myTerm.cPrint("Downhere, world!", lima::vector2(15, 15));
    myTerm.pPrint("\nABC0");
    myTerm.xPrint("X", lima::vector2(15, 15));

    myTerm.xPrint("ABCDEFG\rABC2\n", lima::vector2(15,17));
        myTerm.setCursorPosition(lima::vector2(15,20));
    

    myTerm.disableRawMode();

    
    return 0;
}