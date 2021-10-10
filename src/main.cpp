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
      exit(0);
      break;
    default:
        write(STDOUT_FILENO, "~\r\n", 3);
  }
}

int main(int argc, char **argv){

    /*lima::terminal::terminal& myTerm = lima::terminal::terminal::getInstance();

    myTerm.enableRawMode();

    lima::terminal::terminal::enableRawMode();

    while(1){
        editorProcessKeypress();
    }

    lima::terminal::terminal::disableRawMode();

    myTerm.disableRawMode();*/
    std::cout << "test" << std::endl;
    lima::terminal::terminal::enableRawMode();
    //write(STDOUT_FILENO, "~\r\n", 3);
    //lima::terminal::terminal::disableRawMode();

    //std::cout << fileno(stdout) << std::endl;

    return 0;
}