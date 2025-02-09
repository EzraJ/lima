#include <unistd.h>
#include <string>
#include "lima/keyboard.hpp"

namespace lima{
    void keyboard::Read(){
        lastPressed = '\0';
        read(STDIN_FILENO, &lastPressed, 1);

    }

    


}