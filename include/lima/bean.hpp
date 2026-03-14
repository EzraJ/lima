#pragma once

#include <charconv>

#include "ansi.hpp"
#include "basic_str.hpp"


// TODO: Replace std::to_chars and honestly CStrAdd() with lookup tables and use of booleans


namespace lima{
    struct color{
        unsigned char r,g,b;
        color(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0){
            r = red;
            g = green;
            b = blue;
        }
    };

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

    static const char* LOOKUP_TABLE[256] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "100", "101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", "112", "113", "114", "115", "116", "117", "118", "119", "120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130", "131", "132", "133", "134", "135", "136", "137", "138", "139", "140", "141", "142", "143", "144", "145", "146", "147", "148", "149", "150", "151", "152", "153", "154", "155", "156", "157", "158", "159", "160", "161", "162", "163", "164", "165", "166", "167", "168", "169", "170", "171", "172", "173", "174", "175", "176", "177", "178", "179", "180", "181", "182", "183", "184", "185", "186", "187", "188", "189", "190", "191", "192", "193", "194", "195", "196", "197", "198", "199", "200", "201", "202", "203", "204", "205", "206", "207", "208", "209", "210", "211", "212", "213", "214", "215", "216", "217", "218", "219", "220", "221", "222", "223", "224", "225", "226", "227", "228", "229", "230", "231", "232", "233", "234", "235", "236", "237", "238", "239", "240", "241", "242", "243", "244", "245", "246", "247", "248", "249", "250", "251", "252", "253", "254", "255"};
    static const std::size_t LOOKUP_TABLE_LEN[256] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

    static const std::size_t TF_TABLE[2] = {3,2};

    static const char* ITALIC[2] = {"23;", "3;"};
    static const char* UNDERLINE[2] = {"24;", "4;"};
    static const char* BLINKING[2] = {"25;", "5;"};
    static const char* INVERSE[2] = {"27;", "7;"};
    static const char* STRIKETHROUGH[2] = {"29;", "9;"};

    class bean{
        public:
            bean(char cIn = ' ', color bgIn = color(0, 0, 0), color fgIn = color(255, 255, 255), style sIn = style()){
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
                
                ptr.add(ITALIC[s.italic], TF_TABLE[s.italic]);
                ptr.add(UNDERLINE[s.underline], TF_TABLE[s.underline]);
                ptr.add(BLINKING[s.blinking], TF_TABLE[s.blinking]);
                ptr.add(INVERSE[s.inverse], TF_TABLE[s.inverse]);
                ptr.add(STRIKETHROUGH[s.strikethrough], TF_TABLE[s.strikethrough]);

                /*if(s.italic){
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
                }*/

                // This is faster than std::to_string
                // And faster than having a color buffer for conversions.
                // This practically writes directly to the render memory buffer.
                // I believe the only way to make this faster is a faster std::to_chars that also writes directly to a memory address
                // (I would look into fmt but this is simple, fast, and clear)

                // Foreground
                ptr.add("38;2;", 5);
                ptr.add(LOOKUP_TABLE[fg.r], LOOKUP_TABLE_LEN[fg.r]);
                //resultBuffer = std::to_chars(ptr.m_str + ptr.m_size, ptr.m_str + ptr.m_size + 3, fg.r);
                //ptr.m_size += resultBuffer.ptr - (ptr.m_str + ptr.m_size);
                ptr.m_str[ptr.m_size] = ';';
                ptr.m_size++;
                ptr.add(LOOKUP_TABLE[fg.g], LOOKUP_TABLE_LEN[fg.g]);
                //resultBuffer = std::to_chars(ptr.m_str + ptr.m_size, ptr.m_str + ptr.m_size + 3, fg.g);
                //ptr.m_size += resultBuffer.ptr - (ptr.m_str + ptr.m_size);
                ptr.m_str[ptr.m_size] = ';';
                ptr.m_size++;
                ptr.add(LOOKUP_TABLE[fg.b], LOOKUP_TABLE_LEN[fg.b]);
                //resultBuffer = std::to_chars(ptr.m_str + ptr.m_size, ptr.m_str + ptr.m_size + 3, fg.b);
                //ptr.m_size += resultBuffer.ptr - (ptr.m_str + ptr.m_size);
                ptr.m_str[ptr.m_size] = ';';
                ptr.m_size++;

                // Background
                ptr.add("48;2;", 5);
                ptr.add(LOOKUP_TABLE[bg.r], LOOKUP_TABLE_LEN[bg.r]);
                //resultBuffer = std::to_chars(ptr.m_str + ptr.m_size, ptr.m_str + ptr.m_size + 3, bg.r);
                //ptr.m_size += resultBuffer.ptr - (ptr.m_str + ptr.m_size);
                ptr.m_str[ptr.m_size] = ';';
                ptr.m_size++;
                ptr.add(LOOKUP_TABLE[bg.g], LOOKUP_TABLE_LEN[bg.g]);
                //resultBuffer = std::to_chars(ptr.m_str + ptr.m_size, ptr.m_str + ptr.m_size + 3, bg.g);
                //ptr.m_size += resultBuffer.ptr - (ptr.m_str + ptr.m_size);
                ptr.m_str[ptr.m_size] = ';';
                ptr.m_size++;
                ptr.add(LOOKUP_TABLE[bg.b], LOOKUP_TABLE_LEN[bg.b]);
                //resultBuffer = std::to_chars(ptr.m_str + ptr.m_size, ptr.m_str + ptr.m_size + 3, bg.b);
                //ptr.m_size += resultBuffer.ptr - (ptr.m_str + ptr.m_size);
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

            void setFG(unsigned char r, unsigned char g, unsigned char b){
                setFG(color(r, g, b));
            }
            void setFG(color in){
                fg = in;
            }

            void setBG(unsigned char r, unsigned char g, unsigned char b){
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