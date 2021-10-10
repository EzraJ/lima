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
#include <memory.h>
#include <stdexcept> // std::runtime_error
#include <sys/ioctl.h>
#include "utils/vector2.hpp"

#define CTRL_KEY(k) ((k) & 0x1f) // [2], i.e CTRL_KEY('q') == Ctrl+q on keyboard

namespace lima{
    namespace terminal{
        
        // We need to track *one* terminal and use termios structs, etc, so lets make a singleton terminal class.
        // the gameengine class will have to manage this(i.e using rawmode and turning off rawmode.)
        // All definitions in this hpp file; except singleton def in terminal.cpp
        // (Note: only organizing this way because I like it and this is a singleton class)


        // TODO:
        // cursor navigation and tracking
        // Toggling terminal flags(?)
        // Organization + etc (?)

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

            /***terminal definitions ***/
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
                // I want to preserve the original termios as much as possible, so call _disableRawMode on signals. It will be called multiple times; but _rawMode will eliminate issues.
                struct termios _originalTerm; // Note to self: use memcpy when defining C/structs like this and trying to assign them another structs data. 
                struct termios _rawTerm;
                bool _rawMode = false;
                sighandler_t prevHandleInt;
                sighandler_t prevHandleTerm;

                void signalHandler(int signum){
                    _disableRawMode();
                    std::cout << "signum called: " << signum << std::endl;
                    signal(signum, SIG_DFL);
                    raise(signum);
                    signal(signum, terminal::s_signalHandler);
                }

                // Not entirely sure if I want to keep this; I mostly copied it from[2] and keeping it because a lot of C is needed for this class. IMPORTANT!!!!
                void _die(const char* s){
                    std::cout << "Die\n";
                    perror(s);
                    exit(1);
                }


                static void s_signalHandler(int signum){ 
                    std::cout << "s_signalHandler\n";
                    getInstance().signalHandler(signum);
                }

                

                // TODO: Change all of these std::signals to a different function that resets everything normally(and call signal() elsewhere)
                bool _enableRawMode(){
                    if(_rawMode){
                        return false;
                    }

                    int result = tcgetattr(STDIN_FILENO, &_originalTerm);
                    if(result == -1){
                        throw std::runtime_error("tcgetattr(STDIN_FILENO, &_originalTerm) FAILED");
                        die("tcgetattr: ");
                        return false;
                    }

                    prevHandleTerm = std::signal(SIGTERM, terminal::s_signalHandler); // termination request, sent to the program
                    prevHandleInt = std::signal(SIGINT, terminal::s_signalHandler);  // external interrupt, usually initiated by the user (control C)

                    memcpy(&_rawTerm, &_originalTerm, sizeof(termios)); // FUCK YOU C (if I remember why you caused me trouble, of course)
                    _rawTerm.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); // Turn off carriage returns -> newlines(ICRNL), ctrlSQ(IXON), RTFM rest
                    _rawTerm.c_oflag &= ~(OPOST); // Turn off output processing(i.e \n -> \r\n)[OPOST]
                    _rawTerm.c_cflag |= (CS8); // Character masking(?, RTFM)
                    _rawTerm.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); // Turn off echo(ECHO), canonical(ICANON), ctrlVO(IEXTEN), ctrlCZ(ISIG)
                    _rawTerm.c_cc[VMIN] = 0; // Minimum required amount of bytes for read() to return
                    _rawTerm.c_cc[VTIME] = 1; // Max amount of time to wait before read() returns. If timeout, return 0 

                    result = tcsetattr(STDIN_FILENO, TCSAFLUSH, &_rawTerm);
                    if(result == -1){
                        throw std::runtime_error("tcsetattr(STDIN_FILENO, TCSAFLUSH, &_rawTerm FAILED");
                        die("tcsetattr: ");
                        _rawMode = false;
                        return false;
                    }

                    _rawMode = true;
                    return true;
                }

                bool _disableRawMode(){
                    if(_rawMode){
                        int result = tcsetattr(STDIN_FILENO, TCSAFLUSH, &_originalTerm);
                        if(result == 0){
                            _rawMode = false;
                            return true;
                        }else{
                            throw std::runtime_error("tcsetattr(STDIN_FILENO, TCSAFLUSH, &_originalTerm) FAILED to set ANY flags, or ANY changes");
                            die("tcsetattr: ");
                            _rawMode = true;
                            return false;
                        }
                    }
                    return false;
                }
            /*** cursor definitions ***/
            public:
                static vector2 getCursorPosition(){
                    return getInstance()._getCursorPosition();
                }

                static vector2 getWindowSize(){
                    return getInstance()._getWindowSize();
                }

            private:
                vector2 _getCursorPosition(){
                    char buf[32];
                    unsigned int i = 0;
                    vector2 ret(0,0);
                    ret.x = 0;
                    ret.y = 0;
                    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return ret;
                    while (i < sizeof(buf) - 1) {
                        if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
                        if (buf[i] == 'R') break;
                        i++;
                    }
                    buf[i] = '\0';
                    if (buf[0] != '\x1b' || buf[1] != '[') return ret;
                    if (sscanf(&buf[2], "%d;%d", &((&ret)->y), &((&ret)->x)) != 2) return ret; // it looks ugly but so are you

                    return ret;
                }

                vector2 _getWindowSize(){
                    struct winsize ws;
                    vector2 ret(0,0);
                    ret.x = 0;
                    ret.y = 0;
                    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
                        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return ret;
                        ret = _getCursorPosition();
                        vector2 _cp(0,0);
                        _cp = _getCursorPosition();
                        memcpy(&ret, &_cp, sizeof(vector2(0,0)));
                        return ret;
                    } else {
                        ret.x = ws.ws_col;
                        ret.y = ws.ws_row;
                        return ret;
                    }
                    return ret;
                }

        };


    };
};

