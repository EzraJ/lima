#include <iostream>
#include "args.hxx"
#include "core/terminal/terminal.hpp"
#include <sys/ioctl.h>






int main(int argc, char **argv){
    lima::terminal::terminal& myTerm = lima::terminal::terminal::getInstance();

    myTerm.enableRawMode();

    std::cout << "test\n";
    lima::vector2 windowSize = myTerm.getWindowSize();
    std::cout << "test2\r\n";
    lima::vector2 cursorPosition = myTerm.getCursorPosition();


    myTerm.disableRawMode();
    
    std::cout << windowSize.x << ", " << windowSize.y << std::endl;
    std::cout << cursorPosition.x << ", " << cursorPosition.y << std::endl;
    
    return 0;
}