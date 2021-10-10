// Setup everything terminal related
// TODO:
// Have terminal singleton class that handles:
// Everything terminal related(duh), raw mode, terminal settings, cursor info, and cursor control.
// Terminal mgt

/*
Shamelessly copied sources: (references by [num])
    https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
    https://stackoverflow.com/questions/5640884/what-is-the-c-stream-equivalent-to-perror

*/

#pragma once

#include <iostream>
#include <termios.h> // termios
#include <unistd.h> // read
#include <cstdlib> // std::atexit (handles exit() and normal exit calls)
#include <csignal> // signal
#include <stdexcept> // std::runtime_error

#define CTRL_KEY(k) ((k) & 0x1f) // [2], i.e CTRL_KEY('q') == Ctrl+q on keyboard

namespace lima{
    namespace terminal{
        
        // We need to track *one* terminal and use termios structs, etc, so lets make a singleton terminal class.
        // the gameengine class will have to manage this(i.e using rawmode and turning off rawmode.)
        // All definitions in this hpp file; except singleton def in terminal.cpp


        // What we want the terminal to do:
        // rawmode toggle(including restoring old termios)
        // cursor navigation and tracking
        // Toggling terminal flags(?)

        // Note: probably going to use some nasty C stuff, maybe not
        class terminal{
            /*** singleton definitions ***/
            public:
                terminal(const terminal&) = delete;
                void operator=(terminal const&) = delete;
                static terminal& getInstance(){
                    return s_Instance;
                }
            private:
                terminal() {}
                static terminal s_Instance;

            /*** terminal ***/
            public:
                static bool enableRawMode(){
                    return getInstance()._enableRawMode();
                }

                static bool disableRawMode(){
                    return getInstance()._disableRawMode();
                }

                static void die(const char* s){
                    getInstance()._die(s);
                }

            private:
                // I want to preserve the original termio struct on exit, so use std::atexist and signal to ensure it happens on SIGINT and the program exitting normally
                // This may result in _disableRawMode being called multiple times, but I don't want users having to deal with their terminal being in rawmode at all costs.
                // (plus I'm gonna hope that doesn't cause unexpected issues later..)

                // Note: Behavior is undefined for the signals due to standard library functions being called(I presume)
                struct termios* _originalTerm = nullptr;
                struct termios* _rawTerm = nullptr;
                //static bool _rawMode = false;

                void signalHandler(int signum){
                    _disableRawMode();
                    std::cout << "signum called: " << signum << std::endl;
                    std::exit(signum);
                }

                void atExitHandle(){
                    _disableRawMode();
                }

                // Not entirely sure if I want to keep this; I mostly copied it from[2] and keeping it because a lot of C is needed for this class. IMPORTANT!!!!
                void _die(const char* s){
                    perror(s);
                    exit(1);
                }

                static void s_atExitHandle(){
                    getInstance().atExitHandle();
                }

                static void s_signalHandler(int signum){ 
                    getInstance().signalHandler(signum);
                }

                

                // TODO: Change all of these std::signals to a different function that resets everything normally(and call signal() elsewhere)
                bool _enableRawMode(){
                    std::cout << "Check 1\n";
                    /*if(_rawMode){
                        return false; // Already in rawmode
                    }*/
                    std::cout << "Check 2\n";
                    int result = tcgetattr(STDIN_FILENO, &_originalTerm);
                    std::cout << "Check 3\n";
                    if(result == -1){
                        throw std::runtime_error("tcgetattr(STDIN_FILENO, &_originalTerm) FAILED");
                        die("tcgetattr: ");
                        return false;
                    }
                    std::cout << "Check 4\n";
                    /*std::signal(SIGTERM, terminal::s_signalHandler); // termination request, sent to the program
                    std::signal(SIGSEGV, terminal::s_signalHandler); // invalid memory access (infamous segmentation fault)                 [Should this be added?]
                    std::signal(SIGINT, terminal::s_signalHandler);  // external interrupt, usually initiated by the user (control C)
                    std::signal(SIGILL, terminal::s_signalHandler);  // invalid program image, such as invalid instruction                  [Should this be added?]
                    std::signal(SIGABRT, terminal::s_signalHandler); // abnormal terminal condition, as is e.g. initiated by std::abort()   [Should this be added?]
                    std::signal(SIGFPE, terminal::s_signalHandler); // erroneous arithemetic opeartion such as divide by zero               [Should this be added?]
                    std::atexit(terminal::s_atExitHandle);
                    std::cout << "Check 5\n";*/
                    _rawTerm = _originalTerm;
                    _rawTerm.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); // Turn off carriage returns -> newlines(ICRNL), ctrlSQ(IXON), RTFM rest
                    _rawTerm.c_oflag &= ~(OPOST); // Turn off output processing(i.e \n -> \r\n)[OPOST]
                    _rawTerm.c_cflag |= (CS8); // Character masking(?, RTFM)
                    _rawTerm.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); // Turn off echo(ECHO), canonical(ICANON), ctrlVO(IEXTEN), ctrlCZ(ISIG)

                    _rawTerm.c_cc[VMIN] = 0; // Minimum required amount of bytes for read() to return
                    _rawTerm.c_cc[VTIME] = 1; // Max amount of time to wait before read() returns. If timeout, return 0 
                    std::cout << "Check 6\n";
                    result = tcsetattr(STDIN_FILENO, TCSAFLUSH, &_rawTerm);
                    std::cout << "Check 7\nresult: " << result << std::endl;

                    if(result == -1){
                        throw std::runtime_error("tcsetattr(STDIN_FILENO, TCSAFLUSH, &_rawTerm FAILED");
                        die("tcsetattr: ");
                        //_rawMode = false;
                        return false;
                    }
                    std::cout << "Check 8\n";
                    //_rawMode = true;
                    std::cout << "Check 9\n";
                }

                bool _disableRawMode(){
                    int result = tcsetattr(STDIN_FILENO, TCSAFLUSH, &_originalTerm);
                    // Adding this r/programmerhorror block to remind me that tcsetattr returns 0 for *any* changes, so if I run into issues
                    // change this to check each termios variable.
                    if(result == 0){
                        //_rawMode = false;
                        return true;
                    }else{
                        throw std::runtime_error("tcsetattr(STDIN_FILENO, TCSAFLUSH, &_originalTerm) FAILED to set ANY flags, or ANY changes");
                        die("tcsetattr: ");
                        //_rawMode = true;
                        return false;
                    }
                }

        };


    };
};

