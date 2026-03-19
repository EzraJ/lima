#include "lima/bean.hpp"
namespace lima{


    static const char* LOOKUP_TABLE[256] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "100", "101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", "112", "113", "114", "115", "116", "117", "118", "119", "120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130", "131", "132", "133", "134", "135", "136", "137", "138", "139", "140", "141", "142", "143", "144", "145", "146", "147", "148", "149", "150", "151", "152", "153", "154", "155", "156", "157", "158", "159", "160", "161", "162", "163", "164", "165", "166", "167", "168", "169", "170", "171", "172", "173", "174", "175", "176", "177", "178", "179", "180", "181", "182", "183", "184", "185", "186", "187", "188", "189", "190", "191", "192", "193", "194", "195", "196", "197", "198", "199", "200", "201", "202", "203", "204", "205", "206", "207", "208", "209", "210", "211", "212", "213", "214", "215", "216", "217", "218", "219", "220", "221", "222", "223", "224", "225", "226", "227", "228", "229", "230", "231", "232", "233", "234", "235", "236", "237", "238", "239", "240", "241", "242", "243", "244", "245", "246", "247", "248", "249", "250", "251", "252", "253", "254", "255"};
    static const std::size_t LOOKUP_TABLE_LEN[256] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

    static const std::size_t TF_TABLE[2] = {3,2};

    static const char* ITALIC[2] = {"23;", "3;"};
    static const char* UNDERLINE[2] = {"24;", "4;"};
    static const char* BLINKING[2] = {"25;", "5;"};
    static const char* INVERSE[2] = {"27;", "7;"};
    static const char* STRIKETHROUGH[2] = {"29;", "9;"};



    bean::bean(unsigned char cIn, color bgIn, color fgIn, style sIn){
        invis_c[0] = cIn;
        invis_c[1] = ' ';
        bg = bgIn;
        fg = fgIn;
        s = sIn;
    }
    bean::~bean(){
        
    }

    void bean::CStrAdd(basic_str& ptr){
        ptr.add("\x1b[", 2);

        if(s.bold) ptr.add("1;", 2);
        if(s.dim && !s.bold) ptr.add("2;", 2);
        if(!s.dim && !s.bold) ptr.add("22;", 3);
        
        ptr.add(ITALIC[s.italic], TF_TABLE[s.italic]);
        ptr.add(UNDERLINE[s.underline], TF_TABLE[s.underline]);
        ptr.add(BLINKING[s.blinking], TF_TABLE[s.blinking]);
        ptr.add(INVERSE[s.inverse], TF_TABLE[s.inverse]);
        ptr.add(STRIKETHROUGH[s.strikethrough], TF_TABLE[s.strikethrough]);

        // Foreground
        ptr.add("38;2;", 5);
        ptr.add(LOOKUP_TABLE[fg.r], LOOKUP_TABLE_LEN[fg.r]);

        ptr.m_str[ptr.m_size] = ';';
        ptr.m_size++;
        ptr.add(LOOKUP_TABLE[fg.g], LOOKUP_TABLE_LEN[fg.g]);

        ptr.m_str[ptr.m_size] = ';';
        ptr.m_size++;
        ptr.add(LOOKUP_TABLE[fg.b], LOOKUP_TABLE_LEN[fg.b]);

        ptr.m_str[ptr.m_size] = ';';
        ptr.m_size++;

        // Background
        ptr.add("48;2;", 5);
        ptr.add(LOOKUP_TABLE[bg.r], LOOKUP_TABLE_LEN[bg.r]);

        ptr.m_str[ptr.m_size] = ';';
        ptr.m_size++;
        ptr.add(LOOKUP_TABLE[bg.g], LOOKUP_TABLE_LEN[bg.g]);

        ptr.m_str[ptr.m_size] = ';';
        ptr.m_size++;
        ptr.add(LOOKUP_TABLE[bg.b], LOOKUP_TABLE_LEN[bg.b]);

        // End formatting
        ptr.m_str[ptr.m_size] = 'm';
        ptr.m_size++;
        // Enter character to print
        ptr.m_str[ptr.m_size] = invis_c[s.invisible];
        ptr.m_size++;
    }

    void bean::setFG(unsigned char r, unsigned char g, unsigned char b){
        setFG(color(r, g, b));
    }
    void bean::setFG(color in){
        fg = in;
    }

    void bean::setBG(unsigned char r, unsigned char g, unsigned char b){
        setBG(color(r, g, b));
    }
    void bean::setBG(color in){
        bg = in;
    }

    void bean::setStyle(style in){
        s = in;
    }

    void bean::SetBean(unsigned char cIn, color bgIn, color fgIn, style sIn){
        invis_c[0] = cIn;
        invis_c[1] = ' ';
        bg = bgIn;
        fg = fgIn;
        s = sIn;
    }


    color bean::getBG(){
        return bg;
    }
    color bean::getFG(){
        return fg;
    }
    style bean::getStyle(){
        return s;
    }

    void bean::setChar(unsigned char cIn){
        invis_c[0] = cIn;
        invis_c[1] = ' ';
    }

    char bean::getChar(){
        return invis_c[0];
    }
}