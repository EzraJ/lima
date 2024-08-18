#pragma once
#include <string>
#include <memory>
#include <cstring>
#include <cstdlib>

#include "ansi.hpp"


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

                beanContent.reserve(55);
                _fg.reserve(17);
                _bg.reserve(17);


                _color();

                CStr();
                //Assemble();
            }
            ~bean(){
                
            }

            std::string CStr(){
                char* buf = new char[55];
                int n = 0;
                buf[0] = '\x1b';
                buf[1] = '[';
                n = 2;
                if(s.bold){
                    buf[n] = '1';
                    n++;
                    buf[n] = ';';
                    n++;
                }

                if(s.dim && !s.bold){
                    buf[n] = '2';
                    n++;
                    buf[n] = ';';
                    n++;
                }

                if(!s.dim && !s.bold){
                    buf[n] = '2';
                    n++;
                    buf[n] = '2';
                    n++;
                    buf[n] = ';';
                    n++;
                }

                if(s.italic){
                    buf[n] = '3';
                    n++;
                    buf[n] = ';';
                    n++;
                }else{
                    buf[n] = '2';
                    n++;
                    buf[n] = '3';
                    n++;
                    buf[n] = ';';
                    n++;
                }

                if(s.underline){
                    buf[n] = '4';
                    n++;
                    buf[n] = ';';
                    n++;
                }else{
                    buf[n] = '2';
                    n++;
                    buf[n] = '4';
                    n++;
                    buf[n] = ';';
                    n++;
                }

                if(s.blinking){
                    buf[n] = '5';
                    n++;
                    buf[n] = ';';
                    n++;
                }else{
                    buf[n] = '2';
                    n++;
                    buf[n] = '5';
                    n++;
                    buf[n] = ';';
                    n++;
                }

                if(s.inverse){
                    buf[n] = '7';
                    n++;
                    buf[n] = ';';
                    n++;
                }else{
                    buf[n] = '2';
                    n++;
                    buf[n] = '7';
                    n++;
                    buf[n] = ';';
                    n++;
                }

                if(s.strikethrough){
                    buf[n] = '9';
                    n++;
                    buf[n] = ';';
                    n++;
                }else{
                    buf[n] = '2';
                    n++;
                    buf[n] = '9';
                    n++;
                    buf[n] = ';';
                    n++;
                }
                buf[n] = '\0';

                std::string ret(buf);
                ret.append(_fg);
                ret.append(_bg);
                if(s.invisible){
                    ret += " ";
                }else{
                    ret += c;
                }
                beanContent = ret;
                return ret;
            }


            std::string Assemble(){
                beanContent.clear();
                beanContent.append("\x1b[");

                if(s.bold) beanContent.append("1;");
                if(s.dim && !s.bold) beanContent.append("2;");
                if(!s.dim && !s.bold) beanContent.append("22;");
                beanContent.append((s.italic) ? "3;" : "23;");
                beanContent.append((s.underline) ? "4;" : "24;");
                beanContent.append((s.blinking) ? "5;" : "25;");
                beanContent.append((s.inverse) ? "7;" : "27;");
                beanContent.append((s.strikethrough) ? "9;" : "29;");
                beanContent.append(_fg);
                beanContent.append(_bg);
                if(s.invisible){
                    beanContent += " ";
                }else{
                    beanContent += c;
                }
                beanContent.shrink_to_fit();
                return beanContent;

            }

            void setFG(int r, int g, int b){
                setFG(color(r, g, b));
            }
            void setFG(color in){
                fg = in;
                _color();
                CStr();
                //Assemble();
            }

            void setBG(int r, int g, int b){
                setBG(color(r, g, b));
            }
            void setBG(color in){
                bg = in;
                _color();
                CStr();
                //Assemble();
            }

            void setStyle(style in){
                s = in;
                CStr();
                //Assemble();
            }

            void SetBean(char cIn, color bgIn, color fgIn, style sIn){
                c = cIn;
                bg = bgIn;
                fg = fgIn;
                s = sIn;
                _color();
                CStr();
                //Assemble();
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
                CStr();
                //Assemble();
                //Assemble(); // Might just trim the end of the string instead of a whole assembly
            }

            char getChar(){
                return c;
            }

            // What will be printed
            std::string getContent(){
                return beanContent;
            }


        private:


            void _color(){
                _fg.clear();
                _bg.clear();
                _fg.append("38;2;");
                _fg.append(std::to_string(fg.r));
                _fg.append(";");
                _fg.append(std::to_string(fg.g));
                _fg.append(";");
                _fg.append(std::to_string(fg.b));
                _fg.append(";");

                _bg.append("48;2;");
                _bg.append(std::to_string(bg.r));
                _bg.append(";");
                _bg.append(std::to_string(bg.g));
                _bg.append(";");
                _bg.append(std::to_string(bg.b));
                _bg.append("m");

                _fg.shrink_to_fit();
                _bg.shrink_to_fit();
            }

            color bg, fg;
            std::string _bg, _fg;
            style s;
            char c;
            std::string beanContent;
    };


}