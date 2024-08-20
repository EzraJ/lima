#pragma once
#define _OPEN_SYS_ITOA_EXT
#include <string>
#include <memory>
#include <cstring>
#include <cstdlib>
#include <charconv>
#include <array>

#include "ansi.hpp"
#include "basic_str.hpp"





namespace lima{

    struct color{
        unsigned char r,g,b;
        color(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0){
            r = red;
            g = green;
            b = blue;
        }
    };



    // TODO: Make this 2 bytes for memory optimization perhaps?
    struct style{
        //bool reset = false; // Goes at the end of the sequence [0m
        bool bold = false; // 1m ~ 22m
        bool dim = false; // 2m ~ 22m
        bool italic = false; // 3m ~ 23m
        bool underline = false; // 4m ~ 24m
        bool blinking = false; // 5m ~ 25m
        bool inverse = false; // 7m ~ 27m
        bool invisible = false; // 8m ~ 28m -- What's the point of this? You have to print text to change it...
        bool strikethrough = false; // 9m ~ 29m
        style(bool boldIn = false, bool dimIn = false, bool italicIn = false, bool underlineIn = false, bool blinkingIn = false, bool inverseIn = false, bool invisibleIn = false,bool strikethroughIn = false){
            bold = boldIn;
            dim = dimIn;
            italic = italicIn;
            underline = underlineIn;
            blinking = blinkingIn;
            inverse = inverseIn;
            invisible = invisibleIn;
            strikethrough = strikethroughIn;
        }
    };
    


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
            bean(char cIn = '#', color bgIn = color(0, 0, 0), color fgIn = color(255, 255, 255), style sIn = style()){
                c = cIn;
                bg = bgIn;
                fg = fgIn;
                s = sIn;
            }
            ~bean(){
            }

            
            void CStrAdd(basic_str& ptr){
                ptr.add("\x1b[", 2);

                if(s.bold) ptr.add("1;", 2);
                if(s.dim && !s.bold) ptr.add("2;", 2);
                if(!s.dim && !s.bold) ptr.add("22;", 3);
                
                if(s.italic){
                    ptr.add("3;", 2);
                }else{
                    ptr.add("23;", 3);
                }

                if(s.underline){
                    ptr.add("4;", 2);
                }else{
                    ptr.add("24;", 3);
                }

                if(s.blinking){
                    ptr.add("5;", 2);
                }else{
                    ptr.add("25;", 3);
                }

                if(s.inverse){
                    ptr.add("7;", 2);
                }else{
                    ptr.add("27;", 3);
                }

                if(s.strikethrough){
                    ptr.add("9;", 2);
                }else{
                    ptr.add("29;", 3);
                }

                // This is faster than std::to_string
                // And faster than having a color buffer for conversions.
                // This practically writes directly to the render memory buffer.
                // I believe the only way to make this faster is a faster std::to_chars that also writes directly to a memory address
                // (I would look into fmt but this is simple, fast, and clear)

                // Foreground
                ptr.add("38;2;", 5);
                resultBuffer = std::to_chars(ptr.m_str + ptr.m_size, ptr.m_str + ptr.m_size + 3, fg.r);
                ptr.m_size += resultBuffer.ptr - (ptr.m_str + ptr.m_size);
                ptr.m_str[ptr.m_size] = ';';
                ptr.m_size++;
                resultBuffer = std::to_chars(ptr.m_str + ptr.m_size, ptr.m_str + ptr.m_size + 3, fg.g);
                ptr.m_size += resultBuffer.ptr - (ptr.m_str + ptr.m_size);
                ptr.m_str[ptr.m_size] = ';';
                ptr.m_size++;
                resultBuffer = std::to_chars(ptr.m_str + ptr.m_size, ptr.m_str + ptr.m_size + 3, fg.b);
                ptr.m_size += resultBuffer.ptr - (ptr.m_str + ptr.m_size);
                ptr.m_str[ptr.m_size] = ';';
                ptr.m_size++;

                // Background
                ptr.add("48;2;", 5);
                resultBuffer = std::to_chars(ptr.m_str + ptr.m_size, ptr.m_str + ptr.m_size + 3, bg.r);
                ptr.m_size += resultBuffer.ptr - (ptr.m_str + ptr.m_size);
                ptr.m_str[ptr.m_size] = ';';
                ptr.m_size++;
                resultBuffer = std::to_chars(ptr.m_str + ptr.m_size, ptr.m_str + ptr.m_size + 3, bg.g);
                ptr.m_size += resultBuffer.ptr - (ptr.m_str + ptr.m_size);
                ptr.m_str[ptr.m_size] = ';';
                ptr.m_size++;
                resultBuffer = std::to_chars(ptr.m_str + ptr.m_size, ptr.m_str + ptr.m_size + 3, bg.b);
                ptr.m_size += resultBuffer.ptr - (ptr.m_str + ptr.m_size);
                ptr.m_str[ptr.m_size] = 'm';
                ptr.m_size++;

                if(s.invisible){
                    ptr.m_str[ptr.m_size] = ' ';
                    ptr.m_size++;
                    return;
                }else{
                    ptr.m_str[ptr.m_size] = c;
                    ptr.m_size++;
                }
            }



            void setFG(int r, int g, int b){
                setFG(color(r, g, b));
            }
            void setFG(color in){
                fg = in;
            }

            void setBG(int r, int g, int b){
                setBG(color(r, g, b));
            }
            void setBG(color in){
                bg = in;
            }

            void setStyle(style in){
                s = in;
            }

            void SetBean(char cIn, color bgIn, color fgIn, style sIn){
                c = cIn;
                bg = bgIn;
                fg = fgIn;
                s = sIn;
            }


            color getBG(){
                return bg;
            }
            color getFG(){
                return fg;
            }
            style getStyle(){
                return s;
            }

            void setChar(char cIn){
                c = cIn;
            }

            char getChar(){
                return c;
            }

        private:
            std::to_chars_result resultBuffer;
            color bg, fg;
            style s;
            char c;
    };


}