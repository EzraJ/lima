#include <iostream>
#include "args.hxx"
#include "core/terminal/terminal.hpp"


char editorReadKey(){
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if(nread == -1 && errno != EAGAIN) lima::terminal::terminal::die("read");
    }
    return c;
}

void editorProcessKeypress() {
  char c = editorReadKey();
  switch (c) {
    case CTRL_KEY('q'):
      lima::terminal::terminal::disableRawMode();
      exit(0);
      break;
    default:
        //char str[3];
        //sprintf(str, "%c\r\n", c);
        //write(STDOUT_FILENO, str, 3);
        std::cout << (char)c << "\r\n"; // so yes, we can use std::cout even with raw mode on.
        //write(STDOUT_FILENO, "~\r\n", 3);
  }
}

int main(int argc, char **argv){

    lima::terminal::terminal::enableRawMode();

    while(1){
        editorProcessKeypress();
    }

    lima::terminal::terminal::disableRawMode();

    return 0;
}