// TODO(I know this is before the first commit but I should still write this down)
// [] Windows cross platform
// [] Terminal resize incoporated with rendering engine(doesn't have to be here)


#pragma once
// Manage all of the annoyances of the terminal, subtle linux stuff, and
// some info
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/ioctl.h>

#include "lima/ansi.hpp"

// p.s tcsetattr doesn't usually care which file descriptor it's given(stdout vs stdin)
// since they usually point to the same terminal/tty, despite this confusion
namespace terminal{
    static struct termios initialTerm; // termios before we make any changes to it
    static struct winsize _termSize;
    static ANSI::xy termSize;
    inline void restoreTerminal(){
        // We need to enter our alternative buffer(if we haven't already)
        // Then clear it up, show the cursor again, and return to the main buffer

        std::cout << ANSI::ENTER_ALT_BUFFER;
        std::cout << ANSI::CLEAR_SCREEN;
        std::cout << ANSI::VISIBLE_CURSOR;
        std::cout << ANSI::EXIT_ALT_BUFFER;


        tcsetattr(STDOUT_FILENO, TCSANOW, &initialTerm);
    }

    inline ANSI::xy terminalSize(){
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &_termSize);
        // x = cols
        // y = rows
        termSize.x = _termSize.ws_col;
        termSize.y = _termSize.ws_row;
        return termSize;
    }

    inline void restoreDie(int signum [[maybe_unused]]){
        exit(1); // Should call restoreTerminal()
    }



        // TODO: Add windows compatability 
    inline void initializeTerminal(){
        struct termios limaTerm;
        tcgetattr(STDOUT_FILENO, &limaTerm);
        initialTerm = limaTerm;

        // Time to get messy; we need to set the termial to "raw" mode
        // raw mode will ignore most inputs(like SIGINT from Control-C)
        // and other annoying keys we need to ignore in our program.

        // IXON stops Control-S and Control-Q from working
        // ICRNL Turns carriage returns into newlines, we turn this feature off
        limaTerm.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

        // OPOST Turns off output processing(like \n -> \r\n)
        limaTerm.c_oflag &= ~(OPOST);

        limaTerm.c_cflag |= (CS8);

        // ECHO Turns off Echo mode(typing printing chars)
        // ICANON Turns off canonical mode
        // ISIG Turns off signals like SIGINT or SIGTSTP being sent
        // IEXTEN turns off Control-V
        limaTerm.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

        // BRKINT, INPCK, ISTRIP, and CS8 are all flags, that from what I understand, are historically
        // used for "raw" mode. I'm not sure why, but just in case we'll set them.

        // VMIN sets the minimum characters any processing on stdin needs before returning
        limaTerm.c_cc[VMIN] = 0;
        // Timeout for reads
        limaTerm.c_cc[VTIME] = 0;

        tcsetattr(STDOUT_FILENO, TCSANOW, &limaTerm);
        // Now that we are done entering raw mode we need to immediately setup safeguards

        atexit(restoreTerminal);

        struct sigaction saInt;
        saInt.sa_handler = restoreDie;
        sigemptyset(&saInt.sa_mask);
        saInt.sa_flags = SA_RESTART; // Unsure if this is the right one to use.

        sigaction(SIGINT, &saInt, NULL);

        if(saInt.sa_handler == SIG_IGN){
            exit(1);
            // Something bad happened and the signals weren't able to be intiailized
        }

        struct sigaction saTerm;
        saTerm.sa_handler = restoreDie;
        sigemptyset(&saTerm.sa_mask);
        saTerm.sa_flags = SA_RESTART;
        sigaction(SIGTERM, &saTerm, NULL);
        if(saTerm.sa_handler == SIG_IGN){
            exit(1);
        }


        // I would typically use signal but apparently the multi-thread behaviour
        // is undefined in man and kind of ambigious in POSIX, it's recommended to use
        // sigaction anyways. Time to learn sigaction lol
        //signal(SIGTERM, restoreDie);
        //signal(SIGINT, restoreDie);
        // As of 8/3/24 the signals are being processed right

        //std::cout.setf(std::ios::unitbuf); // Make sure all data is flushed after insertion
        

        // Now that we have some safeguards in place, we need to
        // enter the terminals alternative buffer, and we've initialized
        /*std::cout << ANSI::ENTER_ALT_BUFFER;
        std::cout << ANSI::INVISIBLE_CURSOR;
        std::cout << ANSI::CLEAR_SCREEN;
        std::cout << ANSI::CURSOR_ZERO;*/

        write(STDOUT_FILENO, ANSI::ENTER_ALT_BUFFER.c_str(), ANSI::ENTER_ALT_BUFFER.length());
        write(STDOUT_FILENO, ANSI::INVISIBLE_CURSOR.c_str(), ANSI::INVISIBLE_CURSOR.length());
        write(STDOUT_FILENO, ANSI::CLEAR_SCREEN.c_str(), ANSI::CLEAR_SCREEN.length());
        write(STDOUT_FILENO, ANSI::CLEAR_SCREEN.c_str(), ANSI::CLEAR_SCREEN.length());
        // Hopefully now we don't have to do too much sucky terminal stuff...
    }

}
