// Nice clean include file for ANSI-related stuff.
// Want to keep it lima-free so it can be used regardless of location
#pragma once


#include <iostream>
#include <string>
#include <unistd.h>

// Useful ANSI escape codes with helper stuff
// Not using macros because for now I believe having the values
// assigned with std::string will be useful

namespace ANSI{

    struct xy{ // Should probably rename this but whatever it's basically only used here and terminal.hpp
        int x, y;
    };
    
    // Using hex instead of C-style
    const std::string BEL = "\0x07"; // Terminal Bell (\a)
    const std::string BS = "\0x08"; // Backspace (\b)
    const std::string HT = "\0x09"; // Horizontal Tab (\t)
    const std::string LF = "\0x0A"; // Linefeed/newline (\n)
    const std::string VT = "\x0B"; // Vertical TAB (\v)
    const std::string FF = "\x0C"; // Formfeed(New page) (\f)
    const std::string CR = "\x0D"; // Carriage Return (\r)
    
    const std::string ESC = "\x1B"; // Escape, crucial for most ANSI sequences (\e)
    
    const std::string DEL = "\x7F"; // Delete 

    // Formatting
    
    const std::string STYLE_DEFAULT = ESC + "[0m";
    
    const std::string STYLE_BOLD = "1";
    const std::string STYLE_DIM = "2";
    const std::string STYLE_NO_DIM_OR_BOLD = "22";

    const std::string STYLE_ITALIC = "3";
    const std::string STYLE_NO_ITALIC = "23";

    const std::string STYLE_UNDERLINE = "4";
    const std::string STYLE_NO_UNDERLINE = "24";

    const std::string STYLE_BLINKING = "5";
    const std::string STYLE_NO_BLINKING = "25";

    const std::string STYLE_INVERSE = "7";
    const std::string STYLE_NO_INVERSE = "27";

    const std::string STYLE_INVISIBLE = "8"; // Still don't really understand the point of this style lol
    const std::string STYLE_NO_INVISIBLE = "28";

    const std::string STYLE_STRIKETHROUGH = "9";
    const std::string STYLE_NO_STRIKETHROUGH = "29";

    const std::string FORMAT_SEP = ";";


    const std::string END_OF_FORMAT = "m";

    // Some extra ANSI helper coders


    const std::string CURSOR_ZERO = ESC + "[H";

    const std::string ENTER_ALT_BUFFER = ESC + "[?1049h";

    const std::string EXIT_ALT_BUFFER = ESC + "[?1049l";

    const std::string VISIBLE_CURSOR = ESC + "[?25h";

    const std::string INVISIBLE_CURSOR = ESC + "[?25l";

    const std::string CLEAR_SCREEN = ESC + "[2J";

    const std::string QUERY_CURSOR_POSITION = ESC + "[6n";
    
    // Helper funcs
    
    inline std::string MOVE_CURSOR(unsigned int x, unsigned int y){ // Move cursor to (x, y) regardless of terminal size
        return ESC + "[" + std::to_string(y) + ";" + std::to_string(x) + "H";
        // (Line, Columns)
    }

    inline std::string MOVE_CURSOR_UP(unsigned int n){
        return ESC + "[" + std::to_string(n) + "A";
    }

    inline std::string MOVE_CURSOR_DOWN(unsigned int n){
        return ESC + "[" + std::to_string(n) + "B";
    }

    inline std::string MOVE_CURSOR_RIGHT(unsigned int n){
        return ESC + "[" + std::to_string(n) + "C";
    }

    inline std::string MOVE_CURSOR_LEFT(unsigned int n){
        return ESC + "[" + std::to_string(n) + "D";
    }

    constexpr inline std::string COMMAND_STYLE(std::string fmt){
        return ESC + "[" + fmt + END_OF_FORMAT;
    }

    inline const xy CURSOR_POSITION(){
        // Requires canonical mode and echo to be off to properly function
        write(STDOUT_FILENO, QUERY_CURSOR_POSITION.c_str(), QUERY_CURSOR_POSITION.length());
        std::string buf;
        // Format returned is "\0x1B[#;#R"
        std::getline(std::cin, buf, 'R');
        buf.erase(0, 2); // Delete the first two chars, R is not stored
        xy ret;
        std::string::size_type pos = buf.find(';');
        if(pos != std::string::npos){
            ret.y = std::stoi(buf.substr(0, pos));
            ret.x = std::stoi(buf.substr(pos+1, buf.size()));
        }

        return ret;

    }
    
}
