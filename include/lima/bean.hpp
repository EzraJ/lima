#pragma once

#include <charconv>

#include "ansi.hpp"
#include "basic_str.hpp"
#include "color.hpp"
#include "style.hpp"

// TODO: Replace std::to_chars and honestly CStrAdd() with lookup tables and use of booleans


namespace lima{
    
    // STRIKE THRU 0
    // INVIS 1
    // INVERSE 2
    // BLINKING 3
    // UNDERLINE 4
    // ITALIC 5
    // DIM 6
    // BOLD 7


    class bean{
        public:
            bean(unsigned char cIn = ' ', color bgIn = color(0, 0, 0), color fgIn = color(255, 255, 255), style sIn = style());
            ~bean();

            void CStrAdd(basic_str& ptr);

            void setFG(unsigned char r, unsigned char g, unsigned char b);
            void setFG(color in);

            void setBG(unsigned char r, unsigned char g, unsigned char b);
            void setBG(color in);

            void setStyle(style in);

            void SetBean(unsigned char cIn, color bgIn, color fgIn, style sIn);


            color getBG();
            color getFG();
            style getStyle();

            void setChar(unsigned char cIn);
            char getChar();

        private:
            color bg, fg;
            style s;
            unsigned char invis_c[2];
    };
}